/* 
 * File:   Seg_driver.h
 * Author: zjl
 *
 * Created on August 26, 2026, 9:18 PM
 */

#ifndef SEG_DRIVER_H
#define	SEG_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

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

void print_seg(char *n);
void display_seg(uint8_t *select_place);

#ifdef	__cplusplus
}
#endif

#endif	/* SEG_DRIVER_H */

