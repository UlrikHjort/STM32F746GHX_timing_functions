/*
 * Ulrik Hørlyk Hjort 2018
 *
 */

#include "timing.h"

void dwt_access_enable_func(unsigned ena) {
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
