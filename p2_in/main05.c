/* 
* �������� 5. ������������ ��������� ��������� xor ^.
* 
* ����������� ��������: ��� ���������� ������ ���������� ��������.
* 
* ������ �������� �� 2-�� ������ ����� B.
* ��������������� ��������� ���������� ��������. 
* �������� ��������� �� 5-�� ������ ����� B.
*
* �� ������� ������ �������� �������� ���������.
* 2-� �� ����� B ������� �������������� �� ���������� �������.
* 5-� �� ����� B ������� �������������� �� ��������� �������.
* 
* �������� ������� ����� 2-� �� ����� B. 
* ���� ������ �� ��������� �� ���� ���� 1.
* ���� ������ ���������, �� �� ���� ���� 0.
* 
* ���� �� ���� 2-�� ��� ����� B ���� 0, 
* �� �� ����� 5-�� ��� ����� B ������� ������ 0 ��� ��������� ���������.
*/
#include <avr/io.h>

#define SET_LED           (1<<PB5)                     /* �������� �������� */
#define TURN_LED          PORTB ^= SET_LED             /* ���������� c�������. */
#define PULLUP_ON         (1<<PB2)                     /* ��������� ����������� 
                                                          ����������� ���������. */

#define SET_PORTB         PORTB |= SET_LED | PULLUP_ON /* �������� c������� �� ����������
                                                          ��������� ���������� ��������. */
#define DDR_BUTTPN_LED    DDRB = SET_LED               /* 2-� �� ������ �� ����, 
                                                          5-� �� ������ �� �����. */
 
#define BUTTON_RELEASED   (PINB & (1<<PINB2))          /* ������ ��������? */
#define BUTTON_PRESSED    (PINB & (1<<PINB2))==0       /* ������ ���������? */

int main5(void)
{
	DDR_BUTTPN_LED; 
    SET_PORTB;                                              

    while (1) 
    {
        /* �������� ����� 2-�� ��� */
        while (BUTTON_RELEASED)                        /* ���� ���������� ���� ������ �� ��������� */
        {                                                      
        }
		
		TURN_LED;
		
        while (BUTTON_PRESSED)                         /* ���� ���������� ���� ������ ��������� */
        {                                   
        }
		
		TURN_LED;		
    }
    return 0;
}

