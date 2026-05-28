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

typedef enum {
	WAITING,
	PLAYING
}GameState;

void initPins(void);
//void initNVIC(void);
//void initTPM(void);
void initSysTick(void);
//void buttonHandler(void);
int myRandom(int min, int max);

int array[8] = {0,0,0,0,0,0,0,0};
int simonCount = 0;
unsigned long seed;
GameState gameState = WAITING;

__attribute__ ((weak)) int main(void)
{
	
	

	wdog_init(WDOG_CONF_DIS); // this fuh ass thing
	initPins();
	//initNVIC();
	//initTPM();
	initSysTick();

	while (1) {
		while((GPIOA->PDIR & (1 << 4))&&(gameState == 0)){
			seed = SysTick->VAL;
		}

		gameState = 1;

		simonCount = myRandom(1, 4);

		switch (simonCount)
		{
		case 1:
			digitalWrite(8,B,ON);
			digitalWrite(9,B,ON);
			heavyFunction();
			digitalWrite(8,B,OFF);
			digitalWrite(9,B,OFF);
			heavyFunction();
			break;
		case 2:
			digitalWrite(10,B,ON);
			digitalWrite(11,B,ON);
			heavyFunction();
			digitalWrite(10,B,OFF);
			digitalWrite(11,B,OFF);
			heavyFunction();
			break;
		case 3:
			digitalWrite(10,C,ON);
			digitalWrite(11,C,ON);
			heavyFunction();
			digitalWrite(10,C,OFF);
			digitalWrite(11,C,OFF);
			heavyFunction();
			break;
		case 4:
			digitalWrite(12,C,ON);
			digitalWrite(13,C,ON);
			heavyFunction();
			digitalWrite(12,C,OFF);
			digitalWrite(13,C,OFF);
			heavyFunction();
		default:
			break;
		}
	}

	return 0;
}

void initPins(void){
	pinMode(4, A, INPUT);
	pinMode(8, B, OUTPUT);
	pinMode(9, B, OUTPUT);
	pinMode(10, B, OUTPUT);
	pinMode(11, B, OUTPUT);
	pinMode(10, C, OUTPUT);
	pinMode(11, C, OUTPUT);
	pinMode(12, C, OUTPUT);
	pinMode(13, C, OUTPUT);

	digitalWrite(8, B, OFF);
	digitalWrite(9, B, OFF);
	digitalWrite(10, B, OFF);
	digitalWrite(11, B, OFF);
	digitalWrite(10, C, OFF);
	digitalWrite(11, C, OFF);
	digitalWrite(12, C, OFF);
	digitalWrite(13, C, OFF);
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
	SysTick->CTRL |= 0b111;
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