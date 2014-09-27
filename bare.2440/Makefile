
#
AFLAGS  = -mtune=arm9tdmi -msoft-float

CFLAGS  = -D__ARM__ -fno-strict-aliasing
CFLAGS += -mtune=arm9tdmi
CFLAGS += -msoft-float

all: led.S
	arm-bcm2708hardfp-linux-gnueabi-gcc $(CFLAGS) -c -o led.o led.S

clean:
	rm -rf *.o
