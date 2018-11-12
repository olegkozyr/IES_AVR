/*
* �������� 0. ������ � LCD ������� � 4-������ �����.
*
* ����������� ��������: �������� ������� ������� �� LCD.
*
* ����������:
* - ������������� ATmega168
* - LCD ������� LM016L;
*
* LCD - ��������������� ���������� �������. 
* LM016L ������� * ���������� � ������ ����������� �� 
* ���������� HD44780, * ���� ���� �������. ���� �� 
* ������� ���������� ����� ���������.
* ���� �������� ����� ������ �� ���������� HD44780,
* ���� ����� ������ � ������������ �� �����.
* ������ LM016L �������:
* - VSS   - "�����";
* - VDD   - ��������;
* - RS    - ������� ��� ���������� ����������:
*           0 - �������;
*	    1 - ���;
* - RW    - ������ ����������� ����������:
*           0 - ����� � ��������� �������;
*	    1 - ���������� �� ����������;
* - E     - ��� ��� �������� �� ������ �����
*           �� 1 �� 0 ���������� ������
*		������/���������� ����������;
* - D0-D7 - ���������� 8-�� ���� ������/����������
*           ����� � �������;
* �� ���� ���� �� ������� ������������� ���� ����.
* ���� ��� ������ ����������� ����� � ��������� 
* �������:
* 1) �������� ����� �� ���� ����; ��� ����� 
*    ���������������� �� ��� ������ D0-D7;
* 2) �������� ����� �� ��� �����; ��� ����� 
*    ���������������� ����� ������ ������ D4-D7; 
*    ���������� ���������� ��������, ��� 
*    ��������������� ����� ������;
*    � ������ ����� ���� ���������� ����������
*    �������� ������ 4-�� ��� ���� �������;
* ���� ������ ����������� ��� ����������� �������.
*
* ������ ���������� ATmega168 ������� �� �������:
* PD2 - RS
* PD3 - E
* PD4 - D4
* PD5 - D5
* PD6 - D6
* PD7 - D7
*
* ������ �������:
* VSS -	��������� �� "����" ;
* VDD - �� ��������;
* RW - �� ��������� ���������� - ����� � ��������� �������.
*
*/
#define F_CPU              1000000UL                   /* ������� ������� ���������. */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define E_ON               PORTD |= (1<<PD3)           /* ������ 1 �� E ���� �������. */
#define E_OFF              PORTD &= ~(1<<PD3)          /* ������ 0 �� E ���� �������. */
#define START_DATA         PORTD |= (1<<PD2)           /* ������ 1 �� RS ���� �������. 
                                                          �������� �����. */
#define START_COMMAND      PORTD &= ~(1<<PD2)          /* ������ 0 �� RS ���� �������. 
                                                          �������� ������. */
#define CLEAR_DATA_PINS    PORTD &= 0x0F;             /* ������� ���������� �� ������ D4-D7
                                                          �������. */
#define SEND_DATA(d)       PORTD |= d;                 /* �������� ���������� � ��������� �������. */  
#define INIT_INSTRUCTION_1 0x03
#define INIT_INSTRUCTION_2 0x02
#define INIT_INSTRUCTION_3 0b00101000
#define INIT_INSTRUCTION_4 0b00001100
#define INIT_INSTRUCTION_5 0b00000110

/* ����������� ������ �������������� ATmega168. */
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

/* ����������� ���������� �������. */
static void lcd_init(void)
{
	_delay_ms(15);                                     /* �������� ��� ������������ �������� �������. */
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

