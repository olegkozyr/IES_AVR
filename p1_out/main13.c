

#include <avr/io.h>
#include <util/delay.h>

int main13(void)
{
	PORTB = 0x07;
	DDRB = 0xFF;
	
	while(1)
	{
		for(int i = 0; i < 8; i++)
		{
			_delay_ms((500));
			PORTB = (PORTB<<1) | (PORTB>>7);
		}
	}
}