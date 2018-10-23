/*
 * ¬ключаютьс€ св≥тлод≥оди посл≥довно по одному
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main5(void)
{
    int delay = 500;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
    while (1) 
    {
		PORTB = (1<<PB0);
		_delay_ms(delay);
		PORTB = (1<<PB1);
		_delay_ms(delay);
		PORTB = (1<<PB2);
		_delay_ms(delay);
		PORTB = (1<<PB3);
		_delay_ms(delay);
		PORTB = (1<<PB4);
		_delay_ms(delay);
		PORTB = (1<<PB5);
		_delay_ms(delay);
		PORTB = (1<<PB6);
		_delay_ms(delay);
		PORTB = (1<<PB7);
		_delay_ms(delay);
    }
}

