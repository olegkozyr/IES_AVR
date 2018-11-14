/*
* Програма 0. Робота з LCD дисплеєм в 8-бітному режимі.
*
* Призначення програми: виводить декілька символів на LCD.
*
* Обладнання:
* - мікроконтролер ATmega16;
* - LCD дисплей LM016L;
*
* LCD - рідкокристалічний символьний дисплей. 
* LM016L дисплей складається з модуля відображення та 
* контролера HD44780, який керує дисплеєм. Данні на 
* дисплей виводяться через контролер.
* Існує протокол обміну даними із контролером HD44780,
* який можна знайти в документації до нього.
* Виводи LM016L дисплею:
* - VSS   - "земля";
* - VDD   - живлення;
* - RS    - визначає тип передаваної інформації:
*           0 - команда;
*	        1 - дані;
* - RW    - Напрям передавання інформації:
*           0 - запис в контролер дисплею;
*	        1 - зчитування із контролеру;
* - E     - при зміні значення на даному виводі
*           від 1 до 0 починається процес
*		    запису/зчитування інформації;
* - D0-D7 - паралельна 8-біт шина обміну
*           даними з дисплеєм;
* За один цикл на дисплей можна передати один байт.
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
* Вибір режиму проводиться при ініціалізації дисплею.
*
* Виводи контролера ATmega168 при 8-біт режимі роботи LCD,
* приєднані до дисплею:
* PB0 - E
* PB1 - RS
* PD0 - D0
* PD1 - D1
* PD2 - D2
* PD3 - D3
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

#define E_ON               PORTB |= (1<<PB0)           /* Подача 1 на E вхід дисплею. */
#define E_OFF              PORTB &= ~(1<<PB0)          /* Подача 0 на E вхід дисплею. 
                                                          Початок процесу обміну інформацією. */
#define START_DATA         PORTB |= (1<<PB1)           /* Подача 1 на RS вхід дисплею. 
                                                          Передача даних. */
#define DATA               1
#define START_COMMAND      PORTB &= ~(1<<PB1)          /* Подача 0 на RS вхід дисплею. 
                                                          Передача команд. */
#define COMMAND            0
#define CLEAR_DATA_PINS    PORTD = 0x00;               /* Стираємо інформацію на входах D0-D7
                                                          дисплею. */
#define SEND_DATA(d)       PORTD = d;                  /* Передача інформації в нонтролер дисплея. */  

/* Інфтрукції ініціалізації контролеру LED дисплею. */
#define INIT_INSTRUCTION_1  0b00110000
#define FUNCTION_SET        0b00111000                 /* Встановлення 8-біт режиму, активація 2-х строк 
                                                          та вибір шрифту. */
#define DISPLAY_ON          0b00001100
#define DISPLAY_CLEAR       0b00000001
#define ENTRY_MODE_SET      0b00000110

/* Ініціалізація виводів мікроконтролеру ATmega168. */
static void port_init(void)
{
	PORTD = 0x00;
	DDRD = 0xFF;
	
	PORTB = 0x00;
	DDRB = (1<<DDB0)|(1<<DDB1);
}

static void send2lcd(uint8_t byte)
{
	E_ON;
	_delay_us(50);
	CLEAR_DATA_PINS;
	SEND_DATA(byte);
	E_OFF;
	_delay_us(50);	
}

/* Вивід байту інформації на дисплей. */
static void send_byte(uint8_t byte, uint8_t mode)
{
	/* byte - дані/команда, яка виводиться на дисплей;
	   mode - тип інформації, яка передається в контролер:
	          0 - команда;
 	          1 - дані;*/
	if (mode)
	{
		START_DATA;
	}
	else
	{
		START_COMMAND;
	}
	
	send2lcd(byte);
}

/* Ініціалізація контролеру дисплея. */
static void lcd_init(void)
{
	_delay_ms(15);                                     
	send2lcd(INIT_INSTRUCTION_1);
	_delay_ms(5);
	send2lcd(INIT_INSTRUCTION_1);
	_delay_us(100);
	send2lcd(INIT_INSTRUCTION_1);
	_delay_ms(1);
	
	send_byte(FUNCTION_SET, COMMAND);
	_delay_ms(1);
	send_byte(DISPLAY_ON, COMMAND);
	_delay_ms(1);
	send_byte(DISPLAY_CLEAR, COMMAND);
	_delay_ms(1);
	send_byte(ENTRY_MODE_SET, COMMAND);
	_delay_ms(1);
}

/* Передача одного символу. */
static void send_char(uint8_t ch)
{
	send_byte(ch, 1);
}

/* Встановлення позиції курсора. */
static void set_position(uint8_t h, uint8_t v)
{
	/* h - позиція по горизонталі.
           Приймає значення від 0 до 15;
       v - позиція по вертикалі.
           0 - верхня строка;
           1 - нижня строка. */
	uint8_t position = 0x00;
	position=(0x40*v+h)|0b10000000;
	send_byte(position, 0);
}

int main(void)
{
	port_init();
	lcd_init();
	set_position(0, 0);
	send_char('0');
	send_char('1');
	set_position(14, 0);
	send_char('E');
	send_char('F');
	set_position(4, 1);
	send_char('4');
	send_char('5');
	
    while (1) 
    {
    }
}

