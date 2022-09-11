/*
 * Ulrik Hørlyk Hjort 2018
 *
 */

#include "timing.h"

void reset_cnt() {
    CoreDebug->DEMCR |= 0x01000000;
    DWT->CYCCNT = 0;
    DWT->CTRL = 0;
}

void start_cnt() { DWT->CTRL |= 0x00000001;}

void stop_cnt() {  DWT->CTRL &= 0xFFFFFFFE;}

unsigned int getCycles() { return DWT->CYCCNT;}

void dwt_access_enable(unsigned ena) {
    uint32_t lsr = DWT->LSR;;

    if( (lsr & DWT_LSR_Present_Msk) != 0 ) {
        if( ena ) {
            if ((lsr & DWT_LSR_Access_Msk) != 0) {
                DWT->LAR = DWT_LAR_KEY;
            }
        }
        else {
            if ((lsr & DWT_LSR_Access_Msk) == 0) {
                DWT->LAR = 0;
            }
        }
    }
}
