/*
* Програма 5.0. Робота з spi інтерфейсом.
*
* Призначення програми: передача байту інформації між 
* двома мікроконтролерами по SPI інтерфейсу та 
* відображення переданого байту за допомогою світлодіодів.
*
* Даний вихідний код завантажується в аерований контролер.
*
* Обладнання:
* - мікроконтролер ATmega168;
* - вісім світлодіодів та резисторів.
*
*
*
*
*/

#define F_CPU              1000000UL                   /* Тактова частота процесора. */
#include <avr/io.h>
#include <util/delay.h>

#define MISO               DDB4

/* Ініціалізація виводів мікроконтролеру ATmega168. */
void port_init(void)
{
    /* Входи для передачі байту. */
	PORTD = 0x00;
	DDRD = 0xFF;
	
	/* Ініціалізація SPI інтерфейсу. */
    DDRB = (1<<MISO);                                  /* Set MISO output, all others input */
    SPCR = (1<<SPE);                                   /* Enable SPI */
	SPDR = 0x00;
}

uint8_t spi_receive(void)
{
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)));
    /* Return Data Register */
    return SPDR;
}

void display(uint8_t byte)
{
	PORTD = byte;
}

int main(void)
{
	port_init();
	
    while (1)
    {
        display(spi_receive());
    }
}

