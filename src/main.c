/*
 * 	Name: main.c
 * 	Author: You
 *
 * 	This is a stub. Write your code here.
 *	fuh nah
 */
#include "MyArduino.h"
#include "MKL25Z4.h"
#include "wdog.h"
#include "littleHelper.h"

#define MAX_COUNT 3

typedef enum {
	WAITING,
	SHOWING,
	ANSWERING,
	LOST,
	WON
}GameState;

void initPins(void);
//void initNVIC(void);
//void initTPM(void);
void initSysTick(void);
//void buttonHandler(void);
int myRandom(int min, int max);
void showSimon(int count, int* array);
void setRGB(PinState RED, PinState GREEN, PinState BLUE);
void blinkRGB(PinState R, PinState G, PinState B, int count);
void blink2LEDS(int pin1, Ports port1, int pin2, Ports port2, int count);
unsigned long seed;


__attribute__ ((weak)) int main(void)
{
	int array[MAX_COUNT];
	GameState gameState = WAITING;
	int simonCount = 0;
	int correct = 0;
	unsigned int points = 0;

	wdog_init(WDOG_CONF_DIS); // this fuh ass thing
	initPins();
	initSysTick();

	for(int i = 0; i < MAX_COUNT; i++){
		array[i] = 0;
	}

	while (1) {
		if(gameState==WAITING){
			setRGB(ON,ON,OFF);
			if(!(GPIOA->PDIR & (1 << 4))){
				seed = SysTick->VAL;
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

			for(int i = 0; i < simonCount; i++){
				array[i] = myRandom(1, 4);
			}

			showSimon(simonCount, array);
			
			gameState = ANSWERING;
		}

		if(gameState == ANSWERING){
			setRGB(OFF,OFF,ON);
			
			if(!(GPIOA->PDIR & (1 << 4))){
				if(array[correct] == 1){
					correct++;
					blink2LEDS(8,B,9,B,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(!(GPIOA->PDIR & (1 << 5))){
				if(array[correct] == 2){
					correct++;
					blink2LEDS(10,B,11,B,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(!(GPIOA->PDIR & (1 << 12))){
				if(array[correct] == 3){
					correct++;
					blink2LEDS(10,C,11,C,1);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(!(GPIOA->PDIR & (1 << 13))){
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
			blinkRGB(ON,OFF,OFF,4);

			simonCount = 0;
			correct = 0;
			gameState = WAITING;
		}

		if(gameState == WON){
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

/*void initNVIC(void){
	// Initialize NVIC (Nested Vectored Interrupt Controller)
	NVIC_SetPriority(PORTA_IRQn, 2);
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_SetVector(PORTA_IRQn, (uint32_t)buttonHandler);
}*/

/*void initTPM(void){
	TPM0->MOD = 255;
	TPM0->CONTROLS[2].CnSC |= 0b1010 << 2;
	TPM0->CONTROLS[2].CnV = 128;
	TPM0->SC |= 0b101 << 3;
}*/

void initSysTick(void){
	SysTick->LOAD = 0xFFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 0b101;
}

/*void buttonHandler(void){
	if(gameState == WAITING){
		gameState = PLAYING;
		seed = SysTick->VAL;
	}
}*/

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
			heavyFunction();
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
		heavyFunction();
		setRGB(OFF,OFF,OFF);
		heavyFunction();
	}
}

void blink2LEDS(int pin1, Ports port1, int pin2, Ports port2, int count){
	for(int i = 0; i < count; i++){
		digitalWrite(pin1,port1,ON);
		digitalWrite(pin2,port2,ON);
		heavyFunction();
		digitalWrite(pin1,port1,OFF);
		digitalWrite(pin2,port2,OFF);
		heavyFunction();
	}
}