#include <avr/io.h>


int main1(void)
{
	// ������������ �����
	PORTB = (1<<PB5); // ���������� �� 5 ����� B � 1
	DDRB = (1<<DDB5);    // ���������� �� 5 ����� B �� �����
	
	// ���������� ����
	while (1)
	{
	}
}

