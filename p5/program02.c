/*
* �������� 2. ��������� �������� �� �����.
*
* ����������� ��������: �������� ������ �� LCD.
*
* ����������:
* - ������������� ATmega16;
* - LCD ������� LM016L;
*
* LCD - ��������������� ���������� �������. 
* LM016L ������� ���������� � ������ ����������� �� 
* ���������� HD44780, ���� ���� �������. ����� �� 
* ������� ���������� ����� ���������.
* ���� �������� ����� ������ �� ����������� HD44780,
* ���� ����� ������ � ������������ �� �����.
* ������ LM016L �������:
* - VSS   - "�����";
* - VDD   - ��������;
* - RS    - ������� ��� ���������� ����������:
*           0 - �������;
*	        1 - ����;
* - RW    - ������ ����������� ����������:
*           0 - ����� � ��������� �������;
*	        1 - ���������� �� ����������;
* - E     - ��� ���� �������� �� ������ �����
*           �� 1 �� 0 ���������� ������
*		    ������/���������� ����������;
* - D0-D7 - ���������� 8-�� ���� �����
*           ������ � �������;
* �� ���� ���� �� ������� ����� �������� ���� ����.
* ���� ��� ������ ����������� ����� � ��������� 
* �������:
* 1) �������� ����� �� ���� ����; ��� ����� 
*    ���������������� �� ��� ������ D0-D7;
* 2) �������� ����� �� ��� �����; ��� ����� 
*    ���������������� ����� ������ ������ D4-D7; 
*    ���������� ���������� ���������, ��� 
*    ��������������� ����� ������;
*    � ������ ����� ���� ���������� ����������
*    �������� ������ 4-�� ��� ���� �������;
* ���� ������ ����������� ��� ������������ �������.
*
* ������ ���������� ATmega168 ��� 4-�� ����� ������ LCD,
* �������� �� �������:
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

#include "lcd.h" 

 /* ������������ ������ �������������� ATmega168. */
void port_init(void)
{
	PORTD = 0x00;
	DDRD = 0xFF;
}

int main(void)
{
	port_init();
	lcd_init();
	set_position(0, 0);
	print_lcd("Hello World!");
	set_position(3, 1);
	print_lcd("Hello AVR!");
		
    while (1) 
    {
    }
}
