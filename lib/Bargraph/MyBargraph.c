#include "MyBargraph.h"
#include "MyArduino.h"

void MyBargraph_init(MyBargraph *bargraph, MyBargraph_LED *leds){
    for(int i = 0; i < 8; i++){
        bargraph->leds[i] = leds[i];
    }

    for(int i = 0; i < 8; i++){
        pinMode(bargraph->leds[i].pin, bargraph->leds[i].port, OUTPUT);
    }

    MyBargraph_clearALL(bargraph);
}

void MyBargraph_testHW(MyBargraph *bargraph){
    for(int i = 0; i < 8; i++){
        digitalWrite(bargraph->leds[i].pin, bargraph->leds[i].port, ON);
        myDelay(500);
    }
    MyBargraph_clearALL(bargraph);
}

void MyBargraph_setLED(MyBargraph *bargraph, PinState state, int ledID){
    if(ledID < 1 || ledID > 8){
        return;
    }
    digitalWrite(bargraph->leds[ledID-1].pin, bargraph->leds[ledID-1].port, state);
}

void MyBargraph_setALL(MyBargraph *bargraph, PinState state){
    for(int i = 0; i < 8; i++){
        digitalWrite(bargraph->leds[i].pin, bargraph->leds[i].port, state);
    }
}

void MyBargraph_clearLED(MyBargraph *bargraph, int ledID){
    if(ledID < 1 || ledID > 8){
        return;
    }
    digitalWrite(bargraph->leds[ledID-1].pin, bargraph->leds[ledID-1].port, OFF);
}

void MyBargraph_clearALL(MyBargraph *bargraph){
    for(int i = 0; i < 8; i++){
        digitalWrite(bargraph->leds[i].pin, bargraph->leds[i].port, OFF);
    }
}

void MyBargraph_blinkALL(MyBargraph *bargraph, int count, int delay_ms){
    for(int i = 0; i < count; i++){
        MyBargraph_setALL(bargraph, ON);
        myDelay(delay_ms);
        MyBargraph_setALL(bargraph, OFF);
        myDelay(delay_ms);
    }
}

void MyBargraph_blinkLED(MyBargraph *bargraph, int ledID, int count, int delay_ms){
    for(int i = 0; i < count; i++){
        MyBargraph_setLED(bargraph, ON, ledID);
        myDelay(delay_ms);
        MyBargraph_setLED(bargraph, OFF, ledID);
        myDelay(delay_ms);
    }
}

void MyBargraph_blink2LEDS(MyBargraph *bargraph, int ledID1, int ledID2, int count, int delay_ms){
    for(int i = 0; i < count; i++){
        MyBargraph_setLED(bargraph, ON, ledID1);
        MyBargraph_setLED(bargraph, ON, ledID2);
        myDelay(delay_ms);
        MyBargraph_setLED(bargraph, OFF, ledID1);
        MyBargraph_setLED(bargraph, OFF, ledID2);
        myDelay(delay_ms);
    }
}

void MyBargraph_showScore(MyBargraph *bargraph, int score){
    int val[8];
    for (int i = 0; i < 8; i++){
        val[i] = score%2;
        score /= 2;
    }

    for(int i = 8; i >= 1; i--){
        MyBargraph_setLED(bargraph, val[i-1], 9-i);
    }
    
}