CC = avr-gcc
CFLAGS = -g -Os -mmcu=atmega328 -c -I.
LINKERFLAGS = -g -mmcu=atmega328

NAME = flash
ELFFILE = $(NAME).elf
HEXFILE = $(NAME).hex

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

$(HEXFILE): $(ELFFILE)
	avr-objcopy -j .text -j .data -O ihex $< $@

$(ELFFILE): $(OBJECTS)
	$(CC) $(LINKERFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

test: flash clean
	picocom /dev/ttyUSB0 -b 9600

flash: $(HEXFILE)
	avrdude -F -V -c stk500v1 -p m328p -P /dev/ttyUSB0 -b 57600 -U flash:w:$(HEXFILE)

.PHONY: clean

clean:
	rm -rf *.o *.hex *.elf
