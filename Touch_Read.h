#ifndef TOUCH_READ_H
#define TOUCH_READ_H

#include <stdint.h>

int16_t Touch_CVD_Read(uint8_t channel);
int16_t Touch_CVD_Read_Avg(uint8_t channel);
void Touch_Calibrate(void);
uint16_t Touch_CalculateThreshold(void);
uint8_t Scan_Touch(void);

#endif
