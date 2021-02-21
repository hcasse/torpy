/**
 * Torpy - grid-follower wheeling and box delivering bot.
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
#ifndef STM32F4_IO_H
#define STM32F4_IO_H

#include <stdint.h>

#define _IOREG(b, o)		(*(volatile uint32_t *)(b + o))
#define _SIZE(u, l)			((u) - (l) + 1)
#define _MASK(u, l)			(((1 << _SIZE(u, l)) - 1) << (l))
#define _SET(x, u, l, v)	{ uint32_t xx = (x); xx &= ~_MASK(u, l); xx |= (v) << l; (x) = xx; }
#define _GET(x, u, l)		(((x) & _MASK(u, l)) >> (l))

#define MHZ			* 1000000
#define SYSCLK		(168 MHZ)
#define AHB_CLK		(168 MHZ)
#define APB1_CLK	(42 MHZ)
#define APB2_CLK	(84 MHZ)

#endif	// STM32F4_IO_H
