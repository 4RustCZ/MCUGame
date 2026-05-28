#include <littleHelper.h>
#include "wdog.h"
#include "MKL25Z4.h"

#include "soc_def.h"
#include "res_alloc.h"

#include "wdog.h"
#include "led.h"
#include "sin_lut.h"

// compare trig
/*
DAC
	DAT0L
		DATA0			lower data pro převod
	DAT0H
		DATA1			higher data pro převod
	C0
		DACEN			povolena použití 12bit DAC
CMP
	DACCR
		DACEN			povolení napájení vnitřního DAC
		VOSEL			voltage select
	MUXCR
		PSEL			multiplex to positive input of CMP
		MSEL			multiplex to negative input of CMP
	SCR
		IER				enable flag raising
		CFR				flag interruptu
	CR1
		OPE				enable output
		EN				enable power for CMP
*/

#define PIT_EXPT_PRI		2u
#define CMP_EXPT_PRI		2u
#define PIT0_MOD			3000ul
#define DAC0_DAT0			(*((volatile uint16_t *) 0x4003F000ul))
#define CMP_EXPT_CNT_MOD	50u


uint16_t sin_lut_ind, cmp_expt_cnt, disp_cnt;
const uint16_t sin_lut[SIN_LUT_DATA_LEN] = {SIN_LUT_DATA};

void setupNVICandPIT();


int main(void)
{
	wdog_init(WDOG_CONF_LPOCLK_1024_CYCLES);
	led_init();
	setupNVICandPIT();

	// Povolte použití 12bit DAC
	
	// Přepněte multiplex v periferii port tak, aby přesměroval signál z BNC konektoru J15 na výstup periferie CMP0
	
	// Přepněte multiplex v periferii port tak, aby přesměroval signál z výstupu DAC na BNC konektor
	
	// Nastavte periferii CMP tak aby výstupní hodnota VOSEL byla 0x20u a nastavte napájení interního DAC periferie
	
	// Nastavte vstupní multiplexory na kladný vstup periferii DAC0 a záporný vstup signál DAC periferie CMP
	
	// Povol flag raising v periferii CMP
	
	// Povol výstup a napájení periferie CMP


	while (1) {
		wdog_refresh();
	}

	return 0;
}


void setupNVICandPIT()
{
	NVIC_SetPriority(PIT_IRQn, PIT_EXPT_PRI);
	NVIC_EnableIRQ(PIT_IRQn);

	NVIC_SetPriority(CMP0_IRQn, PIT_EXPT_PRI);
	NVIC_EnableIRQ(CMP0_IRQn);

	PIT->MCR = PIT_MCR_FRZ_MASK;
	PIT->CHANNEL[0u].LDVAL = PIT0_MOD - 1u;
	PIT->CHANNEL[0u].TCTRL = PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;

}


void __attribute__ ((interrupt)) PIT_IRQHandler(void)
{
	PIT->CHANNEL[0u].TFLG = PIT_TFLG_TIF_MASK;

	DAC0_DAT0 = sin_lut[sin_lut_ind];

	sin_lut_ind++;
	if (sin_lut_ind == SIN_LUT_DATA_LEN) {
		sin_lut_ind = 0;
	}
}

void __attribute__ ((interrupt)) CMP0_IRQHandler(void)
{
	// proveďte vynulování vyhozeného flagu (dejte si pozor abyste nevynulovali povolení flagů)

	// čtěte počet vyvolaných interruptů a každých 50 volání zvětšit výstup na diodě o 1


}
