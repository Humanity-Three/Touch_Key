#ifndef TOUCH_READ_H
#define TOUCH_READ_H

#include <stdint.h>

int16_t Touch_CVD_Read(uint8_t channel);
int16_t Touch_CVD_Read_Avg(uint8_t channel);
void Touch_Calibrate(void);
uint16_t Touch_CalculateThreshold(void);
uint8_t Scan_Touch(void);
void Touch_CVD_Read_All_Avg(int16_t values[3]);
void Touch_CVD_Read_All_Avg_Delta(int16_t values[3], uint16_t deltas[3]);

#endif
