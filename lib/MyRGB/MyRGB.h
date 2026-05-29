/**
 * @file MyRGB.h
 * @brief RGB LED helper functions using MyArduino GPIO wrappers.
 * @authors LowGamik + 4RustCZ
 */

#ifndef MyRGB_h
#define MyRGB_h

#include "MyArduino.h"

/**
 * @brief RGB LED pin mapping.
 */
typedef struct {
    int redPin;
    Ports redPort;
    int greenPin;
    Ports greenPort;
    int bluePin;
    Ports bluePort;
} MyRGB;

/**
 * @brief Initialize RGB LED pins.
 *
 * @param myRGB      Pointer to the RGB state structure.
 * @param redPin     Red LED pin number.
 * @param redPort    Red LED port.
 * @param greenPin   Green LED pin number.
 * @param greenPort  Green LED port.
 * @param bluePin    Blue LED pin number.
 * @param bluePort   Blue LED port.
 */
void MyRGB_init(MyRGB *myRGB, int redPin, Ports redPort, int greenPin, Ports greenPort, int bluePin, Ports bluePort);

/**
 * @brief Set the RGB LED output state.
 *
 * @param myRGB  Pointer to the RGB state structure.
 * @param red    Red channel state.
 * @param green  Green channel state.
 * @param blue   Blue channel state.
 */
void MyRGB_set(MyRGB *myRGB, PinState red, PinState green, PinState blue);

/**
 * @brief Turn off all RGB channels.
 *
 * @param myRGB  Pointer to the RGB state structure.
 */
void MyRGB_clear(MyRGB *myRGB);

/**
 * @brief Blink the RGB LED with a fixed color.
 *
 * @param myRGB  Pointer to the RGB state structure.
 * @param red    Red channel state.
 * @param green  Green channel state.
 * @param blue   Blue channel state.
 * @param count  Number of blink cycles.
 */
void MyRGB_blink(MyRGB *myRGB, PinState red, PinState green, PinState blue, int count);

/**
 * @brief Perform a hardware test on the RGB LED.
 *
 * @param myRGB  Pointer to the RGB state structure.
 */
void MyRGB_test(MyRGB *myRGB);

#endif