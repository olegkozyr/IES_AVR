PRG            = program04
OBJ            = $(PRG).o

MCU_TARGET     = atmega168

OPTIMIZE       = -O2

# AVR tools.

CC             = "C:\avr8-gnu-toolchain-3.6.1.1752-win32.any.x86\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe"

OBJCOPY        = "C:\avr8-gnu-toolchain-3.6.1.1752-win32.any.x86\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe"

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET)

all: $(PRG).elf $(PRG).hex

# dependency:
$(OBJ): lcd.c lcd.h

#$(PRG).elf: $(OBJ)
$(PRG).elf: $(OBJ) lcd.o
	$(CC) $(CFLAGS) -o $@ $^

$(PRG).hex: $(PRG).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@



