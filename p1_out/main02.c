/*
 * _01_turn_on_led.c
 *
 * Created: 09.07.2018 17:28:42
 * Author : user
 */ 

#include <avr/io.h>


int main2(void)
{
    PORTB |= (1 << PORTB5); // Set output voltage on Port B Pin 5 high
	DDRB |= (1 << DDB5);    // Set Pin 5 of Port B to output
	
    for (;;) 
    {
    }
}

