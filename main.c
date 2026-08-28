#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/nvm/nvm.h"
#include "mcc_generated_files/uart/eusart.h"
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
static void Uart_Send_Data(uint8_t data);
static void Uart_Send_Data_N(uint8_t data, uint8_t n);
static void Uart_Send_Data3(uint8_t c1, uint8_t c2, uint8_t c3);
static void UART_Rx_Process(void);
static void Touch_On_Single(uint8_t key);
static void Touch_On_Double(uint8_t key);
static void Touch_On_LongRepeat(uint8_t key);
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

/* UART 数据模式：0=输入模式，1=输出模式 */
enum UART_MODE
{
    MODE_IN=0U,
    MODE_OUT=1U,
    MODE_CAP=2U
};
static uint8_t uart_mode=MODE_OUT;   /* 上电默认输出模式 */
static uint8_t tx_data=50;           /* 输出模式待发送数据（初始 50） */
static uint8_t rx_data=0;            /* 输入模式最新接收数据 */

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

/* PPS 引脚映射由 MCC 的 PIN_MANAGER_Initialize 生成：
 *   RB6PPS = 0x10（RB6 -> EUSART TX）
 *   RXPPS  = 0x0F（RB7 -> EUSART RX）
 * 因此这里不再手动配置 PPS。 */

