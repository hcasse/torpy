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
#ifndef STM32F4_RCC_H
#define STM32F4_RCC_H

#include "io.h"

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

#endif	// STM32F4_RCC_H
