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

#include <tinyprintf.h>

#include <stm32f4/dbg.h>
#include <stm32f4/gpio.h>
#include <stm32f4/rcc.h>

volatile int n = 10;

int main() {
	int i = 0;

	ITM_puts("Hello, World!\n");

	// set power
	RCC_AHB1ENR |= 1 << ID_GPIOD;

	// initialize the LEDs
	GPIO_MODER_SET(LED_ORANGE, GPIO_MODER_OUT);
	GPIO_MODER_SET(LED_BLUE, GPIO_MODER_OUT);
	GPIO_MODER_SET(LED_RED, GPIO_MODER_OUT);
	GPIO_MODER_SET(LED_GREEN, GPIO_MODER_OUT);

	// endless loop
	while(1) {

		GPIO_BSRR_SET(LED_ORANGE);
		GPIO_BSRR_SET(LED_RED);
		GPIO_BSRR_RESET(LED_BLUE);
		GPIO_BSRR_RESET(LED_GREEN);
		printf("ping %d\n", i);

		for (i = 0; i < 6000000; i++)
			__asm__("nop");

		GPIO_BSRR_RESET(LED_ORANGE);
		GPIO_BSRR_RESET(LED_RED);
		GPIO_BSRR_SET(LED_BLUE);
		GPIO_BSRR_SET(LED_GREEN);
		printf("pong %d\n", i);

		for (i = 0; i < 6000000; i++)
			__asm__("nop");
		i++;
	}
}
