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
#include "Touch_Read.h"
#include "Key_Scan.h"
#include "Seg_driver.h"

/*
    Main application
*/
 void TMR_INT_Handler(void);
 uint8_t p[4]={36,36,36,36};
//状态机枚举定义
 enum STATE
{
    STATE_IDLE=0U,
    STATE_CORRECT=1U,
    STATE_DISPLAY=2U,
    //STATE_DEBOUNCE=3U,
    //STATE_DOWN=4U,
   // STATE_LONG_ACTIVE=5U,
   // STATE_DOUBLE_WAIT=6U,
    //STATE_DOUBLE_ACTIVE=7U
};
static uint8_t level_tmp=0;
static uint8_t seg_index = 0;
static enum STATE current_state=STATE_IDLE;
static enum STATE next_state=STATE_IDLE;
uint16_t THRESHOLD=500;
uint8_t Key_Value=0;
int main(void)
{
    SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 
    TMR0_PeriodMatchCallbackRegister(TMR_INT_Handler);
    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 

    uint8_t Touch_Channel=0;
    char tmp[4]={0};
    while(1)
    {
        //print_seg("Err");
        //display_seg(&seg_index);
        level_tmp=Scan_All_Keys(); 
        //uint16_t Diff = Compare_Touch_Channel(500,15);
        //Touch_Channel=Scan_Touch();
       // Num2Str(Touch_Channel,tmp);
        //print_seg(tmp);
        p[0]=key(level_tmp,Key_Value);
        //Num2Str(Touch_Read_Avg(0x14U), tmp);   // 用手摸 RC4，看数字变不变、变多少
        print_seg(tmp);
    }    
    return 0;
}

//状态更新函数
void STATE_Update()
{
    switch(current_state)
    {
        case STATE_IDLE:
            
            break;    
        case STATE_CORRECT:
            
            break;
        case STATE_DISPLAY:
            
            break;
    }
}
void STATE_Operation()
{
     switch(current_state)
    {
        case STATE_IDLE:
            
            break;    
        case STATE_CORRECT:
            
            break;
        case STATE_DISPLAY:
            
            break;
       
    }
}
void TMR_INT_Handler()
{   
   
    display_seg(&seg_index);
    //TMR0_Reload();
    
}


