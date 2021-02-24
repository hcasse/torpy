# Torpy Project

Only for board STM32F407.

## Dependencies

The following dependencies are required:
* GCC ARM compiler (preferred arm-none-eabi-)
* openocd
* make
* gdb-multiarch

These packages are already available in standatd Linux distribution.
On Ubuntu-like distribution, you have to type:

	$ sudo apt-get install openocd


Depending on the GCC ARM compiler, you have to tune the Makefile:
	PREFIX=arm-none-eabi-

**Things below are not sure to be required (to check)**
Add the file `/etc/udev/rules.d/99-openocd.rules`:
#STLink V2
ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b", MODE="664", GROUP="plugdev"

And type:
	$ udevadm control --reload-rules && udevadm trigger

**End of optional**


## Building the system

Just type:

	$ make


## Flashing, running and debugging

### Usage

In a separate shell, type:

	$ make openocd

Openocd will run on its own and provide monitoring the STM32F4 board.

Loading from OpenOCD:

	$ telnet localhost 4444
	> init
	> reset init
	> halt
	> flash write_image erase PROGRAM.elf
	> exit

Working with GDB:

	$ gdb PROGRAM.elf
	(gdb) target remote localhost:3333
	(gdb) monitor reset halt
	(gdb) load
	(gdb) continue


## ST-Link

Install st-link utility:
	$ wget https://github.com/stlink-org/stlink/archive/v1.5.1.tar.gz
	$ tar xvf v1.5.1.tar.gz
	$ sudo apt-get install build-essential libgtk-3-dev libgusb-dev
	$ cd stlink-1.5.1
	$ make

It may be useful for instance to flash the ST-Link firmware.


## contributors

* thank you to CJlano for (tinyprintf)[https://github.com/cjlano/tinyprintf]

## References

* https://embedds.com/
* http://stm32f4-discovery.net/2015/01/properly-set-clock-speed-stm32f4xx-devices/
* https://stm32f4-discovery.net/
* https://www.instructables.com/Start-Developing-STM32-on-Linux/
* https://cycling-touring.net/2018/12/flashing-and-debugging-stm32-microcontrollers-under-linux

SWO:
* https://stm32f4-discovery.net/2014/12/library-46-debug-stm32f4-device-swo-feature/
* https://www.openstm32.org/forumthread1530
* http://ehko.blog.free.fr/index.php?post/2017/09/SWD-Trace-avec-un-STM32
* https://github.com/niekiran/Embedded-C/blob/master/All_source_codes/target/itm_send_data.c

