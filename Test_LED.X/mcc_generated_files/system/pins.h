/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
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

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define Seg_a_TRIS                 TRISAbits.TRISA0
#define Seg_a_LAT                  LATAbits.LATA0
#define Seg_a_PORT                 PORTAbits.RA0
#define Seg_a_WPU                  WPUAbits.WPUA0
#define Seg_a_OD                   ODCONAbits.ODCA0
#define Seg_a_ANS                  ANSELAbits.ANSA0
#define Seg_a_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define Seg_a_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define Seg_a_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define Seg_a_GetValue()           PORTAbits.RA0
#define Seg_a_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define Seg_a_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define Seg_a_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define Seg_a_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define Seg_a_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define Seg_a_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define Seg_a_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define Seg_a_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define Seg_b_TRIS                 TRISAbits.TRISA1
#define Seg_b_LAT                  LATAbits.LATA1
#define Seg_b_PORT                 PORTAbits.RA1
#define Seg_b_WPU                  WPUAbits.WPUA1
#define Seg_b_OD                   ODCONAbits.ODCA1
#define Seg_b_ANS                  ANSELAbits.ANSA1
#define Seg_b_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define Seg_b_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define Seg_b_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define Seg_b_GetValue()           PORTAbits.RA1
#define Seg_b_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define Seg_b_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define Seg_b_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define Seg_b_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define Seg_b_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define Seg_b_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define Seg_b_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define Seg_b_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define Seg_c_TRIS                 TRISAbits.TRISA2
#define Seg_c_LAT                  LATAbits.LATA2
#define Seg_c_PORT                 PORTAbits.RA2
#define Seg_c_WPU                  WPUAbits.WPUA2
#define Seg_c_OD                   ODCONAbits.ODCA2
#define Seg_c_ANS                  ANSELAbits.ANSA2
#define Seg_c_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define Seg_c_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define Seg_c_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define Seg_c_GetValue()           PORTAbits.RA2
#define Seg_c_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define Seg_c_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define Seg_c_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define Seg_c_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define Seg_c_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define Seg_c_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define Seg_c_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define Seg_c_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA3 aliases
#define Seg_d_TRIS                 TRISAbits.TRISA3
#define Seg_d_LAT                  LATAbits.LATA3
#define Seg_d_PORT                 PORTAbits.RA3
#define Seg_d_WPU                  WPUAbits.WPUA3
#define Seg_d_OD                   ODCONAbits.ODCA3
#define Seg_d_ANS                  ANSELAbits.ANSA3
#define Seg_d_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define Seg_d_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define Seg_d_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define Seg_d_GetValue()           PORTAbits.RA3
#define Seg_d_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define Seg_d_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define Seg_d_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define Seg_d_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define Seg_d_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define Seg_d_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define Seg_d_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define Seg_d_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)
// get/set IO_RA4 aliases
#define Seg_e_TRIS                 TRISAbits.TRISA4
#define Seg_e_LAT                  LATAbits.LATA4
#define Seg_e_PORT                 PORTAbits.RA4
#define Seg_e_WPU                  WPUAbits.WPUA4
#define Seg_e_OD                   ODCONAbits.ODCA4
#define Seg_e_ANS                  ANSELAbits.ANSA4
#define Seg_e_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define Seg_e_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define Seg_e_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define Seg_e_GetValue()           PORTAbits.RA4
#define Seg_e_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define Seg_e_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define Seg_e_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define Seg_e_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define Seg_e_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define Seg_e_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define Seg_e_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define Seg_e_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define Seg_f_TRIS                 TRISAbits.TRISA5
#define Seg_f_LAT                  LATAbits.LATA5
#define Seg_f_PORT                 PORTAbits.RA5
#define Seg_f_WPU                  WPUAbits.WPUA5
#define Seg_f_OD                   ODCONAbits.ODCA5
#define Seg_f_ANS                  ANSELAbits.ANSA5
#define Seg_f_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define Seg_f_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define Seg_f_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define Seg_f_GetValue()           PORTAbits.RA5
#define Seg_f_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define Seg_f_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define Seg_f_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define Seg_f_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define Seg_f_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define Seg_f_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define Seg_f_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define Seg_f_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RA6 aliases
#define Seg_g_TRIS                 TRISAbits.TRISA6
#define Seg_g_LAT                  LATAbits.LATA6
#define Seg_g_PORT                 PORTAbits.RA6
#define Seg_g_WPU                  WPUAbits.WPUA6
#define Seg_g_OD                   ODCONAbits.ODCA6
#define Seg_g_ANS                  ANSELAbits.ANSA6
#define Seg_g_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define Seg_g_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define Seg_g_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define Seg_g_GetValue()           PORTAbits.RA6
#define Seg_g_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define Seg_g_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define Seg_g_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define Seg_g_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define Seg_g_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define Seg_g_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define Seg_g_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define Seg_g_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)
// get/set IO_RA7 aliases
#define Seg_dp_TRIS                 TRISAbits.TRISA7
#define Seg_dp_LAT                  LATAbits.LATA7
#define Seg_dp_PORT                 PORTAbits.RA7
#define Seg_dp_WPU                  WPUAbits.WPUA7
#define Seg_dp_OD                   ODCONAbits.ODCA7
#define Seg_dp_ANS                  ANSELAbits.ANSA7
#define Seg_dp_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define Seg_dp_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define Seg_dp_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define Seg_dp_GetValue()           PORTAbits.RA7
#define Seg_dp_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define Seg_dp_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define Seg_dp_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define Seg_dp_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define Seg_dp_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define Seg_dp_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define Seg_dp_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define Seg_dp_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)
// get/set IO_RB0 aliases
#define Dig_1_TRIS                 TRISBbits.TRISB0
#define Dig_1_LAT                  LATBbits.LATB0
#define Dig_1_PORT                 PORTBbits.RB0
#define Dig_1_WPU                  WPUBbits.WPUB0
#define Dig_1_OD                   ODCONBbits.ODCB0
#define Dig_1_ANS                  ANSELBbits.ANSB0
#define Dig_1_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define Dig_1_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define Dig_1_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define Dig_1_GetValue()           PORTBbits.RB0
#define Dig_1_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define Dig_1_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define Dig_1_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define Dig_1_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define Dig_1_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define Dig_1_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define Dig_1_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define Dig_1_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)
// get/set IO_RB1 aliases
#define Dig_2_TRIS                 TRISBbits.TRISB1
#define Dig_2_LAT                  LATBbits.LATB1
#define Dig_2_PORT                 PORTBbits.RB1
#define Dig_2_WPU                  WPUBbits.WPUB1
#define Dig_2_OD                   ODCONBbits.ODCB1
#define Dig_2_ANS                  ANSELBbits.ANSB1
#define Dig_2_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define Dig_2_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define Dig_2_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define Dig_2_GetValue()           PORTBbits.RB1
#define Dig_2_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define Dig_2_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define Dig_2_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define Dig_2_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define Dig_2_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define Dig_2_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define Dig_2_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define Dig_2_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)
// get/set IO_RB2 aliases
#define Dig_3_TRIS                 TRISBbits.TRISB2
#define Dig_3_LAT                  LATBbits.LATB2
#define Dig_3_PORT                 PORTBbits.RB2
#define Dig_3_WPU                  WPUBbits.WPUB2
#define Dig_3_OD                   ODCONBbits.ODCB2
#define Dig_3_ANS                  ANSELBbits.ANSB2
#define Dig_3_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define Dig_3_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define Dig_3_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define Dig_3_GetValue()           PORTBbits.RB2
#define Dig_3_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define Dig_3_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define Dig_3_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define Dig_3_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define Dig_3_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define Dig_3_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define Dig_3_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define Dig_3_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)
// get/set IO_RB3 aliases
#define Dig_4_TRIS                 TRISBbits.TRISB3
#define Dig_4_LAT                  LATBbits.LATB3
#define Dig_4_PORT                 PORTBbits.RB3
#define Dig_4_WPU                  WPUBbits.WPUB3
#define Dig_4_OD                   ODCONBbits.ODCB3
#define Dig_4_ANS                  ANSELBbits.ANSB3
#define Dig_4_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define Dig_4_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define Dig_4_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define Dig_4_GetValue()           PORTBbits.RB3
#define Dig_4_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define Dig_4_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define Dig_4_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define Dig_4_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define Dig_4_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define Dig_4_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define Dig_4_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define Dig_4_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)
// get/set IO_RB4 aliases
#define LED_TRIS                 TRISBbits.TRISB4
#define LED_LAT                  LATBbits.LATB4
#define LED_PORT                 PORTBbits.RB4
#define LED_WPU                  WPUBbits.WPUB4
#define LED_OD                   ODCONBbits.ODCB4
#define LED_ANS                  ANSELBbits.ANSB4
#define LED_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LED_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LED_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LED_GetValue()           PORTBbits.RB4
#define LED_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LED_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LED_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
// get/set IO_RB5 aliases
#define Button_TRIS                 TRISBbits.TRISB5
#define Button_LAT                  LATBbits.LATB5
#define Button_PORT                 PORTBbits.RB5
#define Button_WPU                  WPUBbits.WPUB5
#define Button_OD                   ODCONBbits.ODCB5
#define Button_ANS                  ANSELBbits.ANSB5
#define Button_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define Button_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define Button_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define Button_GetValue()           PORTBbits.RB5
#define Button_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define Button_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define Button_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define Button_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define Button_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define Button_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define Button_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define Button_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)
#define RB5_SetInterruptHandler  Button_SetInterruptHandler
// get/set IO_RC0 aliases
#define K_0_TRIS                 TRISCbits.TRISC0
#define K_0_LAT                  LATCbits.LATC0
#define K_0_PORT                 PORTCbits.RC0
#define K_0_WPU                  WPUCbits.WPUC0
#define K_0_OD                   ODCONCbits.ODCC0
#define K_0_ANS                  ANSELCbits.ANSC0
#define K_0_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define K_0_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define K_0_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define K_0_GetValue()           PORTCbits.RC0
#define K_0_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define K_0_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define K_0_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define K_0_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define K_0_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define K_0_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define K_0_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define K_0_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
// get/set IO_RC1 aliases
#define K_1_TRIS                 TRISCbits.TRISC1
#define K_1_LAT                  LATCbits.LATC1
#define K_1_PORT                 PORTCbits.RC1
#define K_1_WPU                  WPUCbits.WPUC1
#define K_1_OD                   ODCONCbits.ODCC1
#define K_1_ANS                  ANSELCbits.ANSC1
#define K_1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define K_1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define K_1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define K_1_GetValue()           PORTCbits.RC1
#define K_1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define K_1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define K_1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define K_1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define K_1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define K_1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define K_1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define K_1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
// get/set IO_RC2 aliases
#define K_2_TRIS                 TRISCbits.TRISC2
#define K_2_LAT                  LATCbits.LATC2
#define K_2_PORT                 PORTCbits.RC2
#define K_2_WPU                  WPUCbits.WPUC2
#define K_2_OD                   ODCONCbits.ODCC2
#define K_2_ANS                  ANSELCbits.ANSC2
#define K_2_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define K_2_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define K_2_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define K_2_GetValue()           PORTCbits.RC2
#define K_2_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define K_2_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define K_2_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define K_2_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define K_2_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define K_2_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define K_2_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define K_2_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC3 aliases
#define K_3_TRIS                 TRISCbits.TRISC3
#define K_3_LAT                  LATCbits.LATC3
#define K_3_PORT                 PORTCbits.RC3
#define K_3_WPU                  WPUCbits.WPUC3
#define K_3_OD                   ODCONCbits.ODCC3
#define K_3_ANS                  ANSELCbits.ANSC3
#define K_3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define K_3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define K_3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define K_3_GetValue()           PORTCbits.RC3
#define K_3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define K_3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define K_3_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define K_3_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define K_3_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define K_3_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define K_3_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define K_3_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the Button pin functionality
 * @param none
 * @return none
 */
void Button_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for Button pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for Button at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void Button_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for Button pin.
 *        This is a dynamic interrupt handler to be used together with the Button_SetInterruptHandler() method.
 *        This handler is called every time the Button ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*Button_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for Button pin. 
 *        This is a predefined interrupt handler to be used together with the Button_SetInterruptHandler() method.
 *        This handler is called every time the Button ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void Button_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/