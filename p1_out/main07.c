/*
 * ¬ключаютьс€ св≥тлод≥оди посл≥довно по два
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main7(void)
{
    int delay = 500;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
    while (1) 
    {
		for(int i = 0; i < 7; i++)
		{
			PORTB = ((1<<i) | (1<<(i+1)));
			_delay_ms(delay);	
		}
		
    }
}

