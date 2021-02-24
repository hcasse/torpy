
# ST-Link configuration
STLINK_ROOT=stlink-1.5.1/build/Release

# sources
APP=main
SOURCES = \
	startup.c \
	main.c \
	src/tinyprintf.c
OBJECTS = $(SOURCES:.c=.o)

# compiler configuration
ARCH=arm-none-eabi-

CC=$(ARCH)gcc
OBJCOPY=$(ARCH)objcopy
CFLAGS += -g3 -Wall -O2

CFLAGS += \
	-Tlink.ld \
	-mfloat-abi=hard \
	-mlittle-endian \
	-mcpu=cortex-m4 \
	-mfpu=fpv4-sp-d16 \
	-mthumb \
	-I include
LDFLAGS = \
	-static \
	-nostdinc -nostdlib \
	-nostartfiles


# rules
all: $(APP).elf

$(APP).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJECTS) $(APP).elf

burn: proj
	$(STLINK)/st-flash write $(APP).bin 0x80000000

openocd:
	rm stm32f4.log
	openocd -f openocd.cfg

$(APP).dis: $(APP).elf
	$(ARCH)objdump -D $< > $@

reset:
	stlink-1.5.1/build/Release/st-flash  write reset.bin 0x8000000
