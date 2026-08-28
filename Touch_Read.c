#include "Touch_Read.h"
#include "mcc_generated_files/system/system.h"
#include <stdint.h>

#define TOUCH_CH_RC4  0x14u
#define TOUCH_CH_RC5  0x15u
#define TOUCH_CH_RC6  0x16u
#define CVD_AVG_COUNT 8u

static const uint8_t touch_channel[3] =
{
    /* 触摸键1、2、3分别接在RC4、RC5、RC6。 */
    TOUCH_CH_RC4, TOUCH_CH_RC5, TOUCH_CH_RC6
};

static int16_t touch_base[3];
static int16_t touch_pressed[3];
extern uint16_t THRESHOLD;

static uint16_t abs_diff_i16(int16_t a, int16_t b)
{
    int32_t delta=(int32_t)a-(int32_t)b;
    return (uint16_t)((delta<0)?-delta:delta);
}

int16_t Touch_CVD_Read(uint8_t channel)
{
    ADPCH=channel;

    /* ADCONT=0时，差分CVD的两个样本分别由两次软件触发完成。 */
    ADCON0bits.ADGO=1;
    while(ADCON0bits.GO_nDONE)
    {
    }

    ADCON0bits.ADGO=1;
    while(ADCON0bits.GO_nDONE)
    {
    }

    return (int16_t)ADERR;
}

int16_t Touch_CVD_Read_Avg(uint8_t channel)
{
    int32_t sum=0;
    uint8_t i;

    for(i=0;i<CVD_AVG_COUNT;i++) sum+=Touch_CVD_Read(channel);
    return (int16_t)(sum/(int32_t)CVD_AVG_COUNT);
}

void Touch_Calibrate(void)
{
    uint8_t i;
    uint8_t n;

    for(i=0;i<3u;i++)
    {
        int32_t sum=0;
        for(n=0;n<4u;n++) (void)Touch_CVD_Read(touch_channel[i]);
        for(n=0;n<8u;n++) sum+=Touch_CVD_Read_Avg(touch_channel[i]);
        touch_base[i]=(int16_t)(sum/8);
    }
}

uint16_t Touch_CalculateThreshold(void)
{
    uint16_t max_delta=0;
    uint8_t i;

    for(i=0;i<3u;i++)
    {
        uint16_t delta;
        touch_pressed[i]=Touch_CVD_Read_Avg(touch_channel[i]);
        delta=abs_diff_i16(touch_pressed[i],touch_base[i]);
        if(delta>max_delta) max_delta=delta;
    }

    if(max_delta<4u) return 0u;
    max_delta=(uint16_t)(max_delta/2u);
    return (max_delta==0u)?1u:max_delta;
}

uint8_t Scan_Touch(void)
{
    uint8_t best=0xFFu;
    uint16_t best_delta=0;
    uint16_t press_threshold;
    uint8_t i;

    /* 标定阈值约为实际触摸变化量的一半；提高按下门限形成迟滞，
       防止空闲漂移刚超过THRESHOLD后被持续误判成长按。 */
    press_threshold=(THRESHOLD>43690u)?65535u:
                    (uint16_t)(THRESHOLD+THRESHOLD/2u);

    for(i=0;i<3u;i++)
    {
        int16_t value=Touch_CVD_Read_Avg(touch_channel[i]);
        uint16_t delta=abs_diff_i16(value,touch_base[i]);

        if(delta>press_threshold)
        {
            if(best==0xFFu || delta>best_delta)
            {
                best=i;
                best_delta=delta;
            }
        }
        else if(delta<(uint16_t)(THRESHOLD/4u+1u))
        {
            int32_t tracked=(int32_t)touch_base[i]*31+(int32_t)value;
            touch_base[i]=(int16_t)(tracked/32);
        }
    }

    return best;
}

/* 读取三个触摸通道的 CVD 差分读数（各 8 次平均），供串口上报电容大小。 */
void Touch_CVD_Read_All_Avg(int16_t values[3])
{
    uint8_t i;

    for(i=0;i<3u;i++)
    {
        values[i]=Touch_CVD_Read_Avg(touch_channel[i]);
    }
}

/* 一次采样同时返回三路原始读数（values）与相对各自基线的差值（deltas）。
 * deltas = |当前值 - 基线|，未按下时约为 0，按下时对应通道增大。 */
void Touch_CVD_Read_All_Avg_Delta(int16_t values[3], uint16_t deltas[3])
{
    uint8_t i;

    for(i=0;i<3u;i++)
    {
        int16_t value=Touch_CVD_Read_Avg(touch_channel[i]);
        values[i]=value;
        deltas[i]=abs_diff_i16(value,touch_base[i]);
    }
}
