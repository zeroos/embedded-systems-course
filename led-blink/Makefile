# Based upon http://www.hookersandbooze.com/avr-gcc-makefile/

MCU = atmega328p
CC = avr-gcc -mmcu=$(MCU)
CFLAGS = -O2 -Wall -Wextra

PRG = led-blink

$(PRG).hex: $(PRG).elf
$(PRG).elf: $(PRG).o
$(PRG).o: $(PRG).c

%.elf: %.o
	$(CC) $(CFLAGS) -o $@ $^

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

install: $(PRG).hex
	avrdude -p $(MCU) -c arduino -P $(PORT) -v -U flash:w:$(PRG).hex 

clean:
	@rm -vf $(PRG).{elf,hex,o,map} *~
