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
    switch (*select_place)
    {
        case 0:
            //Dig_4_SetHigh();
            IO_RB3_SetHigh();
            //Dig_1_SetLow();
            IO_RB0_SetLow();
            break;
        case 1:
           // Dig_1_SetHigh();
            IO_RB0_SetHigh();
           // Dig_2_SetLow();
            IO_RB1_SetLow();
            break;
        case 2:
            //Dig_2_SetHigh();
            IO_RB1_SetHigh();
            //Dig_3_SetLow();
            IO_RB2_SetLow();
            break;
        case 3:
           // Dig_3_SetHigh();
            IO_RB2_SetHigh();
           // Dig_4_SetLow();
            IO_RB3_SetLow();
            break;
    }
    LATA = seg_table[p[*select_place]];
    if (++(*select_place) > 3)
    {
        *select_place = 0;
    }
    return;
}

void Num2Str(uint16_t num, char *buf)   
{
    buf[3] = '0' + (num % 10);   num /= 10;
    buf[2] = '0' + (num % 10);   num /= 10;
    buf[1] = '0' + (num % 10);   num /= 10;
    buf[0] = '0' + (num % 10);
}
