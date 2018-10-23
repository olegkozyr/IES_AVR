/* 
* �������� 7. ������������ ��������� ����������. INT0 �����������.
* 
* �������� ����������� - �� �����������, 
* �� ��������� ��� ���� ����� ������ ������ ��������������.
*
* ����������� ��������: LED0 �������� ���� �������. 
* ϳ��� ���������� �� ������ �������� LED1 ��������, 
* � LED0 �������� ����������. 
* ��� ���������� ������ LED1 ������� ����������, 
* � LED0 - ������ ������.
* 
* ������ �������� �� ������ PD2 ����� D.
* ��������������� ��������� ���������� ��������.
* LED0 �������� ��������� �� 5-�� ��� ����� B.
* LED1 �������� ��������� �� 7-�� ��� ����� B.
* 
* ����� 1 � PINB7 �� ������� PINB
* ����� �������� ���������� ��� 
* �� ����������. ��� ����� ����� ��
* ������� ���� ������������ ��� ���������
* ������� DDRB = (1<<PB7).
*
* ����������� INT0 ������ �� ����� PD2 ����� D.
* ���������� INT0 ����������� � ��������� ������
* ��������� ������� ���������� �����������: ����������� �����,
* ������� �����, ����-��� ���� ����� ������ �� 
* �������� ������� ����� ������� �� �����.
* 
* � ���� ������� ����������� INT0 ������ �� 
* ����-��� ���� ������ PD2.
* 
* ��� ������������ INT0 ����������� ������� �����������
* ������� EIMSK, EICRA �� SREG (������ �����). 
* 1. ������������ � ������ EIMSK �� INT0 ��� ��������� 
*    INT0 �����������:
*    EIMSK |= (1<<INT0).
* 2. ������������ � ������ EICRA �� ISC00 ��� ���������
*    ������ ���������� ����������� INT0 ��
*    ����-��� ���� ������ PD2:
*    EICRA |= (1<<ISC00).
* 3. �������� ��������� ������� ��������������� 
*    ��� ����������, ������� � ������ SREG ��� I.
*    ��� ����� ������������� ������� sei().
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LED0 (1<<PB5)
#define LED1 (1<<PB7)
#define ON   1
#define OFF  0

//uint8_t led0_state = ON;
uint8_t led1_state = OFF;
uint16_t i = 0;

/* ���������� ������� ������� ����������. 
ISR(INT0_vect)                                         /* �������� INT0_vect ������� ����� ������ 
{                                                      /* �������� ������� ����������� INT0. 
	if(led1_state)
	{
		led1_state = OFF;
		led0_state = ON;
		PORTB &= ~LED1;
	}
	else
	{
		led1_state = ON;
		led0_state = OFF;
		PORTB &= ~LED0;
		PORTB |= LED1;
	}
	
}
*/
int main9(void)
{
	/* ������������ ������ */
	PORTB = 0x00;                                      
    DDRB = (LED0|LED1);                                     /* 5-� �� 7-� ������ �������� �� �����. */
    DDRD = (0<<PD2);                                   /* 2-� �� ������ �� ����. */
	PORTD = (1<<PD2);                                  /* ��������� ����������� �����������
	                                                      ��������� �� ����� PD2. */

	/* ������������ INT0 ����������� */
	EIMSK |= (1<<INT0);                                /* ��������� INT0. */
	EICRA |= (1<<ISC00);                               /* ����������� ������ ��� ���� �����
	                                                      ������ PD2. */
	sei();                                             /* ��������� ��������� ����������. */
 
    while (1) 
    {
//		if(led0_state)
//		{
//		    PORTB ^= LED0;		    	
//		}
//		else
//		{
//			PORTB &= ~LED0;
//		}
//		_delay_ms(500);			
//		i++;
//		
    }
	
    return 0;
}
