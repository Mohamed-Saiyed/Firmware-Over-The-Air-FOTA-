cc=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -I inc -c -mcpu=$(MACH)  -mthumb -Wall -std=gnu11 
LDFLAGS= -nostdlib -T LinkerScript.ld -Wl,-Map=final.map

vpath %.c D:\ARM\01-RCC\src


OJEC =  RCC_Program.o D:\ARM\02-GPIO\GPIO_Program.c

$(OJEC):%.o:%.c 
	$(cc) $(CFLAGS) -o $@ $^
		