int main(void)
{
    SYSTEM_Initialize();
    EUSART_Initialize();                     /* MCC EUSART 初始化（9600, 8N1） */
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
        UART_Rx_Process();                   /* 接收串口数据帧 */
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

        /* 键7：切换为输出模式。 */
        if(cur_key==7)
        {
            uart_mode=MODE_OUT;
            return;
        }
        /* 键8：切换为输入模式。 */
        if(cur_key==8)
        {
            uart_mode=MODE_IN;
            return;
        }
        /* 键9：输出模式下把当前数据经串口发出。 */
        if(cur_key==9)
        {
            if(uart_mode==MODE_OUT)
            {
                Uart_Send_Data(tx_data);
            }
            return;
        }
        /* 键10：进入电容读取模式（幂等，再按模式不变）。 */
        if(cur_key==10)
        {
            uart_mode=MODE_CAP;
            return;
        }

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
    static uint16_t press_start=0, repeat_time=0, pending_time=0;
    uint16_t now;

    /* 电容读取模式：每 100ms 读取当前通道电容并显示/发送三路电容帧。 */
    if(uart_mode==MODE_CAP)
    {
        static uint16_t cap_last=0;
        uint16_t cap_now;
        int16_t vals[3];
        uint8_t ch, cap;

        INTERRUPT_GlobalInterruptDisable();
        cap_now=touch_time_4ms;
        INTERRUPT_GlobalInterruptEnable();
        if((uint16_t)(cap_now-cap_last)<25u) return;   /* 100ms 节拍 */
        cap_last=cap_now;

        ch=Scan_Touch();
        if(ch==0xFFu) ch=0u;                     /* 无触摸默认通道1 */
        Touch_CVD_Read_All_Avg(vals);
        cap=(uint8_t)vals[ch];                   /* 当前通道电容值 */
        p[0]=12;                                 /* C */
        p[1]=(uint8_t)(cap/100u);
        p[2]=(uint8_t)((cap/10u)%10u);
        p[3]=(uint8_t)(cap%10u);
        Uart_Send_Data3((uint8_t)vals[0],(uint8_t)vals[1],(uint8_t)vals[2]);
        return;
    }

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
                        Touch_On_Single(pending_key);
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
                        Touch_On_Double(press_key);
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
        Touch_On_Single(pending_key);
        pending_key=0;
    }

    /* 长按满0.5秒后，此后每0.5秒为当前触摸键加1。 */
    if(stable_key!=0u && (uint16_t)(now-press_start)>=TOUCH_HALF_SECOND)
    {
        /* 第二击演变成长按时，之前的第一击仍按一次单击结算。 */
        if(second_click && pending_key!=0u)
        {
            Touch_On_Single(pending_key);
            pending_key=0;
            second_click=0;
        }
        while((uint16_t)(now-repeat_time)>=TOUCH_HALF_SECOND)
        {
            repeat_time=(uint16_t)(repeat_time+TOUCH_HALF_SECOND);
            Touch_On_LongRepeat(stable_key);
        }
        long_active=1;
    }

    /* 输出/输入模式下的数码管显示（校准态由 STATE_Operation 显示阈值）。 */
    if(uart_mode==MODE_OUT)
    {
        p[0]=24;                 /* O：输出模式 */
        p[1]=36;                 /* 空白 */
        p[2]=(uint8_t)(tx_data/10u);
        p[3]=(uint8_t)(tx_data%10u);
    }
    else
    {
        uint8_t disp=(rx_data>99u)?99u:rx_data;
        p[0]=18;                 /* I：输入模式 */
        p[1]=36;                 /* 空白 */
        p[2]=(uint8_t)(disp/10u);
        p[3]=(uint8_t)(disp%10u);
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

/* 发送一帧：0x03 | data | 0xFC */
static void Uart_Send_Data(uint8_t data)
{
    EUSART_Write(0x03u);   /* 帧头 */
    EUSART_Write(data);    /* 数据 */
    EUSART_Write(0xFCu);   /* 帧尾 */
}

/* 连续发送 n 帧：逐帧等待发完再发下一帧，避免发送缓冲溢出丢帧。 */
static void Uart_Send_Data_N(uint8_t data, uint8_t n)
{
    uint8_t i;

    for(i=0u;i<n;i++)
    {
        EUSART_Write(0x03u);   /* 帧头 */
        EUSART_Write(data);    /* 数据 */
        EUSART_Write(0xFCu);   /* 帧尾 */
        while(!EUSART_IsTxDone()) { }   /* 等本帧发完 */
    }
}

/* 发送三路触摸电容帧：0x03 | c1 | c2 | c3 | 0xFC */
static void Uart_Send_Data3(uint8_t c1, uint8_t c2, uint8_t c3)
{
    EUSART_Write(0x03u);   /* 帧头 */
    EUSART_Write(c1);      /* 触摸键 1 电容 */
    EUSART_Write(c2);      /* 触摸键 2 电容 */
    EUSART_Write(c3);      /* 触摸键 3 电容 */
    EUSART_Write(0xFCu);   /* 帧尾 */
}

/* 主循环轮询接收：解析 0x03 | data | 0xFC 帧，data 供输入模式显示。 */
static void UART_Rx_Process(void)
{
    static uint8_t rx_state=0;   /* 0=等帧头, 1=已收帧头, 2=已收数据 */

    while(EUSART_IsRxReady())
    {
        uint8_t b=EUSART_Read();
        if(rx_state==0u)
        {
            if(b==0x03u) rx_state=1u;
        }
        else if(rx_state==1u)
        {
            rx_data=b;              /* 保存最新数据 */
            rx_state=2u;
        }
        else /* rx_state==2u：收到帧尾或异常，回到等待帧头 */
        {
            rx_state=0u;
        }
    }
}

/* 触摸键动作：输出模式下 T1/T3 调节待发数据；其他模式维持原计数。 */
static void Touch_On_Single(uint8_t key)
{
    if(uart_mode==MODE_OUT)
    {
        if(key==1u)      tx_data=(tx_data>=99u)?99u:(uint8_t)(tx_data+1u);
        else if(key==3u) tx_data=(tx_data>=1u)?(uint8_t)(tx_data-1u):0u;
        else if(key==2u) Uart_Send_Data(tx_data);   /* T2：输出模式下短按发送当前数据 */
    }
    else
    {
        if(touch_count[key-1u]<99u) ++touch_count[key-1u];
    }
}

static void Touch_On_Double(uint8_t key)
{
    if(uart_mode==MODE_OUT)
    {
        if(key==1u)
        {
            uint16_t v=(uint16_t)tx_data+5u;
            tx_data=(v>99u)?99u:(uint8_t)v;
        }
        else if(key==3u)
        {
            uint16_t v=(tx_data>=5u)?((uint16_t)tx_data-5u):0u;
            tx_data=(uint8_t)v;
        }
        else if(key==2u) Uart_Send_Data_N(tx_data,5u);   /* T2：双击发送 5 次 */
    }
    else
    {
        uint8_t room=(uint8_t)(99u-touch_count[key-1u]);
        touch_count[key-1u]+=(room>=5u)?5u:room;
    }
}

static void Touch_On_LongRepeat(uint8_t key)
{
    if(uart_mode==MODE_OUT)
    {
        if(key==1u)      tx_data=(tx_data>=99u)?99u:(uint8_t)(tx_data+1u);
        else if(key==3u) tx_data=(tx_data>=1u)?(uint8_t)(tx_data-1u):0u;
        else if(key==2u) Uart_Send_Data(tx_data);   /* T2：长按连续发送（每 0.5s 一帧） */
    }
    else
    {
        if(touch_count[key-1u]<99u) ++touch_count[key-1u];
    }
}
