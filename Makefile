CC=arm-none-eabi-gcc
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump

CFLAGS=-I./ -std=c11 -mcpu=cortex-m4 -mthumb -fno-common -fno-builtin -g -Wextra -Wall --pedantic -Wno-missing-field-initializers -Wno-unused-parameter
ASFLAGS=-mcpu=cortex-m4 -mthumb
LDFLAGS=-nostartfiles -T stm32f407vg.ld

all: main.elf

clean:
	rm -f *.bin *.elf *.o *.generated.c

main.bin: main.elf
	$(OBJCOPY) -O binary $< $@

main.elf: startup.o main.o util.o bomb.o simonsays.o morse.o wires.o capacitor.o memory.o password.o
	$(LD) $(LDFLAGS) -o $@ $^

morse.o: morse.c morse.words.generated.c

morse.words.generated.c: morse.words.txt
	./morse.words.py < $^ > $@

password.o: password.c password.words.generated.c

password.words.generated.c: password.words.txt
	./password.words.py < $^ > $@

main.o: main.c pins.inc.h

startup.o: stm32f407vg.h
