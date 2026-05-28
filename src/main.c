/*
 * 	Name: main.c
 * 	Author: LowGamik + 4RustCZ
 *
 * 	This is a stub. Write your code here.
 *	
 */
#include "MyArduino.h"
#include "MKL25Z4.h"
#include "wdog.h"
#include "littleHelper.h"

#define MAX_COUNT 32

typedef enum {
	WAITING,
	SHOWING,
	ANSWERING,
	LOST,
	WON
}GameState;

void initPins(void);
void initSysTick(void);
void testHWBG(void);
void testHWRGB(void);
int myRandom(int min, int max);
void showSimon(int count, int* array);
void setRGB(PinState RED, PinState GREEN, PinState BLUE);
void blinkRGB(PinState R, PinState G, PinState B, int count);
void blink2LEDS(int pin1, Ports port1, int pin2, Ports port2, int count);
void barGraphScore(int points);
void barGraphClear(void);
unsigned long seed;


__attribute__ ((weak)) int main(void)
{
	int array[MAX_COUNT];
	GameState gameState = WAITING;
	int simonCount = 0;
	int correct = 0;
	unsigned int points = 0;

	wdog_init(WDOG_CONF_DIS);
	initPins();
	initSysTick();

	testHWBG();
	testHWRGB();

	for(int i = 0; i < MAX_COUNT; i++){
		array[i] = 0;
	}

	while (1) {
		if(gameState==WAITING){
			setRGB(ON,ON,OFF);
			if(!(GPIOA->PDIR & (1 << 4))){
				seed = SysTick->VAL;
				barGraphClear();
				points=0;
				gameState = SHOWING;
			}
		}

		if(gameState == SHOWING){
			setRGB(OFF,ON,OFF);
			simonCount++;

			if(simonCount > MAX_COUNT){
				gameState = WON;
				continue;
			}

			array[simonCount-1] = myRandom(1,4);

			showSimon(simonCount, array);
			
			gameState = ANSWERING;
		}

		if(gameState == ANSWERING){
			setRGB(OFF,OFF,ON);
			
			if(digitalRead(4,A)){
				if(array[correct] == 1){
					correct++;
					blink2LEDS(8,B,9,B,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(digitalRead(5,A)){
				if(array[correct] == 2){
					correct++;
					blink2LEDS(10,B,11,B,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(digitalRead(12,A)){
				if(array[correct] == 3){
					correct++;
					blink2LEDS(10,C,11,C,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(digitalRead(13,A)){
				if(array[correct] == 4){
					correct++;
					blink2LEDS(12,C,13,C,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(correct == simonCount){
				points++;
				correct = 0;
				gameState = SHOWING;
			}
		}	

		if(gameState == LOST){
			barGraphScore(points);
			blinkRGB(ON,OFF,OFF,4);

			simonCount = 0;
			correct = 0;
			gameState = WAITING;
		}

		if(gameState == WON){
			barGraphScore(points);
			blinkRGB(ON,ON,ON,4);

			simonCount = 0;
			correct = 0;
			gameState = WAITING;
		}
	}

	return 0;
}

void initPins(void){
	//buttons
	pinMode(4, A, INPUT);
	pinMode(5, A, INPUT);
	pinMode(12, A, INPUT);
	pinMode(13, A, INPUT);
	//bargraph
	pinMode(8, B, OUTPUT);
	pinMode(9, B, OUTPUT);
	pinMode(10, B, OUTPUT);
	pinMode(11, B, OUTPUT);
	pinMode(10, C, OUTPUT);
	pinMode(11, C, OUTPUT);
	pinMode(12, C, OUTPUT);
	pinMode(13, C, OUTPUT);
	//bargraph off
	digitalWrite(8, B, OFF);
	digitalWrite(9, B, OFF);
	digitalWrite(10, B, OFF);
	digitalWrite(11, B, OFF);
	digitalWrite(10, C, OFF);
	digitalWrite(11, C, OFF);
	digitalWrite(12, C, OFF);
	digitalWrite(13, C, OFF);
	//RGB
	pinMode(18,B,OUTPUT);
	pinMode(19,B,OUTPUT);
	pinMode(1,D,OUTPUT);
	//RGB OFF
	digitalWrite(18,B,OFF);
	digitalWrite(19,B,OFF);
	digitalWrite(1,D,OFF);
}

void initSysTick(void){
	SysTick->LOAD = 0xFFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0b101;
}


int myRandom(int min, int max){
	seed = (seed * 1103515245 + 12345) & 0x7fffffff; // Linear Congruential Generator

	unsigned int n = (unsigned int)(seed /65536);

	return (n % (max - min + 1)) + min;
}


void showSimon(int count, int* array){
	for(int i = 0; i < count; i++){
		switch (array[i])
		{
		case 1:
			blink2LEDS(8,B,9,B,1);
			break;
		case 2:
			blink2LEDS(10,B,11,B,1);
			break;
		case 3:
			blink2LEDS(10,C,11,C,1);
			break;
		case 4:
			blink2LEDS(12,C,13,C,1);
			break;
		default:
			break;
		}
	}
}

void setRGB(PinState RED, PinState GREEN, PinState BLUE){
	digitalWrite(18,B,RED);
	digitalWrite(19,B,GREEN);
	digitalWrite(1,D,BLUE);
}

void blinkRGB(PinState R, PinState G, PinState B, int count){
	for(int i = 0; i < count; i++){
		setRGB(R,G,B);
		myDelay(500);
		setRGB(OFF,OFF,OFF);
		myDelay(500);
	}
}

void blink2LEDS(int pin1, Ports port1, int pin2, Ports port2, int count){
	for(int i = 0; i < count; i++){
		digitalWrite(pin1,port1,ON);
		digitalWrite(pin2,port2,ON);
		myDelay(500);
		digitalWrite(pin1,port1,OFF);
		digitalWrite(pin2,port2,OFF);
		myDelay(500);
	}
}

void barGraphScore(int points){
	int val[8];

	for(int i = 0; i < 8; i++){
		val[i] = points%2;
		points/=2;
	}

	digitalWrite(8, B, val[7]);
	digitalWrite(9, B, val[6]);
	digitalWrite(10, B, val[5]);
	digitalWrite(11, B, val[4]);
	digitalWrite(10, C, val[3]);
	digitalWrite(11, C, val[2]);
	digitalWrite(12, C, val[1]);
	digitalWrite(13, C, val[0]);
}

void barGraphClear(void){
	digitalWrite(8, B, OFF);
	digitalWrite(9, B, OFF);
	digitalWrite(10, B, OFF);
	digitalWrite(11, B, OFF);
	digitalWrite(10, C, OFF);
	digitalWrite(11, C, OFF);
	digitalWrite(12, C, OFF);
	digitalWrite(13, C, OFF);
}

void testHWBG(void){
	digitalWrite(8, B, ON);
	myDelay(200);
	digitalWrite(9, B, ON);
	myDelay(200);
	digitalWrite(10, B, ON);
	myDelay(200);
	digitalWrite(11, B, ON);
	myDelay(200);
	digitalWrite(10, C, ON);
	myDelay(200);
	digitalWrite(11, C, ON);
	myDelay(200);
	digitalWrite(12, C, ON);
	myDelay(200);
	digitalWrite(13, C, ON);
	myDelay(200);
	barGraphClear();
}

void testHWRGB(void){
	blinkRGB(ON,OFF,OFF,1);
	blinkRGB(OFF,ON,OFF,1);
	blinkRGB(OFF,OFF,ON,1);
}