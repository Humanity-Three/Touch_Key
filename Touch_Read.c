#include "Touch_Read.h"
#include "mcc_generated_files/system/interrupt.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/system/config_bits.h"
#include "stdint.h"

#define TOUCH_CH_RC4  0x14u
#define TOUCH_CH_RC5  0x15u
#define TOUCH_CH_RC6  0x16u
#define CH_AVSS       0x3Cu 

static uint16_t touch_base[3];
extern uint16_t THRESHOLD;

static void adcc_discharge_and_switch(uint8_t ch)
{
    ADPCH = CH_AVSS;
    ADCON0bits.GO = 1;
    while (ADCON0bits.GO_nDONE) {}
    ADPCH = ch;
    ADCON0bits.GO = 1;          /* 目标通道也让一次采样动作/充电稳定 */
    while (ADCON0bits.GO_nDONE) {}
}

uint16_t Touch_Read_Avg(uint8_t ch)
{
    static const uint8_t N = 16;
    uint32_t sum = 0;
    uint8_t i;
    adcc_discharge_and_switch(ch);            /* 放电 + 换通道 → 避免串扰 */
    for (i = 0; i < N; i++)
    {
        ADPCH = ch;
        ADCON0bits.GO = 1;
        while (ADCON0bits.GO_nDONE) {}
        sum += ((uint16_t)ADRESH << 8) | ADRESL;
    }
    return (uint16_t)(sum / N);
}

uint8_t Scan_Touch(void)   /* 返回按下的通道下标 0~2，无键返回 0xFF */
{
    const uint8_t ch_map[3] = {TOUCH_CH_RC4, TOUCH_CH_RC5, TOUCH_CH_RC6};
    uint8_t i;
    for (i = 0; i < 3; i++)
    {
        uint16_t v = Touch_Read_Avg(ch_map[i]);
        int16_t delta = (int16_t)v - (int16_t)touch_base[i];
        if (delta > THRESHOLD)         /* 负数说明采样电压下降，方向看你实测定正负 */
            return i;
    }
    return 0xFF;
}