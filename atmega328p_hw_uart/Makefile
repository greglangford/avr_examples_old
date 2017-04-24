CC = avr-gcc
CFLAGS = -g -Os -mmcu=atmega328 -c
LINKERFLAGS = -g -mmcu=atmega328

HEXFILE = main.hex
ELFFILE = main.elf

flash: hex
	avrdude -F -V -c stk500v1 -p m328p -P /dev/ttyUSB0 -b 57600 -U flash:w:$(HEXFILE)

hex: link
	avr-objcopy -j .text -j .data -O ihex $(ELFFILE) $(HEXFILE)

link: main.o
	$(CC) $(LINKERFLAGS) -o $(ELFFILE) main.o

main.o: main.c
	$(CC) $(CFLAGS) -o main.o main.c
