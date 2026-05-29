/**
 * @file MyBargraph.h
 * @brief 8-LED bargraph display helpers using MyArduino GPIO wrappers.
 * @authors LowGamik + 4RustCZ
 */

#ifndef MYBARGRAPH_H
#define MYBARGRAPH_H

#include "MyArduino.h"

/**
 * @brief Single bargraph LED pin and port assignment.
 */
typedef struct {
    int pin;
    Ports port;
} MyBargraph_LED;

/**
 * @brief Bargraph controller state.
 */
typedef struct {
    MyBargraph_LED leds[8];
} MyBargraph;

/**
 * @brief Initialize the bargraph LEDs.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param leds     Array of 8 LED pin/port mappings.
 */
void MyBargraph_init(MyBargraph *bargraph, MyBargraph_LED *leds);

/**
 * @brief Run a simple hardware test by lighting each LED briefly.
 *
 * @param bargraph Pointer to the bargraph state structure.
 */
void MyBargraph_testHW(MyBargraph *bargraph);

/**
 * @brief Set the state of a single bargraph LED.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param state    Desired pin state.
 * @param ledID    LED index from 1 to 8.
 */
void MyBargraph_setLED(MyBargraph *bargraph, PinState state, int ledID);

/**
 * @brief Set all bargraph LEDs to a given state.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param state    Desired pin state.
 */
void MyBargraph_setALL(MyBargraph *bargraph, PinState state);

/**
 * @brief Turn off a single bargraph LED.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param ledID    LED index from 1 to 8.
 */
void MyBargraph_clearLED(MyBargraph *bargraph, int ledID);

/**
 * @brief Turn off all bargraph LEDs.
 *
 * @param bargraph Pointer to the bargraph state structure.
 */
void MyBargraph_clearALL(MyBargraph *bargraph);

/**
 * @brief Blink all LEDs on the bargraph.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param count    Number of blink cycles.
 * @param delay_ms Delay between state changes in milliseconds.
 */
void MyBargraph_blinkALL(MyBargraph *bargraph, int count, int delay_ms);

/**
 * @brief Blink a single LED on the bargraph.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param ledID    LED index from 1 to 8.
 * @param count    Number of blink cycles.
 * @param delay_ms Delay between state changes in milliseconds.
 */
void MyBargraph_blinkLED(MyBargraph *bargraph, int ledID, int count, int delay_ms);

/**
 * @brief Blink two LEDs on the bargraph simultaneously.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param ledID1   First LED index from 1 to 8.
 * @param ledID2   Second LED index from 1 to 8.
 * @param count    Number of blink cycles.
 * @param delay_ms Delay between state changes in milliseconds.
 */
void MyBargraph_blink2LEDS(MyBargraph *bargraph, int ledID1, int ledID2, int count, int delay_ms);

/**
 * @brief Display a binary score on the bargraph.
 *
 * @param bargraph Pointer to the bargraph state structure.
 * @param score    Score value to display as binary.
 */
void MyBargraph_showScore(MyBargraph *bargraph, int score);

#endif