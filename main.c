#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/nvm/nvm.h"
#include "Touch_Read.h"
#include "Key_Scan.h"
#include "Seg_driver.h"

void TMR_INT_Handler(void);
void STATE_Update(void);
void STATE_Operation(void);
void Touch_Operation(void);
void Key_Operation(void);
void THR_Load(void);
void THR_Save(void);
uint8_t p[4]={0,13,0,0};                    /* 上电立即显示0D00 */

enum STATE
{
    STATE_IDLE=0U,
    STATE_CORRECT=1U,
    STATE_DEBOUNCE=2U,
    STATE_DOWN=3U,
    STATE_LONG_ACTIVE=4U,
    STATE_DOUBLE_WAIT=5U,
    STATE_DOUBLE_ACTIVE=6U
};

enum Key_event
{
    KEY_NO_EVENT=0U,
    KEY_PRESS=1U,
    KEY_RELEASE=2U,
    KEY_LONG_PRESS=3U,
    KEY_LONG_RELEASE=4U,
    KEY_SINGLE=5U,
    KEY_DOUBLE_PRESS=6U,
    KEY_DOUBLE_RELEASE=7U,
    KEY_ERROR=8U,
};

static uint8_t seg_index = 0;
static enum STATE current_state=STATE_IDLE;
static enum STATE next_state=STATE_IDLE;
static uint8_t Num_of_Down=0;
uint8_t Window=0;
uint16_t THRESHOLD=50;
uint8_t Key_Value=0;
uint8_t cur_key=0;
static enum Key_event key_event=KEY_NO_EVENT;
static char disp_tmp[4];
static volatile uint16_t touch_time_4ms=0;
static volatile uint8_t touch_sample_due=0;
static volatile uint8_t key_scan_due=0;
static uint8_t touch_count[3]={0,0,0};
#define THRESHOLD_STEP 1u
#define LONG_PRESS_TIME 50u                     /* 首次长按：50 x 4 ms = 0.2 s */
#define LONG_REPEAT_TIME 50u                    /* 连续调整：50 x 4 ms = 0.2 s */
#define DEBOUNCE_TIME 3u
#define DOUBLE_WAIT_TIME 128u
#define TOUCH_HALF_SECOND 63u                  /* 按实测校正：触摸长按约0.5 s一次 */
#define TOUCH_DOUBLE_TIME 64u                  /* 按实测校正：双击窗口约0.5 s */
#define EEP_TH_L       (EEPROM_START_ADDRESS+0x00u)
#define EEP_TH_H       (EEPROM_START_ADDRESS+0x01u)
#define EEP_TH_MAGIC   (EEPROM_START_ADDRESS+0x02u)
#define EEP_MAGIC_VAL  0xA5u

void THR_Load(void)
{
    if(EEPROM_Read(EEP_TH_MAGIC)==EEP_MAGIC_VAL)
    {
        THRESHOLD=(uint16_t)(((uint16_t)EEPROM_Read(EEP_TH_H)<<8) |
                            EEPROM_Read(EEP_TH_L));
        if(THRESHOLD==0u) THRESHOLD=50u;
    }
}

void THR_Save(void)
{
    NVM_UnlockKeySet(UNLOCK_KEY);
    EEPROM_Write(EEP_TH_L,(uint8_t)THRESHOLD);
    while(NVM_IsBusy()) {}
    EEPROM_Write(EEP_TH_H,(uint8_t)(THRESHOLD>>8));
    while(NVM_IsBusy()) {}
    EEPROM_Write(EEP_TH_MAGIC,EEP_MAGIC_VAL);
    while(NVM_IsBusy()) {}
    NVM_UnlockKeyClear();
}

int main(void)
{
    SYSTEM_Initialize();
    THR_Load();                              /* 上电自动读取手动保存的阈值 */
    TMR0_PeriodMatchCallbackRegister(TMR_INT_Handler);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    /* 先启动显示中断，再做CVD基线校准，避免校准期间数码管全黑。 */
    Touch_Calibrate();                          /* 上电时请勿触摸按键 */

    while(1)
    {
        Key_Operation();
        STATE_Update();
        STATE_Operation();
    }
    return 0;
}

void Key_Operation(void)
{
    static uint8_t key_hold_ticks=0, key_repeat_ticks=0;
    static uint8_t key_long_active=0;
    uint8_t level;
    uint8_t kid;

    if(!key_scan_due) return;

    INTERRUPT_GlobalInterruptDisable();
    key_scan_due=0;
    INTERRUPT_GlobalInterruptEnable();

    level=Scan_All_Keys();
    kid=level ? key(level,Key_Value) : 0u;

    if(level)
    {
        if(Num_of_Down==0)
        {
            cur_key=kid;
            key_hold_ticks=0;
            key_repeat_ticks=0;
            key_long_active=0;
        }
        if(Num_of_Down<255) ++Num_of_Down;
        if(!key_long_active)
        {
            if(++key_hold_ticks>=LONG_PRESS_TIME)
            {
                key_long_active=1;
                key_repeat_ticks=0;
                key_event=KEY_LONG_PRESS;
            }
        }
        else if(++key_repeat_ticks>=LONG_REPEAT_TIME)
        {
            key_repeat_ticks=0;
            key_event=KEY_LONG_PRESS;
        }
    }
    else
    {
        if(Num_of_Down>=DEBOUNCE_TIME)
        {
            key_event=key_long_active ? KEY_LONG_RELEASE : KEY_RELEASE;
            Window=DOUBLE_WAIT_TIME;
        }
        Num_of_Down=0;
        key_hold_ticks=0;
        key_repeat_ticks=0;
        key_long_active=0;
    }

    if(level==0 && Window>0) --Window;
}

