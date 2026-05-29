/**
 * @file MyArduino.h
 * @brief Arduino-inspired GPIO utilities for the MKL25Z4 MCU.
 * @authors LowGamik + 4RustCZ
 */

#ifndef MYARDUINO_H
#define MYARDUINO_H

/**
 * @brief GPIO pin direction.
 */
typedef enum {
    INPUT = 0,
    OUTPUT = 1
} PinType;

/**
 * @brief MCU port identifiers.
 */
typedef enum {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4
} Ports;

/**
 * @brief Logical pin states.
 */
typedef enum {
    OFF = 0,
    ON = 1
} PinState;

/**
 * @brief Configure a GPIO pin as input or output.
 *
 * @param pin   Pin number on the selected port.
 * @param port  Port identifier.
 * @param mode  INPUT or OUTPUT.
 */
void pinMode(int pin, Ports port, PinType mode);

/**
 * @brief Set a GPIO pin state.
 *
 * @param pin    Pin number on the selected port.
 * @param port   Port identifier.
 * @param state  OFF to drive the pin high, ON to drive it low.
 */
void digitalWrite(int pin, Ports port, PinState state);

/**
 * @brief Read a digital input pin.
 *
 * @param pin   Pin number on the selected port.
 * @param port  Port identifier.
 * @return Non-zero if the pin is active, zero otherwise.
 */
int digitalRead(int pin, Ports port);

/**
 * @brief Busy-wait delay loop.
 *
 * @param ms  Delay duration in milliseconds.
 */
void myDelay(unsigned long ms);

#endif