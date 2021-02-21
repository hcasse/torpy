/**
 *	Torpy - grid-follower wheeling and box delivering bot.
 *	Copyright (C) 2021  Université de Toulouse <casse@irit.fr>
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 */

#include <stm32f4/rcc.h>

void handler_reset();
void handler_default();
void main();

/*** linker script pointers ***/
extern uint32_t _data_flash;
extern uint32_t _data_begin;
extern uint32_t _data_end;
extern uint32_t _bss_begin;
extern uint32_t _bss_end;
extern uint32_t _stack_end;

/*** vector table ***/
__attribute__ ((section(".vector_table")))
void (* const table_interrupt_vector[256])() = {
	(void *)&_stack_end,// 0 - Stack
	handler_reset,		// 1 - Reset
	handler_default, 	// 2 - NMI (non maskable interrupt)
	handler_default, 	// 3 - Hard fault
	handler_default, 	// 4 - Memmanage fault (MPU violation or access to illegal location)
	handler_default, 	// 5 - Bus fault (bus error)
	handler_default, 	// 6 - Usage fault (program error eg acces coprocessor)
	0, 					// 7 - Reserved
	0, 					// 8 - Reserved
	0, 					// 9 - Reserved
	0, 					// 10 - Reserved
	handler_default,	// 11 - SVC (Supervisor call)
	handler_default,	// 12 - Debug monitor (BP, WP, external debug requests)
	0, 					// 13 - Reserved
	handler_default, 	// 14 - PendSV (pendable service call)
	handler_default, 	// 15 - SysTick (System tick timer)
	handler_default, 	// 0 -- ExtInt0 (External interrupt 0)
	handler_default,	// ...
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default,
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default,	// 20
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default,	// 30
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default,	// 40
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default,	// 50
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default, 
	handler_default,
	handler_default		// 60
};


/*** reset handler ***/
void handler_reset() {
	uint32_t *p;
	uint32_t *q;
	uint32_t x;

	// configure clock
	// HSE_VALUE <- 8000000 (8MHz - crystial frequency)
	// PLL_M <- 8 (/8 - 1MHz PLL)
	// MCK = (HS[EI]_CK / PLL_M) * PLL_N / PLL_P
	//	MCK		APB1	APB2	PLL_M	PLL_N	PLL_P	PLL_Q
	//	168		42		84		8		336		2		7

	// configure HSI clock
	RCC_CR |= RCC_CR_HSION;
	while((RCC_CR & RCC_CR_HSIRDY) == 0);
	RCC_CFGR_SW_SET(RCC_CFGR, RCC_HSI);

	// configure HSE clock
	RCC_CR |= RCC_CR_HSEON;
	while((RCC_CR & RCC_CR_HSERDY) == 0);
	//RCC_CFGR_SW_SET(RCC_CFGR, RCC_HSE);

	// configure AHB and AHP[12]
	RCC_CFGGR_HPRE_SET(RCC_CR, RCC_HPRE_NODIV);
	RCC_CFGGR_PPRE1_SET(RCC_CR, RCC_PPRE_DIV4);
	RCC_CFGGR_PPRE2_SET(RCC_CR, RCC_PPRE_DIV2);

	// configure PLL
	RCC_CR &= ~RCC_CR_PLLON;
	x = 0;
	x |= RCC_PLLCFGR_SRC_HSE;
	RCC_PLLCFGR_M_SET(x, 8);
	RCC_PLLCFGR_N_SET(x, 336);
	RCC_PLLCFGR_P_SET(x, RCC_PLLP2);
	RCC_PLLCFGR_Q_SET(x, 7);
	RCC_PLLCFGR = x;
	RCC_CR |= RCC_CR_PLLON;
	while((RCC_CR & RCC_CR_PLLRDY) == 0);	

	// select PLL as SYSCLK
	RCC_CFGR_SW_SET(RCC_CFGR, RCC_PLL);
	while(RCC_CFGR_SWS_GET(RCC_CFGR) != RCC_PLL);
	RCC_CR &= ~RCC_CR_HSION;

	// copy data from FLASH to RAM
	p = &_data_flash;
	for(q = &_data_begin; q < &_data_end;)
			*q++ = *p++;

	// set to 0 BSS
	for(q = &_bss_begin; q < &_bss_end;)
		*q++ = 0;

	// run main
	main();
}

/*** default handler */
void handler_default() {
	while(1);
}

