/*
 * ¬ключаютьс€ св≥тлод≥оди посл≥довно по три
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main8(void)
{
    int delay = 500;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
    while (1) 
    {
		for(int i = 0; i < 6; i++)
		{
			PORTB = ((1<<i) | (1<<(i+1)) | (1<<(i+2)));
			_delay_ms(delay);	
		}
		
    }
}

