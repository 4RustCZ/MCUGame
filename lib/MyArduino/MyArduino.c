#include <MKL25Z4.h>
#include "MyArduino.h"

void pinMode(int pin, Ports port, PinType mode){
    switch(mode) {
        case INPUT:
            switch (port)
            {
            case A:
                PORTA->PCR[pin] |= 1 << 8;
                GPIOA->PDDR &= ~(1 << pin);
                break;
            case B:
                PORTB->PCR[pin] |= 1 << 8;
                GPIOB->PDDR &= ~(1 << pin);
                break;
            case C:
                PORTC->PCR[pin] |= 1 << 8;
                GPIOC->PDDR &= ~(1 << pin);
                break;
            case D:
                PORTD->PCR[pin] |= 1 << 8;
                GPIOD->PDDR &= ~(1 << pin);
                break;
            case E:
                PORTE->PCR[pin] |= 1 << 8;
                GPIOE->PDDR &= ~(1 << pin);
                break;
            default:
                break;
            }
            break;
        case OUTPUT:
            switch(port){
            case A:
                PORTA->PCR[pin] |= 1 << 8;
                GPIOA->PDDR |= 1 << pin;
                break;
            case B:
                PORTB->PCR[pin] |= 1 << 8;
                GPIOB->PDDR |= 1 << pin;
                break; 
            case C:
                PORTC->PCR[pin] |= 1 << 8;
                GPIOC->PDDR |= 1 << pin;
                break;
            case D:
                PORTD->PCR[pin] |= 1 << 8;
                GPIOD->PDDR |= 1 << pin;
                break;
            case E:
                PORTE->PCR[pin] |= 1 << 8;
                GPIOE->PDDR |= 1 << pin;
                break;
            }
            break;
    }
}

void digitalWrite(int pin, Ports port, PinState state){
    switch(port){
        case A:
            if(state == OFF){
                GPIOA->PDOR |= 1 << pin;
            } else {
                GPIOA->PDOR &= ~(1 << pin);
            }
            break;
        case B:
            if(state == OFF){
                GPIOB->PDOR |= 1 << pin;
            } else {
                GPIOB->PDOR &= ~(1 << pin);
            }
            break; 
        case C:
            if(state == OFF){
                GPIOC->PDOR |= 1 << pin;
            } else {
                GPIOC->PDOR &= ~(1 << pin);
            }
            break;
        case D:
            if(state == OFF){
                GPIOD->PDOR |= 1 << pin;
            } else {
                GPIOD->PDOR &= ~(1 << pin);
            }
            break;
        case E:
            if(state == OFF){
                GPIOE->PDOR |= 1 << pin;
            } else {
                GPIOE->PDOR &= ~(1 << pin);
            }
            break;
    }
}

int digitalRead(int pin, Ports port){
    switch(port){
        case A:
            return !((GPIOA->PDIR >> pin) & 1);
        case B:
            return !((GPIOB->PDIR >> pin) & 1);
        case C:
            return !((GPIOB->PDIR >> pin) & 1);
        case D:
            return !((GPIOB->PDIR >> pin) & 1);
        case E:
            return !((GPIOB->PDIR >> pin) & 1);
    }
    return -1; // Invalid port
}

void myDelay(unsigned long ms){
    for (unsigned long i = 0; i < ms; i++){
        for(int j = 0; j < 5000; j++){
            __NOP();
        }
    }
    
}