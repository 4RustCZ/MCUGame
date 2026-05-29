/**
 * @file MySysTick.h
 * @brief Simple SysTick timer configuration helpers.
 */

#ifndef MYSYSTICK_H
#define MYSYSTICK_H

/**
 * @brief SysTick configuration parameters.
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