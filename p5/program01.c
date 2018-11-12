/*
* �������� 0. ������ � LCD �������.
*
* ����������� ��������: �������� ������ �� �������.
*
* ����������:
* - ������������� ATmega168
* - LCD �������;
*
* 7seg-mpx4-ca ������� ���������� �� �������� ��������������
* ����������. ���������� ���������� �� ���� �� ��������� ������,
* ����� �� �������� (���������) ���������� �'����� �����
* ������� � �������� ��������. ������ �������������� �����������
* �� ������ ���������. ��� ���������� �� ���������
* ����� ����� ������� ���������� ����� ��������� ���������,
* � ����� ��������� ������� ���� ��������.
* ��� ����, ��� �������� ���������� �� ��������� ������
* ��������� �� ���� ����� ������� ���� ��������� ������ ��
* ��������� �����. ����, ��� ��������� ������� ��������
* ���������� �� ���������� ����� �������������� �������
* ���� ������������ ������� ����. ��� ��������� �������� ��
* ����� ������� ���� ������ �������.
*
* ������ � ����� ����� ������� �� ��� ����������. � �����
* ������ ���� ����� �������� ����� ����� �� ���� ���������
* �������. ����, � ����� ������ ���� ��������� ����� ����
* ���������, � �� ���� �������.
* ���� ��������� ������� ����� ��������� ������� ����� ������
* ����� ������� ����, ���� ������ �� ��� ������� ��� ������,
* �� ���������� �������, �� �� �������� ������� �������
* ���������.
* � ��������� PROTEUS ��� ������� 7seg-mpx4-ca ��� ��� < 10 ��.
*
* ������� 7seg-mpx4-ca ������ ��� ������ ������:
* - ������ ������ ��� ������, �������� "ABCDEFG DP";
* - ������ ������ ������ ������, �������� "1234".
* ������ ���� ������ ���� ���������� ����������� ����������.
* "ABCDEFG" ������ ������� ���������� (�����������)
* ���������� ��� ����������� �����.
* "DP" ���� ���� ����������, ���� �������� ��������� �����
* � ������� �������� ��� ����������.
* ������ ���� ������ ����� ������ ����������� ����������
* �������.
*
* ������ ����� D ������� �� ������ "ABCDEFG DP" �������:
* PD0-"A", PD1-"B", ..., PD6-"G", PD7-"DP".
* ������ PB0-PB3 ������� �� ������ "1234":
* PB0-"1", PB1-"2", PB2-"3", PB3-"4".
*
*/
#define F_CPU              1000000UL
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

