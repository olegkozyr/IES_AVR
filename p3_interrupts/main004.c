/* 
* �������� 4. ������������ �������/���������. ������ 0.
* ���������� �����. 
*
* ����������� ��������: ������� ��������� LED0
* �������������� ������. 
* 
* LED0 �������� ��������� �� PB0 ����� B.
*
* � ������ ������ ������ ��������������� 
* ��� ��������� ��������.
* ������ 0 - 8 �����, - ����� �� 0 �� 255.
* ������� �������� ��������� ���������� �
* ������ TCNT0. 
* � ����������� ����� �������� ������ 
* �������� TCNT0. ��� ���������� �������������
* �������� 255, � ��������� ���� �������� 
* TCNT0 ����������� � � ������ TIFR0 
* �������������� TOV0 ��, �� ��������� ����,
* �� �������� ������������. 
*
* ���������� ������� ������ ����� ���������
* ��� ��������� ������� �������� �� ��������� LED0.
* 
* �������� �� �������������               tdel.
* ������� ������� ����������� ������     fclk_io.
* �������� �������                        N.
* ������� ������� �������                  f0 = fclk_io/N.
* ������ �������� ��������� �������       t0 = 1/f0.
* ��������� ������ ������� ����� �������  t8 = t0*255.
* ʳ������ n ������ ����� ������� 
* ��� ���������� �������� tdel:            n = tdel/t8.
*
* tdel    = 1�.
* fclk_io = 1���.
* N       = 1024.
* f0      = 1���/1024     = 976,5625��.
* t0      = 1/976,5625��  = 0,001024�.
* t8      = 0,001024�*255 = 0,26112�.
* n       = 1�/0,26112�   = 3,829657 = 4
*
* 
*/

#include <avr/io.h>
#define F_CPU 1000000UL                                /* ������� ������� ���������. */
#define LED0 PB0

int main004(void)
{
	int current_n = 0;
	const int n = 4;
	
	/* ������������ ������ */     
	PORTB = 0x00;
	DDRB = (1<<LED0);              
	                           
    /* ������������ ������ 0 */
    TCNT0 = 0x00;                                      /* ������� ������� ��������� �������� 
	                                                      ���������. */
	TCCR0A = 0x00;                                     /* ���������� ����� ������. */
	TCCR0B = (1<<CS02)|(1<<CS00);                      /* ���� ����������� ������� �������� �������:
	                                                      fclk_io = F_CPU = 1���.
	                                                      �������� ������� N = 1024. 
														  ������ ���������. */
 
    while (1) 
    {
        while((TIFR0 & (1<<TOV0)) == 0);               /* ³������� ������������ ���������? */
		TIFR0 = (1<<TOV0);                             /* ��� �������� ��� TOV0 � TIFR0 ������,
		                                                  ������� ���������� 1 � TOV0 ��. */
		current_n++;
		
		if(current_n == n)
		{
		    PINB = (1<<LED0);
		    current_n = 0;
		}
    }
	
    return 0;
}

