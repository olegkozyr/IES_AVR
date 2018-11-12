/*
* Програма 0. Робота з LCD дисплеєм.
*
* Призначення програми: виводить строку на дисплей.
*
* Обладнання:
* - мікроконтролер ATmega168
* - LCD дисплей;
*
* 7seg-mpx4-ca дисплей складається із чотирьом семисегментних
* індикаторів. Індикатори відносяться до типу із загальним анодом,
* тобто всі сегменти (світлодіоди) індикатору з'єднані своїми
* анодами з джерелом живлення. Виводи мікроконтролеру приєднуються
* до катодів світлодіодів. Щоб відобразити на індикаторі
* певну цифру повинна увімкнутись певна комбінація світлодіодів,
* а решта світлодіодів повинна бути вимкнена.
* Для того, щоб світлодіод індикатора із загальним анодом
* увімкнувся на його катоді повинен бути потенціал нижчий за
* потенціал аноду. Тому, для увімкнення певного сегменту
* індикатора на відповідному виході мікроконтролеру повинен
* бути встановлений логічний нуль. Для вимкнення сегменту на
* виході повинна бути логічна одиниця.
*
* Робота з даним типом дисплея має свої особливості. В кожен
* момент часу можна виводити цифру тільки на один індикатор
* дисплея. Тому, в кожен момент часу увімкнутий тільки один
* індикатор, а всі інші вимкнуті.
* Якщо послідовно вмикати кожен індикатор дисплея через досить
* малий проміжок часу, який менший за час реакція ока людини,
* то складається відчуття, що всі сегменти дисплею увімкнуті
* одночасно.
* В симуляторі PROTEUS для дисплею 7seg-mpx4-ca цей час < 10 мс.
*
* Дисплей 7seg-mpx4-ca містить два набори виводів:
* - перший містить вісім виводів, позначені "ABCDEFG DP";
* - другий містить чотири виводи, позначені "1234".
* Перший набір виводів керує сегментами конкретного індикатору.
* "ABCDEFG" виводи керують сегментами (світлодіодами)
* індикатору для відображення цифри.
* "DP" вивід керує світлодіодом, який відображає десяткову точку
* в правому нижньому куті індикатору.
* Другий набір виводів слугує вибору конкретного індикатора
* дисплея.
*
* Виводи порту D приєднані до виводів "ABCDEFG DP" дисплею:
* PD0-"A", PD1-"B", ..., PD6-"G", PD7-"DP".
* Виводи PB0-PB3 приєднані до виводів "1234":
* PB0-"1", PB1-"2", PB2-"3", PB3-"4".
*
*/
#define F_CPU              1000000UL
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
#define INIT_INSTRUCTION   0x03

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

static void lcd_init(void)
{
	_delay_ms(15);
	send_half_byte(INIT_INSTRUCTION);
	_delay_ms(4);
	send_half_byte(INIT_INSTRUCTION);
	_delay_ms(100);
	send_half_byte(INIT_INSTRUCTION);
	_delay_ms(1);
	send_half_byte(0x02);
	_delay_ms(1);
	send_byte(0b00101000, 0);
	_delay_ms(1);
	send_byte(0b00001100, 0);
	_delay_ms(1);
	send_byte(0b00000110, 0);
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

static void print_lcd(uint8_t string[])
{
	for(int i = 0; string[i]; i++)
	{
		send_char(string[i]);
	}
}

int main01(void)
{
	port_init();
	lcd_init();
	set_position(0, 0);
	print_lcd("Hello World!");
	set_position(3, 1);
	print_lcd("Second s");
		
    while (1) 
    {
    }
}

