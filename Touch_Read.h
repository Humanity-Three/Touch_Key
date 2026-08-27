/* 
 * File:   Touch_Read.h
 * Author: u2024
 *
 * Created on August 26, 2026, 7:34 PM
 */

#ifndef TOUCH_READ_H
#define	TOUCH_READ_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif

static void adcc_discharge_and_switch(uint8_t ch);
uint16_t Touch_Read_Avg(uint8_t ch);
uint8_t Scan_Touch(void);
#ifdef	__cplusplus
}
#endif

#endif	/* TOUCH_READ_H */
