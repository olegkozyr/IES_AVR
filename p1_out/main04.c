/*
 * _01_blink_led.c
 *
 * Created: 08.09.2018 18:31:34
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main4(void)
{
    DDRB = 0b00000001;
	
    while (1) 
    {
		PORTB = 0b00000001;
		_delay_ms(1000);
		
		PORTB = 0b00000000;
		_delay_ms(1000);
	}
	
	
}

