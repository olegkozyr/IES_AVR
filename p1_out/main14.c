/*
* POV Toy
*/

#include <avr/io.h>
#include <util/delay.h>

void POVDisplay(uint8_t one_byte)
{
	PORTB = one_byte;
	_delay_ms(2);
}

int main14(void)
{
	PORTB = 0x00;
	DDRB = 0xFF;
	
	while(1)
	{
		POVDisplay(0b00001110);
		POVDisplay(0b00011000);
		POVDisplay(0b10111101);
		POVDisplay(0b01110110);
		POVDisplay(0b00111100);
		POVDisplay(0b00111100);
		POVDisplay(0b00111100);
		POVDisplay(0b01110110);
		POVDisplay(0b10111101);
		POVDisplay(0b00011000);
		POVDisplay(0b00001110);
		
		PORTB = 0x00;
		_delay_ms(10);
	}
}