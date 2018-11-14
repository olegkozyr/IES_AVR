 #include "lcd.h" 
 
/* Функція передає молодшу половину байта в контролер дисплею. 
   (4-біт режим)*/
void send_half_byte(uint8_t halfByte)
{
	/* В аргументі halfByte використовуються тільки молодші
	   4 біти. 
	   В даному з'єднанні виводів мікроконтролеру та 
	   дисплею працюють тільки 4 старші виводи порту D.
       Тому, для передачі 4-х молодших бітів аргументу halfByte
	   потрібно виконати операцію зсуву на 4-ри біти. */
	halfByte <<= 4;
	
	E_ON;
	_delay_us(50);
	CLEAR_DATA_PINS;
	SEND_DATA(halfByte);
	E_OFF;
	_delay_us(50);
}

/* Вивід байту інформації на дисплей. */
void send_byte(uint8_t byte, uint8_t mode)
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
	
	uint8_t high_half_byte = 0x00;                     /* Тимчасова змінна для зберігання старших 
	                                                      4-біт аргументу "byte" в молодших 4-біт. */
	high_half_byte = byte >> 4;                        /* Зберігання старших 4-біт аргументу "byte"*/
	/* В 4-біт режимі в контролер дисплею, спочатку, 
	   передаються старші 4-біт, а потім
	   молодші 4-біт.*/
	send_half_byte(high_half_byte);                    /* Передача старших 4-біт. */
	send_half_byte(byte);                              /* Передача молодших 4-біт. */
}

/* Ініціалізація контролеру дисплея. */
void lcd_init(void)
{
	_delay_ms(15);                                     
	send_half_byte(INIT_INSTRUCTION_1);
	_delay_ms(5);
	send_half_byte(INIT_INSTRUCTION_1);
	_delay_us(100);
	send_half_byte(INIT_INSTRUCTION_1);
	_delay_ms(1);
	send_half_byte(INIT_INSTRUCTION_2);
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
void send_char(uint8_t ch)
{
	send_byte(ch, 1);
}

/* Встановлення позиції курсора. */
void set_position(uint8_t h, uint8_t v)
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

/* Передача строки на дисплей. */
void print_lcd(uint8_t string[])
{
	for(int i = 0; string[i]; i++)
	{
		send_char(string[i]);
	}
}