#ifndef LCD_H_
#define LCD_H_

#define F_CPU              1000000UL                   /* Тактова частота процесора. */
#include <avr/io.h>
#include <util/delay.h>

#define E_ON               PORTD |= (1<<PD3)           /* Подача 1 на E вхід дисплею. */
#define E_OFF              PORTD &= ~(1<<PD3)          /* Подача 0 на E вхід дисплею. 
                                                          Початок процесу обміну інформацією. */
#define START_DATA         PORTD |= (1<<PD2)           /* Подача 1 на RS вхід дисплею. 
                                                          Передача даних. */
#define DATA               1
#define START_COMMAND      PORTD &= ~(1<<PD2)          /* Подача 0 на RS вхід дисплею. 
                                                          Передача команд. */
#define COMMAND            0
#define CLEAR_DATA_PINS    PORTD &= 0x0F;              /* Стираємо інформацію на входах D4-D7
                                                          дисплею. */
#define SEND_DATA(d)       PORTD |= d;                 /* Передача інформації в нонтролер дисплея. */ 

/* Інфтрукції ініціалізації контролеру LED дисплею. */
#define INIT_INSTRUCTION_1  0b00000011
#define INIT_INSTRUCTION_2  0b00000010
#define FUNCTION_SET        0b00101000                 /* Встановлення 4-біт режиму, активація 2-х строк 
                                                          та вибір шрифту. */
#define DISPLAY_ON          0b00001100
#define DISPLAY_CLEAR       0b00000001
#define ENTRY_MODE_SET      0b00000110

/* Функція передає молодшу половину байта в контролер дисплею. 
   (4-біт режим)*/
void send_half_byte(uint8_t halfByte);

/* Вивід байту інформації на дисплей. */
void send_byte(uint8_t byte, uint8_t mode);

/* Ініціалізація контролеру дисплея. */
void lcd_init(void);

/* Передача одного символу. */
void send_char(uint8_t ch);

/* Встановлення позиції курсора. */
void set_position(uint8_t h, uint8_t v);

/* Передача строки на дисплей. */
void print_lcd(uint8_t string[]);

#endif /* LCD_H_ */ 

