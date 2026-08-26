 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
? [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/tmr0.h"

uint8_t charcase=0;		//预留/暂存单元(本程序未使用)
uint8_t p[4]={0};           //数码管4位显示的值(0~9 数字, 10~35 字母 A~Z)
uint8_t select_place=0; //位选第几位数码管
uint16_t sys_tic=0;     //全局可看的系统时钟(16 位: sys_tick 低字节, sys_tick+1 高字节)
uint8_t i=0;
uint8_t key_data=0;     //保存按下时 PORTC 低 4 位数据(供状态机比较)
uint8_t key_cnt=0;      //按键状态机通用计数(进入各状态清零)
uint8_t key_state=0;    //按键状态机状态(bit0-2=0~5, bit7=1 双击消抖)
const uint8_t seg_table[] = {
    0x3F, // 0: a b c d e f
    0x06, // 1: b c
    0x5B, // 2: a b d e g
    0x4F, // 3: a b c d g
    0x66, // 4: b c f g
    0x6D, // 5: a c d f g
    0x7D, // 6: a c d e f g
    0x07, // 7: a b c
    0x7F, // 8: a b c d e f g
    0x6F, // 9: a b c d f g
    0x77, // A: a b c e f g
    0x7C, // b: c d e f g
    0x39, // C: a d e f
    0x5E, // d: b c d e g
    0x79, // E: a d e f g
    0x71, // F: a e f g
    0x3D, // G: a c d e f
    0x76, // H: b c e f g
    0x30, // I: b c
    0x1E, // J: b c d e
    0x75, // K: 无法完美显示，近似: a c e f g
    0x38, // L: d e f
    0x15, // M: 无法完美显示，近似: a c e
    0x37, // n: a c e g
    0x3F, // O: a b c d e f
    0x73, // P: a b e f g
    0x67, // q: a b c f g
    0x50, // r: e g
    0x6D, // S: a c d f g
    0x78, // t: d e f g
    0x3E, // U: b c d e f
    0x3E, // V: 无法完美显示，近似同U
    0x2A, // W: 无法完美显示，近似: b c f g
    0x76, // X: 无法完美显示，近似同H
    0x6E, // y: b c d f g
    0x5B,  // Z: a b d e g
    0x00  //空白
};

//处理按键中断
void button_react(void)
{
    LED_Toggle();  
}

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

//十个按键的状态机
void buttons_state(void)
{
    if (key_state)
    {
        
    }
    i = 4;
    WPUC = 0x0f;
    TRISC = 0x0F;
    
    charcase = PORTC & 0x0F;
    charcase = charcase ^ (uint8_t)((1<<i) - 1);
    if (charcase)
    {
        charcase = charcase & (charcase-1);
        if (charcase)
        {
            p[0] = 'E' - '0' - 8;
            p[1] = 'E' - '0' - 8;
            p[2] = 'E' - '0' - 8;
            
        }
    }
}

void Handle_Timer0(void)
{
    sys_tic++;
    buttons_state();
    switch (select_place)
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
    LATA = seg_table[p[select_place]];
    if (++select_place > 3)
    {
        select_place = 0;
    }
    
    
}

int main(void)
{
    SYSTEM_Initialize();
    
    TMR0_PeriodMatchCallbackRegister(Handle_Timer0);
    Button_SetInterruptHandler(button_react);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 
    
    print_seg("Err ");
   
    while(1)
    {
    }    
}