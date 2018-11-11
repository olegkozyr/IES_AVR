/*
* �������� 6. ���.
*
* ������������ ��������� ����� � ��������� ����� �����
* 
* �������� �������� 10 ������ ���:
* ������ �������: 0...5 �;
* dV = 5/1024 = 0,0048828125 �.
* 
* ʳ������ ����� ������� ��� ���������
* ������� �������� �� ��������� LED0:
*
* tdel    = 0,010�.
* fclk_io = 1���.
* N       = 8.
* f0      = 1���/8           = 125000��.
* t0      = 1/125000��       = 0,000008�.
* n       = 0,010�/0,000008� = 1250
* 
*/

#include <avr/io.h>
#define F_CPU              1000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

#define DIGIT_1            (1<<PB0)
#define DIGIT_2            (1<<PB1)
#define DIGIT_3            (1<<PB2)
#define DIGIT_4            (1<<PB3)

#define CLEAR_TIMER        TCNT1 = 0x00                /* ������� ������� ��������� �������� 
	                                                      ���������. */
#define TIMER_COUNT        1250
#define NUMBER_CODE_MAX    6
#define DIGITS_MAX         3
#define DIGITS_MIN         0
#define DELAY              19

static const uint8_t number_code[] = {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
static const uint8_t digits[] = {DIGIT_1,DIGIT_2,DIGIT_3,DIGIT_4};
static uint8_t values[] = {0,0,0,0};
static uint8_t i = DIGITS_MAX;
static uint8_t k = 0;
/*
ISR(TIMER1_COMPA_vect)
{
	PORTB = digits[i];
	PORTD = number_code[values[i]];

	if(i > DIGITS_MIN)
	{
		i--;
	}
	else
	{
		i = DIGITS_MAX;
		PORTD &= ~0x80;
		if(k < DELAY)
		{
			k++;
		}
		else
		{
			k = 0;
		}
	}
}
*/
int main08(void)
{
	/* ����������� �������� 12 ������. */
	PORTB = 0x00;
	PORTD = 0x00;
	DDRB = 0x0F;
	DDRD = 0xFF;
	
	/* ����������� ��� */
	ADMUX |= (1<<REFS0); /* ������ ������� �� AVCC, ADC0 ����. */
	ADCSRA |= (1<<ADPS1)|(1<<ADPS0); /* �������� ������� �������, N=8. */
	ADCSRA |= (1<<ADEN); /* �������� ���. */
	
    /* ������������ ������ 1. */
    CLEAR_TIMER;                                                                           
	OCR1A = TIMER_COUNT;                               /* ʳ������ ����� ���������. */
	TIMSK1 |= (1<<OCIE1A);                             /* ��������� TIMER1_COMPA �����������. */
	sei();                                             /* ��������� ��������� ����������. */
	TCCR1A |= 0x00;                                    /* ����� CTC. */
	TCCR1B |= (1<<WGM12)|(1<<CS11);                    /* ���� ����������� ������� �������� 
	                                                      �������: fclk_io = F_CPU = 1���.
	                                                      �������� ������� N = 8. 														  
														  ������ ���������.*/
	
	uint16_t temp = 0;
	uint8_t temp_values[] = {0,0,0,0};
	float fvalue = 0.0f;
		
	while (1)
	{
		_delay_ms(100);
		
		/* ��������� �������� */
		ADCSRA |= (1<<ADSC);
		while((ADCSRA & (1<<ADSC))>0);

        temp = ADC;
		fvalue = 5.0f*(temp)/1024.0f;
		temp = fvalue*1000.0f;
		temp_values[0] = temp/1000;
		temp = temp%1000;
		temp_values[1] = temp/100;
		temp = temp%100;
		temp_values[2] = temp/10;
		temp_values[3] = temp%10;
		
		cli();
		
		for(int j = 0; j < (DIGITS_MAX+1); j++)
		{
			values[j] = temp_values[j];
		}
		
		sei();
	}
}

