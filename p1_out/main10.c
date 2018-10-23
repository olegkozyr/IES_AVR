/*
 * Світлодіоди вмикаються послідовно по одному, по два, і т.д з повтореннями
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main10(void)
{
    int delay = 500;
	
	PORTB = 0x00;
	DDRB = 0xFF;
	
    while (1) 
    {
		for(volatile uint8_t i = 0; i < 8; i++)
		{
			for(volatile uint8_t j = 0; j < (8-i); j++)
			{
				PORTB = 0x00;
				for(volatile uint8_t k = j; k < (j+i+1); k++)
				{
					PORTB |= (1<<k);
				}
				_delay_ms(delay);
			}
		}
		
    }
}

