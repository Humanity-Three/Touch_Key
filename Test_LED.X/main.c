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
#include "Seg_driver.h"

uint8_t charcase=0;		//预留/暂存单元(本程序未使用)
uint8_t p[4]={0};           //数码管4位显示的值(0~9 数字, 10~35 字母 A~Z)
uint8_t select_place=0; //位选第几位数码管
uint16_t sys_tic=0;     //全局可看的系统时钟(16 位: sys_tick 低字节, sys_tick+1 高字节)
uint8_t i=0;
uint8_t key_data=0;     //保存按下时 PORTC 低 4 位数据(供状态机比较)
uint8_t key_cnt=0;      //按键状态机通用计数(进入各状态清零)
uint8_t key_state=0;    //按键状态机状态(bit0-2=0~5, bit7=1 双击消抖)

typedef enum button_state{
    st_idle,
    st_debounce,
    st_down,
    st_long_active,
    st_wait_double,
    st_double_active
}BUTTON_STATE;



//处理按键中断
void button_react(void)
{
    LED_Toggle();  
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
            print_seg("Err"); 
        }
        else
        {
            key_data = PORTC & 0x0F;
            key_cnt = 0;
            key_state = st_debounce;
        }
        return;
    }
    else 
    {
        
    }
}

void Handle_Timer0(void)
{
    sys_tic++;
    buttons_state();
    display_seg(&select_place);  
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
    
    print_seg("zsr");
   
    while(1)
    {
    }    
}