/*
* Програма 6. АЦП.
*
* Перетворення двійкового числа в десяткове дійсне число
* 
* Роздільна здатність 10 бітного АЦП:
* розмах напруги: 0...5 В;
* dV = 5/1024 = 0,0048828125 В.
* 
* Кількість тактів таймеру для створення
* потрібної затримки між миганнями LED0:
*
* tdel    = 0,010с.
* fclk_io = 1МГц.
* N       = 8.
* f0      = 1МГц/8           = 125000Гц.
* t0      = 1/125000Гц       = 0,000008с.
* n       = 0,010с/0,000008с = 1250
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

#define CLEAR_TIMER        TCNT1 = 0x00                /* Очистка регістру поточного значення 
	                                                      лічильника. */
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
	/* Ініціалізація вихідних 12 виводів. */
	PORTB = 0x00;
	PORTD = 0x00;
	DDRB = 0x0F;
	DDRD = 0xFF;
	
	/* Ініціалізація АЦП */
	ADMUX |= (1<<REFS0); /* Опорна напруга на AVCC, ADC0 вхід. */
	ADCSRA |= (1<<ADPS1)|(1<<ADPS0); /* Подільник тактової частоти, N=8. */
	ADCSRA |= (1<<ADEN); /* Активіція АЦП. */
	
    /* Налаштування тамеру 1. */
    CLEAR_TIMER;                                                                           
	OCR1A = TIMER_COUNT;                               /* Кількість тактів лічильника. */
	TIMSK1 |= (1<<OCIE1A);                             /* Активація TIMER1_COMPA переривання. */
	sei();                                             /* Глобальна активація переривань. */
	TCCR1A |= 0x00;                                    /* Режим CTC. */
	TCCR1B |= (1<<WGM12)|(1<<CS11);                    /* Вибір внутрішнього джерела тактових 
	                                                      сигналів: fclk_io = F_CPU = 1МГц.
	                                                      Подільник частоти N = 8. 														  
														  Запуск лічильника.*/
	
	uint16_t temp = 0;
	uint8_t temp_values[] = {0,0,0,0};
	float fvalue = 0.0f;
		
	while (1)
	{
		_delay_ms(100);
		
		/* Отримання значення */
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

