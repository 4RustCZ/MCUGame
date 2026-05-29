#include <MKL25Z4.h>
#include "MySysTick.h"

void MySysTick_init(MySysTick *mySysTick){
    SysTick->LOAD = mySysTick->maxVal;
    SysTick->VAL = mySysTick->currentVal;
    SysTick->CTRL = mySysTick->control;
}

void MySysTick_start(void){
    SysTick->CTRL |= 1;
}

void MySysTick_stop(void){
    SysTick->CTRL &= ~1;
}

void MySysTick_reset(void){
    SysTick->VAL = 0;
}

unsigned int MySysTick_getVal(void){
    return SysTick->VAL;
}