void STATE_Update()
{
    current_state=next_state;

    /* 校准态下，键2/3每收到一次0.2秒长按节拍就调整1。 */
    if(key_event==KEY_LONG_PRESS)
    {
        key_event=KEY_NO_EVENT;
        if(current_state==STATE_CORRECT)
        {
            if(cur_key==2 && THRESHOLD<65535u) ++THRESHOLD;
            else if(cur_key==3 && THRESHOLD>0u) --THRESHOLD;
        }
        return;
    }

    if(key_event==KEY_RELEASE || key_event==KEY_LONG_RELEASE)
    {
        uint8_t is_long = (key_event==KEY_LONG_RELEASE);
        key_event=KEY_NO_EVENT;
        /* 键1从任意非校准状态进入校准；校准状态下再次按键1退出。 */
        if(cur_key==1)
        {
            /* 掉电检测接入前暂不保存，阈值只在掉电时统一落盘 */
            next_state=(current_state==STATE_CORRECT)?STATE_IDLE:STATE_CORRECT;
            return;
        }

        /* 手指保持在触摸键上，松开普通键4后自动计算并显示阈值。 */
        if(cur_key==4)
        {
            uint16_t auto_threshold=Touch_CalculateThreshold();
            if(auto_threshold!=0u)
            {
                THRESHOLD=auto_threshold;
                next_state=STATE_CORRECT;
            }
            return;
        }

        /* 普通键5：清空三个触摸按键的全部计数。 */
        if(cur_key==5)
        {
            touch_count[0]=0;
            touch_count[1]=0;
            touch_count[2]=0;
            return;
        }

        /* 普通键6：仅在校准界面保存阈值，并启动两次闪烁提示。 */
        if(cur_key==6)
        {
            if(current_state==STATE_CORRECT)
            {
                uint8_t i;
                THR_Save();
                for(i=0u;i<2u;i++)
                {
                    p[0]=36u;
                    p[1]=36u;
                    p[2]=36u;
                    p[3]=36u;
                    __delay_ms(200);
                    Num2Str(THRESHOLD,disp_tmp);
                    print_seg(disp_tmp);
                    __delay_ms(200);
                }
            }
            return;
        }

        switch(current_state)
        {
            case STATE_CORRECT:
                /* 长按已按0.2秒节拍调整，松手时不再重复加减。 */
                if(!is_long && cur_key==2 && THRESHOLD<65535u)
                    THRESHOLD+=THRESHOLD_STEP;
                else if(!is_long && cur_key==3 && THRESHOLD>=THRESHOLD_STEP)
                    THRESHOLD-=THRESHOLD_STEP;
                break;
            default: break;
        }
        return;
    }

    switch(current_state)
    {
        case STATE_IDLE:
            if(Num_of_Down>=1)
            {
                next_state=STATE_DEBOUNCE;
            }
            else next_state=STATE_IDLE;
            break;
        case STATE_CORRECT:
            next_state=STATE_CORRECT;
            break;
        case STATE_DEBOUNCE:
            if(Num_of_Down>=3) next_state=STATE_DOWN;
            else if(Num_of_Down==0) next_state=STATE_IDLE;
            else next_state=STATE_DEBOUNCE;
            break;
        case STATE_DOWN:
            if(Num_of_Down>=255)
            {
                Num_of_Down=0;
                next_state=STATE_LONG_ACTIVE;
            }
            else if(Num_of_Down==0) next_state=STATE_DOUBLE_WAIT;
            break;
        case STATE_LONG_ACTIVE:
            break;
        case STATE_DOUBLE_WAIT:
            if(Num_of_Down>=3&&Window!=0) next_state=STATE_DOUBLE_ACTIVE;
            else if(Window==0) next_state=STATE_IDLE;
            else if(Num_of_Down<3) next_state=STATE_DOUBLE_WAIT;
            break;
        case STATE_DOUBLE_ACTIVE:
            if(Window!=0) next_state=STATE_DOUBLE_ACTIVE;
            else next_state=STATE_IDLE;
            break;
    }
}

