/**
 * @file interrupt_E.c
 * @author Jan Choutka (CHO0178)
 * @brief  tento program seznámí studenta s problematikou přerušení a principem využívání blokujících a neblokujících funkcí.
 * @version 0.1
 * @date 2026-05-15
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "littleHelper.h"
#include "MKL25Z4.h"
#include "wdog.h"
#include "led.h"
#include "btn.h"

/*
pinout(str. 161)

PORT (CH11)
	PCR[32]
		ISF
		IRQC
		MUX
	ISFR

GPIO (CH41)
	PDOR
*/

/*
CZ: postupne spoustejte funkce z main nebo z handleru dle postupu:
EN: sequentially execute functions from main or from the handler according to the procedure:

// Blocking function = B
// Non blocking function = NB

1) main: B,NB	handler: -
2) main: NB		handler: B
3) main: -		handler: B,NB
4) main: NB		handler: B
5)	CZ: pouzijte spravnou variantu a upravte kod tak, aby fungoval bez pouziti tlacitka 1
	EN: use the correct variant and modify the code to work without using button 1
*/

void blockingFunctionExample();
void nonBlockingFunctionExample();

// CZ: vyzkousejte co se stane pokud pouzijete blokovací a neblokovaci funkce v
// ruznych kombinacich jako bezici funkci nebo preruseni a popiste jaky maji vliv
// EN: try different combination of functions as base function and interrupt
// function and describe what do you see


int main(void)
{
	wdog_init(WDOG_CONF_DIS);
	led_init();
	btn_init();

	// CZ: povol prijem preruseni pro port A a nastav prioritu na 2
	// EN: enable processing of incoming interrupt signal from port A and set priority 2
	
	
	// CZ: povol generovani preruseni v periferii port A pro sestupnou hranu tlačítka 1
	// EN: enable generating interrupt signal in port A for falling edge of button 1
	
	while (1) {
		wdog_refresh();
		// CZ: zavolej funkci
		// EN: call function

	}

	return 0;
}

void PORTA_IRQHandler(void)
{
	// CZ: vynuluj flag
	// EN: reset flag
	
	// CZ: zavolej funkci
	// EN: call function

}


void blockingFunctionExample()
{
	//wait
	heavyFunction();

	// CZ: zapni diodu 1 a vypni diodu 2 na LED bargrafu
	// EN: turn on diode 1 and turn off diode 2 on LED bargraf

	//wait
	heavyFunction();

	// CZ: zapni diodu 2 a vypni diodu 1 na LED bargrafu
	// EN: turn on diode 2 and turn off diode 1 on LED bargraf


}

void nonBlockingFunctionExample()
{
	// CZ: pokud je tlacitko 2 sepnute rozsvit diodu 3 na LED bargrafu
	// EN: if button 2 is pushed turn on diode 3 on LED bargraf

}


