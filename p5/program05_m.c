/*
* Програма 5.0. Робота з spi інтерфейсом.
*
* Призначення програми: передача байту інформації між 
* двома мікроконтролерами по SPI інтерфейсу та 
* відображення переданого байту за допомогою світлодіодів.
*
* Даний вихідний код завантажується в керуючий контролер.
*
* Обладнання:
* - мікроконтролер ATmega168;
* - набір із восьми логічних ключів DIPSWC_8.
*
*
*
*/

#define F_CPU              1000000UL                   /* Тактова частота процесора. */
#include <avr/io.h>
#include <util/delay.h>

#define MOSI               DDB3
#define SCK                DDB5
#define SS                 DDB2

/* Ініціалізація виводів мікроконтролеру ATmega168. */
void port_init(void)
{
    /* Входи для передачі байту. */
	DDRD = 0x00;
	
	/* Ініціалізація SPI інтерфейсу. */
	
    DDRB = (1<<MOSI)|(1<<SCK)|(1<<SS);                 /*   Set MOSI and SCK output, all others input */
	PORTB = 0x00;
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);               /* Enable SPI, Master, set clock rate fck/16 */
	SPDR = 0x00;
}

void spi_transmit(uint8_t byte)
{
    SPDR = byte;                                       /* Start transmission */
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
	//uint8_t temp = SPSR;
	//temp = SPDR;
	//temp++;
	//SPSR &= ~(1<<SPIF);
}

int main(void)
{
	port_init();
	
    while (1)
    {
		spi_transmit(PIND);
		_delay_ms(100);
    }
}

