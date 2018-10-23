/*
 * Світлодіоди включаються послідовно по два без повторень
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main9(void)
{
    int delay = 500;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
    while (1) 
    {
		for(int i = 0; i < 4; i++)
		{
			PORTB = ( (1<<(i*2)) | (1<<(i*2+1)) );
			_delay_ms(delay);	
		}
		
    }
}

