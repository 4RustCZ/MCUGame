#ifndef MyRGB_h
#define MyRGB_h

#include "MyArduino.h"

typedef struct{
    int redPin;
    Ports redPort;
    int greenPin;
    Ports greenPort;
    int bluePin;
    Ports bluePort;
}MyRGB;


void MyRGB_init(MyRGB *myRGB, int redPin, Ports redPort, int greenPin, Ports greenPort, int bluePin, Ports bluePort);
void MyRGB_set(MyRGB *myRGB, PinState red, PinState green, PinState blue);
void MyRGB_clear(MyRGB *myRGB);
void MyRGB_blink(MyRGB *myRGB, PinState red, PinState green, PinState blue, int count);
void MyRGB_test(MyRGB *myRGB);

#endif