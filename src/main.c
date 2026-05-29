/*
 * 	Name: main.c
 * 	Author: LowGamik + 4RustCZ
 *
 * 	This is a stub. Write your code here.
 *	
 */
#include "MyArduino.h"
#include "MyRGB.h"
#include "MyBargraph.h"
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
int myRandom(int min, int max);
void showSimon(int count, int* array, MyBargraph *bargraph);
unsigned long seed;

MyBargraph_LED leds[8] = {{8,B},{9,B},{10,B},{11,B},{10,C},{11,C},{12,C},{13,C}};


__attribute__ ((weak)) int main(void)
{
	MyRGB myRGB;
	MyBargraph myBargraph;

	int array[MAX_COUNT];
	GameState gameState = WAITING;
	int simonCount = 0;
	int correct = 0;
	unsigned int points = 0;

	wdog_init(WDOG_CONF_DIS);
	initPins();
	initSysTick();
	MyRGB_init(&myRGB, 18, B, 19, B, 1, D);
	MyBargraph_init(&myBargraph, leds);

	MyBargraph_testHW(&myBargraph);
	MyRGB_test(&myRGB);

	for(int i = 0; i < MAX_COUNT; i++){
		array[i] = 0;
	}

	while (1) {
		if(gameState==WAITING){
			MyRGB_set(&myRGB,ON,ON,OFF);
			
			if(digitalRead(4,A)||digitalRead(5,A)||digitalRead(12,A)||digitalRead(13,A)){
				seed = SysTick->VAL;
				MyBargraph_clearALL(&myBargraph);
				points=0;
				gameState = SHOWING;
			}
		}

		if(gameState == SHOWING){
			MyRGB_set(&myRGB,OFF,ON,OFF);
			simonCount++;

			if(simonCount > MAX_COUNT){
				gameState = WON;
				continue;
			}

			array[simonCount-1] = myRandom(1,4);

			showSimon(simonCount, array, &myBargraph);
			
			gameState = ANSWERING;
		}

		if(gameState == ANSWERING){
			MyRGB_set(&myRGB,OFF,OFF,ON);
			
			if(digitalRead(4,A)){
				if(array[correct] == 1){
					correct++;
					MyBargraph_blink2LEDS(&myBargraph,1,2,1,500);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(digitalRead(5,A)){
				if(array[correct] == 2){
					correct++;
					MyBargraph_blink2LEDS(&myBargraph,3,4,1,500);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(digitalRead(12,A)){
				if(array[correct] == 3){
					correct++;
					MyBargraph_blink2LEDS(&myBargraph,5,6,1,500);
				}else{
					correct = 0;
					gameState = LOST;
				}
			}

			if(digitalRead(13,A)){
				if(array[correct] == 4){
					correct++;
					MyBargraph_blink2LEDS(&myBargraph,7,8,1,500);
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
			MyBargraph_showScore(&myBargraph, points);
			MyRGB_blink(&myRGB,ON,OFF,OFF,4);

			simonCount = 0;
			correct = 0;
			gameState = WAITING;
		}

		if(gameState == WON){
			MyBargraph_showScore(&myBargraph, points);
			MyRGB_blink(&myRGB,ON,ON,ON,4);

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


void showSimon(int count, int* array, MyBargraph *myBargraph){
	for(int i = 0; i < count; i++){
		switch (array[i])
		{
		case 1:
			MyBargraph_blink2LEDS(myBargraph,1,2,1,500);
			break;
		case 2:
			MyBargraph_blink2LEDS(myBargraph,3,4,1,500);
			break;
		case 3:
			MyBargraph_blink2LEDS(myBargraph,5,6,1,500);
			break;
		case 4:
			MyBargraph_blink2LEDS(myBargraph,7,8,1,500);
			break;
		default:
			break;
		}
	}
}