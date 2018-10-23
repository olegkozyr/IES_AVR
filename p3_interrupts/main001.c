/* 
* �������� 1. ������������ ��������� ����������. INT0 �����������.
*
* ����������� ��������: ��������� LED0 � ��������� LED1 ���������
* ��� ���������� ������.
* 
* ������ �������� �� ������ PD2 ����� D.
* ��������������� ��������� ���������� ��������.
* LED0 �������� ��������� �� 5-�� ��� ����� B.
* LED1 �������� ��������� �� 3-�� ��� ����� �.
*
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/* ���������� ������� ������� ����������. 
ISR(INT0_vect)                                         /* �������� INT0_vect ������� ����� ������ 
{                                                      /* �������� ������� ����������� INT0.                                                   
    PINB |= (1<<PINB5);                                /* ����������� ��������� LED0. 
	PINC |= (1<<PINC3);                                /* ����������� ��������� LED1. 
}
*/
int main001(void)
{
	/* ������������ ������ */
	PORTB = 0x00;                                      /* �������� �������� LED0. */
	PORTC = (1<<PC3);                                  /* �������� �������� LED1. */
	PORTD = (1<<PD2);                                  /* ��������� ����������� �����������
	                                                      ��������� �� ����� PD2. */                         
    DDRB = (1<<DDB5);                                  /* 5-� ���� ����� B ������ �� �����. */
	DDRC = (1<<DDC3);                                  /* 3-� ���� ����� C ������ �� �����. */
    DDRD = (0<<DDD2);                                  /* 2-� ���� ����� D ������ �� ����. */

	/* ������������ INT0 ����������� */
	EICRA |= (1<<ISC00);                               /* ����������� ������ ��� ���� �����
	                                                      ������ PD2. */
	EIMSK |= (1<<INT0);                                /* ��������� INT0. */
	sei();                                             /* ��������� ��������� ����������. */
 
    while (1) 
    {
    }
	
    return 0;
}
