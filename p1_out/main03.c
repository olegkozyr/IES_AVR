/*
 * _02_flashing_led_specific_frequency.c
 *
 * Created: 10.07.2018 18:10:42
 * Author : user
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

int main3(void)
{
    DDRB |= (1 << DDB5);
	
    for (;;) 
    {
		PINB |= (1 << PINB5);
		
		_delay_ms(1000);
    }
}

