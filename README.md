# Torpy Project

Only for board STM32F407.

## Dependencies

For Linux, take a look here https://www.instructables.com/Start-Developing-STM32-on-Linux/ .

* Install any GCC ARM compiler you want. Mine is:
	PREFIX=arm-linux-gnueabi-

* Install st-link utility (use openocd instead)
	$ wget https://github.com/stlink-org/stlink/archive/v1.5.1.tar.gz
	$ tar xvf v1.5.1.tar.gz
	$ sudo apt-get install build-essential libgtk-3-dev libgusb-dev
	$ cd stlink-1.5.1
	$ make



## OpenOCD

### Installation

https://cycling-touring.net/2018/12/flashing-and-debugging-stm32-microcontrollers-under-linux

To install:
	$ sudo apt-get install openocd

**Things below are not sure to be required (to check)**
Add the file `/etc/udev/rules.d/99-openocd.rules`:
#STLink V2
ATTRS{idVendor}=="0483", ATTRS{idProduct}=="374b", MODE="664", GROUP="plugdev"

And type:
	$ udevadm control --reload-rules && udevadm trigger

**End of optional**


### Usage

Type:
	$ openocd -f board/stm32f4discovery.cfg -f interface/stlink-v2-1.cfg

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


## References

* https://embedds.com/
* http://stm32f4-discovery.net/2015/01/properly-set-clock-speed-stm32f4xx-devices/
* https://stm32f4-discovery.net/



