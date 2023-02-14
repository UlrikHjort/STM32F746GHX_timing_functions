/*
 * Ulrik Hørlyk Hjort 2018
 *
 */

#ifndef INC_TIMING_H_
#define INC_TIMING_H_
#include "stm32f7xx_hal.h"

#if !defined DWT_LSR_Present_Msk
    #define DWT_LSR_Present_Msk ITM_LSR_Present_Msk
#endif
#if !defined DWT_LSR_Access_Msk
    #define DWT_LSR_Access_Msk ITM_LSR_Access_Msk
#endif
#define DWT_LAR_KEY 0xC5ACCE55

void dwt_access_enable(unsigned ena);

#define reset_cnt() { \
    CoreDebug->DEMCR |= 0x01000000; \
    DWT->CYCCNT = 0; \
    DWT->CTRL = 0; \
}

#define start_cnt() { \
DWT->CTRL |= 0x00000001; \
}

#define stop_cnt() { \
 DWT->CTRL &= 0xFFFFFFFE; \
 }

#define getCycles() (DWT->CYCCNT)
#define dwt_access_enable()


#define TIME_MEASURE_S(func)                                               \
{                                                                          \
    dwt_access_enable(1);                                                  \
    reset_cnt();                                                           \
    start_cnt();                                                           \
    func;                                                                  \
    stop_cnt();                                                            \
    printf(#func ": %.2fs\r\n",(double)getCycles()/HAL_RCC_GetHCLKFreq()); \
}


#define TIME_MEASURE_MS(func)                                              \
{                                                                          \
    dwt_access_enable(1);                                                  \
    reset_cnt();                                                           \
    start_cnt();                                                           \
    func;                                                                  \
    stop_cnt();                                                            \
    printf(#func ": %.2fms\r\n",(double)getCycles()/HAL_RCC_GetHCLKFreq() * 1000.0); \
}


#define TIME_MEASURE_US(func)                                              \
{                                                                          \
    dwt_access_enable(1);                                                  \
    reset_cnt();                                                           \
    start_cnt();                                                           \
    func;                                                                  \
    stop_cnt();                                                            \
    printf(#func ": %.2fus\r\n",(double)getCycles()/HAL_RCC_GetHCLKFreq() * 1000000.0); \
}


#define TIME_MEASURE_NS(func)                                              \
{                                                                          \
    dwt_access_enable(1);                                                  \
    reset_cnt();                                                           \
    start_cnt();                                                           \
    func;                                                                  \
    stop_cnt();                                                            \
    printf(#func ": %.2fns\r\n",(double)getCycles()/HAL_RCC_GetHCLKFreq() * 1000000000.0); \
}

#define TIME_MEASURE_CYCLES(func)                                          \
{                                                                          \
    dwt_access_enable(1);                                                  \
    reset_cnt();                                                           \
    start_cnt();                                                           \
    func;                                                                  \
    stop_cnt();                                                            \
    printf(#func ": %u cycles\r\n",getCycles());                           \
}


#endif /* INC_TIMING_H_ */
