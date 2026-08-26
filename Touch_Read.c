#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/system/clock.h"
#include "mcc_generated_files/system/interrupt.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/system/config_bits.h"


uint16_t Touch_Read(uint8_t channel)
{
    ADPCH=channel;
    ADCON0bits.GO=1;
    while(ADCON0bits.GO_nDONE)
    {
        return ((uint16_t)ADRESH<<8);
    }
}
