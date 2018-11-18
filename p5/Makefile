PRG              = program05
PRG_M            = $(PRG)_m
PRG_S            = $(PRG)_s
OBJ_M            = $(PRG_M).o
OBJ_S            = $(PRG_S).o

MCU_TARGET     = atmega168

OPTIMIZE       = -O2

# AVR tools.

CC             = "C:\avr8-gnu-toolchain-3.6.1.1752-win32.any.x86\avr8-gnu-toolchain-win32_x86\bin\avr-gcc.exe"

OBJCOPY        = "C:\avr8-gnu-toolchain-3.6.1.1752-win32.any.x86\avr8-gnu-toolchain-win32_x86\bin\avr-objcopy.exe"

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET)

all: $(PRG_M).elf $(PRG_M).hex $(PRG_S).elf $(PRG_S).hex

$(PRG_M).elf: $(OBJ_M)
	$(CC) $(CFLAGS) -o $@ $^

$(PRG_M).hex: $(PRG_M).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	
$(PRG_S).elf: $(OBJ_S)
	$(CC) $(CFLAGS) -o $@ $^

$(PRG_S).hex: $(PRG_S).elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@



