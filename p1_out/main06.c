/*
 * ¬ключаютьс€ св≥тлод≥оди посл≥довно по одному
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main6(void)
{
    int delay = 500;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
    while (1) 
    {
		for(int i = 0; i < 8; i++)
		{
			PORTB = (1<<i);
			_delay_ms(delay);	
		}
		
    }
}

