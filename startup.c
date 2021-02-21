/*
 * Starup code for STM32 F4
 */

#include <stdint.h>

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

// useful
#define _IOREG(b, o)		(*(volatile uint32_t *)(b + o))
#define _SIZE(u, l)			((u) - (l) + 1)
#define _MASK(u, l)			(((1 << _SIZE(u, l)) - 1) << (l))
#define _SET(x, u, l, v)	{ uint32_t xx = (x); xx &= ~_MASK(u, l); xx |= (v) << l; (x) = xx; }
#define _GET(x, u, l)		(((x) & _MASK(u, l)) >> (l))

// RCC registers
#define RCC_HSI				0b00
#define RCC_HSE				0b01
#define RCC_PLL				0b10

#define RCC_HPRE_NODIV		0b0000
#define RCC_PPRE_DIV2		0b100
#define RCC_PPRE_DIV4		0b101
#define RCC_PLLP2			0b00
#define RCC_PLLP4			0b01
#define RCC_PLLP6			0b10
#define RCC_PLLP8			0b11


#define RCC_BASE		0x40023800
#define RCC_REG(o)		_IOREG(RCC_BASE, o)
#define RCC_CR			RCC_REG(0x00)
#define RCC_CR_HSION		(1 << 0)
#define RCC_CR_HSIRDY		(1 << 1)
#define RCC_CR_HSEON		(1 << 16)
#define RCC_CR_HSERDY		(1 << 17)
#define RCC_CR_PLLON		(1 << 24)
#define RCC_CR_PLLRDY		(1 << 25)
#define RCC_PLLCFGR		RCC_REG(0x04)
#define RCC_PLLCFGR_M_SET(x, v)		_SET(x, 5, 0, v)
#define RCC_PLLCFGR_N_SET(x, v)		_SET(x, 14, 6, v)
#define RCC_PLLCFGR_P_SET(x, v)		_SET(x, 17, 16, v)
#define RCC_PLLCFGR_SRC_HSI			0
#define RCC_PLLCFGR_SRC_HSE			(1 << 22)
#define RCC_PLLCFGR_Q_SET(x, v)		_SET(x, 27, 24, v)
#define RCC_CFGR		RCC_REG(0x08)
#define RCC_CFGR_SW_SET(x, v)		_SET(x, 1, 0, v)
#define RCC_CFGR_SWS_GET(x)			_GET(x, 2, 1)
#define RCC_CFGGR_HPRE_SET(x, v)	_SET(x, 7, 4, v)
#define RCC_CFGGR_PPRE1_SET(x, v)	_SET(x, 12, 10, v)
#define RCC_CFGGR_PPRE2_SET(x, v)	_SET(x, 15, 13, v)
#define RCC_CIR			RCC_REG(0x0C)
#define RCC_AHB1RSTR	RCC_REG(0x10)
#define RCC_AHB2RSTR	RCC_REG(0x14)
#define RCC_AHB3RSTR	RCC_REG(0x18)
#define RCC_APB1RSTR	RCC_REG(0x20)
#define RCC_APB2RSTR	RCC_REG(0x24)
#define RCC_AHB1ENR		RCC_REG(0x30)
#define RCC_AHB2ENR		RCC_REG(0x34)
#define RCC_AHB3ENR		RCC_REG(0x38)
#define RCC_APB1ENR		RCC_REG(0x40)
#define RCC_APB2ENR		RCC_REG(0x44)
#define RCC_AHB1LPENR	RCC_REG(0x50)
#define RCC_AHB2LPENR	RCC_REG(0x54)
#define RCC_AHB3LPENR	RCC_REG(0x58)
#define RCC_APB1LPENR	RCC_REG(0x60)
#define RCC_APB2LPENR	RCC_REG(0x64)
#define RCC_BDCR		RCC_REG(0x70)
#define RCC_CSR			RCC_REG(0x74)
#define RCC_SSCGR		RCC_REG(0x80)
#define RCC_PLLISCFGR	RCC_REG(0x84)

#define MHZ			* 1000000
#define SYSCLK		(168 MHZ)
#define AHB_CLK		(168 MHZ)
#define APB1_CLK	(42 MHZ)
#define APB2_CLK	(84 MHZ)


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

