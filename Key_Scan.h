/* 
 * File:   Key_Scan.h
 * Author: u2024
 *
 * Created on August 26, 2026, 8:41 PM
 */

#ifndef KEY_SCAN_H
#define	KEY_SCAN_H
#include "stdint.h"
#ifdef	__cplusplus
extern "C" {
#endif


uint8_t Scan_All_Keys(void);
uint8_t key(const uint8_t level, const uint8_t kv);
#ifdef	__cplusplus
}
#endif

#endif	/* KEY_SCAN_H */



