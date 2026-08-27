#include "mcc_generated_files/system/system.h"
#include "Key_Scan.h"
#include "Seg_driver.h"
static uint8_t level=0x00;
static uint8_t number_of_zero=0x00;
extern uint8_t Key_Value;

extern uint8_t p[4];
/*
 level=0x0F;
 Key_Value=PORTC&level;
  number_of_zero=Key_Value^level&(Key_Value-1);
 * if(Key_Value==level)
 * {
 *      TRISC=TRISC&(0xF0)^(level/2);
 *      break;
 * }
 * else if(!number_of_zero)
 * {
 *      return Key_Value;
 * }
 * else 
 * {
 *      return error;
 * }
 */
uint8_t Scan_All_Keys(void)
{
    char C_tmp[4]={0};
    //寄存器配置
    TRISC=TRISC&(0xF0)^0x0F;
    Key_Value=0;//PORTC&0x0F;
    for(level=0x0F;level>=1;level=level/2)
    {
    Key_Value=PORTC&level;
     number_of_zero=(Key_Value^level)&((Key_Value^level)-1);
    if(Key_Value==level)
    {
       TRISC=TRISC&(0xF0)^(level/2);
    }
    else if(!number_of_zero)
    { 
      return level;
    }
    else 
    {
     print_seg("Err");
     return 0;
    }      
    }
    return 0;
}
/* level:0x01/0x03/0x07/0x0F，kv:同一级读到的 Key_Value
 * 返回 1..10；无键返回 0 */
uint8_t key(const uint8_t level, const uint8_t kv)
{
    uint8_t f = (level & ~kv) & 0x0F;                 /* 按下位 2^n */
    uint8_t c = (level & 8) ? 4 : (level & 4) ? 3
             : (level & 2) ? 2 : 1;                   /* 通道数 */
    uint8_t i = (f & 8) ? 3 : (f & 4) ? 2
             : (f & 2) ? 1 : 0;                       /* 按下位序号 */
    return (uint8_t)(c * (c - 1) / 2 + 1 + i);        /* 1..10 */
}