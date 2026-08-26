#include "mcc_generated_files/system/system.h"
#include "Seg_driver.h"

extern uint8_t p[4];

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
            Dig_4_SetHigh();
            Dig_1_SetLow(); 
            break;
        case 1:
            Dig_1_SetHigh();
            Dig_2_SetLow();
            break;
        case 2:
            Dig_2_SetHigh();
            Dig_3_SetLow();
            break;
        case 3:
            Dig_3_SetHigh();
            Dig_4_SetLow();
            break;
    }
    LATA = seg_table[p[*select_place]];
    if (++(*select_place) > 3)
    {
        *select_place = 0;
    }
    return;
}