void STATE_Operation()
{
     switch(current_state)
    {
        case STATE_IDLE:
        case STATE_DEBOUNCE:
        case STATE_DOWN:
        case STATE_LONG_ACTIVE:
        case STATE_DOUBLE_WAIT:
        case STATE_DOUBLE_ACTIVE:
            Touch_Operation();
            break;
        case STATE_CORRECT:
            Num2Str(THRESHOLD,disp_tmp);
            print_seg(disp_tmp);
            break;
    }
}

void Touch_Operation(void)
{
    static uint8_t candidate=0, candidate_count=0, stable_key=0;
    static uint8_t press_key=0, long_active=0, second_click=0;
    static uint8_t pending_key=0;
    static uint8_t shown_key=0, shown_type=13;  /* 13='D'：单击 */
    static uint16_t press_start=0, repeat_time=0, pending_time=0;
    uint16_t now;

    INTERRUPT_GlobalInterruptDisable();
    now=touch_time_4ms;
    INTERRUPT_GlobalInterruptEnable();

    if(touch_sample_due)
    {
        uint8_t ch, raw_key;
        touch_sample_due=0;
        ch=Scan_Touch();
        raw_key=(ch==0xFFu)?0u:(uint8_t)(ch+1u);

        if(raw_key!=candidate)
        {
            candidate=raw_key;
            candidate_count=1;
        }
        else if(candidate_count<3u) ++candidate_count;

        if(candidate_count>=3u && candidate!=stable_key)
        {
            stable_key=candidate;
            if(stable_key!=0u)
            {
                /* 同一触摸键在等待窗口内再次按下，作为双击的第二击。 */
                if(pending_key==stable_key &&
                   (uint16_t)(now-pending_time)<TOUCH_DOUBLE_TIME)
                {
                    second_click=1;
                }
                else
                {
                    /* 换键时，前一个待定点击立即确认为单击。 */
                    if(pending_key!=0u)
                    {
                        if(touch_count[pending_key-1u]<99u)
                            ++touch_count[pending_key-1u];
                        shown_key=pending_key;
                        shown_type=13;          /* D: single */
                        pending_key=0;
                    }
                    second_click=0;
                }
                press_key=stable_key;
                press_start=repeat_time=now;
                long_active=0;
            }
            else if(press_key!=0u)
            {
                if(!long_active)
                {
                    if(second_click)
                    {
                        uint8_t room=(uint8_t)(99u-touch_count[press_key-1u]);
                        touch_count[press_key-1u]+=(room>=5u)?5u:room;
                        shown_key=press_key;
                        shown_type=28;          /* S: double */
                        pending_key=0;
                    }
                    else
                    {
                        /* 第一击先等待窗口结束，避免过早报告单击。 */
                        pending_key=press_key;
                        pending_time=now;
                    }
                }
                press_key=0;
                second_click=0;
            }
        }
    }

    /* 等待窗口内没有第二击，至此才确认一次单击。 */
    if(pending_key!=0u && stable_key==0u &&
       (uint16_t)(now-pending_time)>=TOUCH_DOUBLE_TIME)
    {
        if(touch_count[pending_key-1u]<99u) ++touch_count[pending_key-1u];
        shown_key=pending_key;
        shown_type=13;                          /* D: single */
        pending_key=0;
    }

    /* 长按满0.5秒后，此后每0.5秒为当前触摸键加1。 */
    if(stable_key!=0u && (uint16_t)(now-press_start)>=TOUCH_HALF_SECOND)
    {
        /* 第二击演变成长按时，之前的第一击仍按一次单击结算。 */
        if(second_click && pending_key!=0u)
        {
            if(touch_count[pending_key-1u]<99u) ++touch_count[pending_key-1u];
            pending_key=0;
            second_click=0;
        }
        while((uint16_t)(now-repeat_time)>=TOUCH_HALF_SECOND)
        {
            repeat_time=(uint16_t)(repeat_time+TOUCH_HALF_SECOND);
            if(touch_count[stable_key-1u]<99u) ++touch_count[stable_key-1u];
        }
        long_active=1;
        shown_key=stable_key;
        shown_type=21;                          /* L */
    }

    if(shown_key==0u)
    {
        /* 上电/未触摸时给出明确的正常待机显示。 */
        p[0]=0;
        p[1]=13;                              /* D */
        p[2]=0;
        p[3]=0;
    }
    else
    {
        p[0]=shown_key;
        p[1]=shown_type;
        p[2]=(uint8_t)(touch_count[shown_key-1u]/10u);
        p[3]=(uint8_t)(touch_count[shown_key-1u]%10u);
    }
}

void TMR_INT_Handler()
{
    static uint8_t app_tick_divider=0;

    /* 1ms刷新一位，四位完整刷新周期4ms，每位刷新率约250Hz。 */
    display_seg(&seg_index);

    /* 普通键、触摸计时仍保持原来的4ms业务节拍。 */
    if(++app_tick_divider<4u) return;
    app_tick_divider=0;

    ++touch_time_4ms;
    touch_sample_due=1;
    key_scan_due=1;

}
