CC = arm-none-eabi-gcc
ARCH = cortex-m4
CFLAGS = -c -mcpu=$(ARCH) -mthumb -Wall	
LDFLAGS = --specs=nano.specs -T STM32f103xx.ld -Wl,-Map=final.map
CL = rm -rf *.o *.hex *.elf *.map

.PHONY: all
.PHONY: clean

OBJS = Stm32f103C8T6_Startup.o main.o GPIO_Program.o RCC_Program.o syscalls.o 	final.elf final.hex
all: $(OBJS)


clean:
	$(CL)
	
main.o:main.c
	$(CC) $(CFLAGS) -o $@ $^
	
GPIO_Program.o:GPIO_Program.c
	$(CC) $(CFLAGS) -o $@ $^
	
RCC_Program.o:RCC_Program.c
	$(CC) $(CFLAGS) -o $@ $^
	
Stm32f103C8T6_Startup.o:Stm32f103C8T6_Startup.c
	$(CC) $(CFLAGS) -o $@ $^
	
final.elf:Stm32f103C8T6_Startup.o main.o GPIO_Program.o	RCC_Program.o
	$(CC) $(LDFLAGS) -o $@ $^
	
final.hex:final.elf
	arm-none-eabi-objcopy -O ihex final.elf final.hex

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) -o $@ $^
	

