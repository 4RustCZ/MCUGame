/**
 * @file MySysTick.h
 * @brief Simple SysTick timer configuration helpers.
 * @authors LowGamik + 4RustCZ
 */

#ifndef MYSYSTICK_H
#define MYSYSTICK_H

/**
 * @brief SysTick configuration parameters.
 * 
 * @param maxVal Maximum value of the SysTick counter.
 * @param currentVal Current value of the SysTick counter.
 * @param control SysTick control register value.  3 bits, first controls if external or internal processor clock is used. second bit controls if interrupt is enabled. third bit controls if SysTick is enabled.
 */
typedef struct {
    unsigned int maxVal;
    unsigned int currentVal;
    char control;
} MySysTick;

/**
 * @brief Initialize the SysTick timer.
 *
 * @param mySysTick Pointer to the SysTick configuration.
 */
void MySysTick_init(MySysTick *mySysTick);

/**
 * @brief Start the SysTick timer.
 */
void MySysTick_start(void);

/**
 * @brief Stop the SysTick timer.
 */
void MySysTick_stop(void);

/**
 * @brief Reset the SysTick current count value.
 */
void MySysTick_reset(void);

/**
 * @brief Get the current SysTick counter value.
 *
 * @return Current SysTick VAL register value.
 */
unsigned int MySysTick_getVal(void);

#endif