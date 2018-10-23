/*
 * POV Toy
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main12(void)
{
	PORTB = 0x00;
	DDRB = 0xFF;
	
	while(1)
	{
		for(int i = 0; i < 8; i++)
		{
			if(i < 6)
			{
				PORTB = ((1<<i) | (1<<(i+1)) | (1<<(i+2)));
				_delay_ms(500);
			}
			else if(i == 6)
			{
				PORTB = ((1<<i) | (1<<(i+1)) | (1<<PB0));
				_delay_ms(500);
			}
			else
			{
				PORTB = ((1<<i) | (1<<PB1) | (1<<PB0));
				_delay_ms(500);
			}
		}
	}
}
