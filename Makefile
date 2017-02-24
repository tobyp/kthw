CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

CFLAGS=-I./ -std=c11 -fno-common -g -mcpu=cortex-m4 -mthumb
ASFLAGS=-mcpu=cortex-m4
LDFLAGS=-nostartfiles -T stm32f407vg.ld

all: main.bin

clean:
	rm -f *.bin *.elf *.o

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

main.elf: startup.o main.o bomb.o simonsays.o util.o shift_register.o
	$(LD) $(LDFLAGS) -o $@ $^

startup.o: stm32f407vg.h
