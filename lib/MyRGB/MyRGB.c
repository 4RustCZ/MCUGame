#include "MyRGB.h"
#include "MyArduino.h"

void MyRGB_init(MyRGB *myRGB, int redPin, Ports redPort, int greenPin, Ports greenPort, int bluePin, Ports bluePort){
    pinMode(redPin, redPort, OUTPUT);
    pinMode(greenPin, greenPort, OUTPUT);
    pinMode(bluePin, bluePort, OUTPUT);

    myRGB->redPin = redPin;
    myRGB->redPort = redPort;
    myRGB->greenPin = greenPin;
    myRGB->greenPort = greenPort;
    myRGB->bluePin = bluePin;
    myRGB->bluePort = bluePort;
}

void MyRGB_set(MyRGB *myRGB, PinState red, PinState green, PinState blue){
    digitalWrite(myRGB->redPin,myRGB->redPort,red);
    digitalWrite(myRGB->greenPin,myRGB->greenPort,green);
    digitalWrite(myRGB->bluePin,myRGB->bluePort,blue);
}

void MyRGB_clear(MyRGB *myRGB){
    MyRGB_set(myRGB,OFF,OFF,OFF);
}

void MyRGB_blink(MyRGB *myRGB, PinState red, PinState green, PinState blue, int count){
    for(int i = 0; i < count; i++){
        MyRGB_set(myRGB,red,green,blue);
        myDelay(500);
        MyRGB_clear(myRGB);
        myDelay(500);
    }
}

void MyRGB_test(MyRGB *myRGB){
    MyRGB_blink(myRGB,ON,OFF,OFF,1);
    MyRGB_blink(myRGB,OFF,ON,OFF,1);
    MyRGB_blink(myRGB,OFF,OFF,ON,1);
}