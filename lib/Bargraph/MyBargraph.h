#ifndef MYBARGRAPH_H
#define MYBARGRAPH_H

#include "MyArduino.h"

typedef struct{
    int pin;
    Ports port;
}MyBargraph_LED;

typedef struct{
    MyBargraph_LED leds[8];
}MyBargraph;

void MyBargraph_init(MyBargraph *bargraph, MyBargraph_LED *leds);
void MyBargraph_testHW(MyBargraph *bargraph);
void MyBargraph_setLED(MyBargraph *bargraph, PinState state, int ledID);
void MyBargraph_setALL(MyBargraph *bargraph, PinState state);
void MyBargraph_clearLED(MyBargraph *bargraph, int ledID);
void MyBargraph_clearALL(MyBargraph *bargraph);
void MyBargraph_blinkALL(MyBargraph *bargraph, int count, int delay_ms);
void MyBargraph_blinkLED(MyBargraph *bargraph, int ledID, int count, int delay_ms);
void MyBargraph_blink2LEDS(MyBargraph *bargraph, int ledID1, int ledID2, int count, int delay_ms);
void MyBargraph_showScore(MyBargraph *bargraph, int score);

#endif