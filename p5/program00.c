/*
* Програма 0. Робота з LCD дисплеєм в 4-бітному режимі.
*
* Призначення програми: виводить декілька символів на LCD.
*
* Обладнання:
* - мікроконтролер ATmega168
* - LCD дисплей LM016L;
*
* LCD - рідкокристалічний символьний дисплей. 
* LM016L дисплей * складається з модуля відображення та 
* контролера HD44780, * який керує дисплеєм. Данні на 
* дисплей виводяться через контролер.
* Існує протокол обміну даними із контролеро HD44780,
* який можна знайти в документації до нього.
* Виводи LM016L дисплею:
* - VSS   - "земля";
* - VDD   - живлення;
* - RS    - визначає тип передаваємої інформації:
*           0 - команда;
*	    1 - дані;
* - RW    - Напрям передавання інформації:
*           0 - запис в контролер дисплею;
*	    1 - зчитування із контролеру;
* - E     - при зміні значення на даному виводі
*           від 1 до 0 починається процес
*		запису/зчитування інформації;
* - D0-D7 - паралельна 8-біт шина запису/зчитування
*           даних з дисплею;
* За один цикл на дислпей можнапередати один байт.
* Існує два режими передавання байту в контролер 
* дисплею:
* 1) передача байта за один цикл; при цьому 
*    використовуються всі вісім виводів D0-D7;
* 2) передача байта за два цикли; при цьому 
*    використовуються тільки чотири виводи D4-D7; 
*    інформація передається повільніше, але 
*    використовується менше виводів;
*    в даному режимі байт передається половинами
*    спочатку старші 4-ри біти потім молодші;
* Вибір режимів проводиться при ініціалізації дисплею.
*
* Виводи контролера ATmega168 приєднаді до дисплею:
* PD2 - RS
* PD3 - E
* PD4 - D4
* PD5 - D5
* PD6 - D6
* PD7 - D7
*
* Виводи дисплею:
* VSS -	приєднаний до "землі" ;
* VDD - до живлення;
* RW - до нульового потенціалу - запис в контролер дисплею.
*
*/
#define F_CPU              1000000UL                   /* Тактова частота процесору. */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define E_ON               PORTD |= (1<<PD3)           /* Подача 1 на E вхід дисплею. */
#define E_OFF              PORTD &= ~(1<<PD3)          /* Подача 0 на E вхід дисплею. */
#define START_DATA         PORTD |= (1<<PD2)           /* Подача 1 на RS вхід дисплею. 
                                                          Передача даних. */
#define START_COMMAND      PORTD &= ~(1<<PD2)          /* Подача 0 на RS вхід дисплею. 
                                                          Передача команд. */
#define CLEAR_DATA_PINS    PORTD &= 0x0F;             /* Стираємо інформацію на входах D4-D7
                                                          дисплею. */
#define SEND_DATA(d)       PORTD |= d;                 /* Передача інформації в нонтролер дисплея. */  
#define INIT_INSTRUCTION_1 0x03
#define INIT_INSTRUCTION_2 0x02
#define INIT_INSTRUCTION_3 0b00101000
#define INIT_INSTRUCTION_4 0b00001100
#define INIT_INSTRUCTION_5 0b00000110

/* Ініціалізація виводів мікроконтролеру ATmega168. */
static void port_init(void)
{
	PORTD = 0x00;
	DDRD = 0xFF;
}

static void send_half_byte(uint8_t halfByte)
{
	halfByte <<= 4;
	E_ON;
	_delay_us(50);
	CLEAR_DATA_PINS;
	SEND_DATA(halfByte);
	E_OFF;
	_delay_us(50);
}

static void send_byte(uint8_t byte, uint8_t mode)
{
	if (mode)
	{
		START_DATA;
	}
	else
	{
		START_COMMAND;
	}
	
	uint8_t temp_byte = 0x00;
	temp_byte = byte >> 4;
	send_half_byte(temp_byte);
	send_half_byte(byte);
}

/* Ініціалізація контролеру дисплея. */
static void lcd_init(void)
{
	_delay_ms(15);                                     /* Затримка для встановлення живлення дисплею. */
	send_half_byte(INIT_INSTRUCTION_1);
	_delay_ms(5);
	send_half_byte(INIT_INSTRUCTION_1);
	_delay_us(100);
	send_half_byte(INIT_INSTRUCTION_1);
	_delay_ms(1);
	send_half_byte(INIT_INSTRUCTION_2);
	_delay_ms(1);
	send_byte(INIT_INSTRUCTION_3, 0);
	_delay_ms(1);
	send_byte(INIT_INSTRUCTION_4, 0);
	_delay_ms(1);
	send_byte(INIT_INSTRUCTION_5, 0);
	_delay_ms(1);
}

static void send_char(uint8_t ch)
{
	send_byte(ch, 1);
}

static void set_position(uint8_t h, uint8_t v)
{
	uint8_t position = 0x00;
	position=(0x40*v+h)|0b10000000;
	send_byte(position, 0);
}

int main(void)
{
	port_init();
	lcd_init();
	set_position(0, 0);
	send_char('g');
	send_char('j');
	set_position(8, 0);
	send_char('a');
	send_char('c');
	set_position(4, 1);
	send_char('d');
	send_char('l');
	
    while (1) 
    {
    }
}

