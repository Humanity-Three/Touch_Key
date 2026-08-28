#include "mcc_generated_files/system/system.h"
#include "Seg_driver.h"
#include "stdint.h"
extern uint8_t p[4];   // 数码管显示缓冲区（4位）

void print_seg(char *n)
{
    for (int i = 0; i < 4; i++)
    {
        char data = *(n+i);
        if (data <= '9' && data >= '0') data -= 48;
        else if (data <= 'Z' && data >= 'A') data -= 55;
        else if (data <= 'z' && data >= 'a') data -= 87;
        else data = 36;
        p[i] = data;
    }
}

void display_seg(uint8_t *select_place)
{
    uint8_t place=*select_place;

    /* 先关闭全部位选，避免切换段码时上一位或下一位被瞬间点亮。 */
    IO_RB0_SetHigh();
    IO_RB1_SetHigh();
    IO_RB2_SetHigh();
    IO_RB3_SetHigh();

    /* 位选仍关闭时更新段码，再只打开当前一位。 */
    LATA = seg_table[p[place]];

    switch (place)
    {
        case 0:
            IO_RB0_SetLow();
            break;
        case 1:
            IO_RB1_SetLow();
            break;
        case 2:
            IO_RB2_SetLow();
            break;
        case 3:
            IO_RB3_SetLow();
            break;
        default:
            place=0;
            IO_RB0_SetLow();
            break;
    }

    *select_place=(uint8_t)((place+1u)&0x03u);
    return;
}

void Num2Str(uint16_t num, char *buf)   
{
    buf[3] = '0' + (num % 10);   num /= 10;
    buf[2] = '0' + (num % 10);   num /= 10;
    buf[1] = '0' + (num % 10);   num /= 10;
    buf[0] = '0' + (num % 10);
}
