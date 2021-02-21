
# ST-Link configuration
STLINK_ROOT=stlink-1.5.1/build/Release

# sources
APP=main
SOURCES = \
	startup.c \
	main.c
OBJECTS = $(SOURCES:.c=.o)

# compiler configuration
ARCH=arm-linux-gnueabi-
CC=$(ARCH)gcc
OBJCOPY=$(ARCH)objcopy
CFLAGS += -g3 -Wall
#-Tlink.ld
CFLAGS += -mlittle-endian -mcpu=cortex-m4
#CFLAGS += -mfloat-abi=hard
#-mfpu=fpv4-sp-d16
CFLAGS += -I include
#CFLAGS += -mthumb -mthumb-interwork
LDFLAGS = -Tlink.ld -nostartfiles



# rules
all: $(APP).elf

$(APP).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -f *.o $(APP).elf

burn: proj
	$(STLINK)/st-flash write $(APP).bin 0x80000000

openocd:
	openocd -f board/stm32f4discovery.cfg -f interface/stlink-v2-1.cfg
