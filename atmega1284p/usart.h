/*
 * atmega1284p/usart.h
 *
 * USART configuration for
 * 		- ATMEGA164A
 * 		- ATMEGA164PA
 * 		- ATMEGA324A
 * 		- ATMEGA324PA
 * 		- ATMEGA644A
 * 		- ATMEGA644PA
 * 		- ATMEGA1284
 * 		- ATMEGA1284P
 *
 * Created on: 11.09.2014
 *     Author: Wilhelm Haas
 *     E-Mail: wilhelm.haas@bavaga.com
 *    Website: http://embedded.bavaga.com
 *
 *
 * Examples 1 (writing "Hello World" to usart0):
 * 		usart_set_baud(&usart0, USART_BAUD_RATE_9600);
 * 		usart_enable_writing(&usart0);
 * 		usart_write(&usart0, 'H');
 * 		usart_write(&usart0, 'e');
 * 		usart_write(&usart0, 'l');
 * 		usart_write(&usart0, 'l');
 * 		usart_write(&usart0, 'o');
 * 		usart_write(&usart0, ' ');
 * 		usart_write(&usart0, 'W');
 * 		usart_write(&usart0, 'o');
 * 		usart_write(&usart0, 'r');
 * 		usart_write(&usart0, 'l');
 * 		usart_write(&usart0, 'd');
 * 		usart_write(&usart0, '!');
 *
 * Example 2 (reading from usart0):
 * 		usart_set_baud(&usart0, USART_BAUD_RATE_9600);
 * 		usart_enable_reading(&usart0);
 * 		char c = usart_read(&usart0);
 *
 * TODO:
 * 		* Add interrupts
 * 		* Use buffers
 *
 */

#ifndef USART_BAVAGA_AVR_ATMEGA1284P_H_
#define USART_BAVAGA_AVR_ATMEGA1284P_H_

#include <inttypes.h>
#include <stdbool.h>

typedef enum {
	USART_BAUD_RATE_300 = 300,
	USART_BAUD_RATE_600 = 600,
	USART_BAUD_RATE_1200 = 1200,
	USART_BAUD_RATE_1800 = 1800,
	USART_BAUD_RATE_2400 = 2400,
	USART_BAUD_RATE_4000 = 4000,
	USART_BAUD_RATE_4800 = 4800,
	USART_BAUD_RATE_7200 = 7200,
	USART_BAUD_RATE_9600 = 9600,
	USART_BAUD_RATE_14400 = 14400,
	USART_BAUD_RATE_16000 = 16000,
	USART_BAUD_RATE_19200 = 19200,
	USART_BAUD_RATE_28800 = 28800,
	USART_BAUD_RATE_38400 = 38400,
	USART_BAUD_RATE_51200 = 51200,
	USART_BAUD_RATE_56000 = 56000,
	USART_BAUD_RATE_57600 = 57600,
	USART_BAUD_RATE_64000 = 64000,
	USART_BAUD_RATE_76800 = 76800,
	USART_BAUD_RATE_115200 = 115200,
	USART_BAUD_RATE_128000 = 128000,
	USART_BAUD_RATE_153600 = 153600,
	USART_BAUD_RATE_230400 = 230400,
	USART_BAUD_RATE_250000 = 250000,
	USART_BAUD_RATE_256000 = 256000,
	USART_BAUD_RATE_460800 = 460800,
	USART_BAUD_RATE_500000 = 500000,
	USART_BAUD_RATE_576000 = 576000,
	USART_BAUD_RATE_921600 = 921600,
	USART_BAUD_RATE_1000000 = 1000000
} UsartBaudRate;

typedef enum {
	USART_MODE_ASYNCHRONOUS = 0,
	USART_MODE_SYNCHRONOUS = 1,
	USART_MODE_SYNCHRONOUS_MASTER = 2,
	USART_MODE_MASTER_SPI = 3
} UsartMode;

typedef enum {
	USART_PARITY_MODE_DISABLED = 0,
	USART_PARITY_MODE_EVEN_PARITY = 2,
	USART_PARITY_MODE_ODD_PARITY = 3
} UsartParityMode;

typedef enum {
	USART_ONE_STOP_BITS = 1, USART_TWO_STOP_BITS = 2
} UsartNumberOfStopBits;

typedef enum {
	USART_FIVE_BITS_CHARACTER_SIZE = 5,
	USART_SIX_BITS_CHARACTER_SIZE = 6,
	USART_SEVEN_BITS_CHARACTER_SIZE = 7,
	USART_EIGHT_BITS_CHARACTER_SIZE = 8,
	USART_NINE_BITS_CHARACTER_SIZE = 9
} UsartCharacterSize;

typedef enum {
	USART_CLOCK_POLARITY_OUTPUT_ON_RISING_AND_INPUT_ON_FALLING_EDGE = 0,
	USART_CLOCK_POLARITY_OUTPUT_ON_FALLING_AND_INPUT_ON_RISING_EDGE = 1
} UsartClockPolarity;

typedef struct {
	/* Registers */
	volatile uint8_t* ubrrh;
	volatile uint8_t* ubrrl;
	volatile uint8_t* ucsra;
	volatile uint8_t* ucsrb;
	volatile uint8_t* ucsrc;
	volatile uint8_t* udr;
	volatile uint8_t* ddr_xck;


	/* Flags */
	uint8_t u2x;		// u2x bit
	uint8_t rxen;		// enable reading
	uint8_t txen;		// enable writing
	uint8_t udre;
	uint8_t rxc;
	uint8_t umsel1;		// Usart mode
	uint8_t umsel0;		// Usart mode
	uint8_t upm1;		// Parity mode
	uint8_t upm0;		// Parity mode
	uint8_t usbs;		// Number of stop bits
	uint8_t ucsz2;		// Character size
	uint8_t ucsz1;		// Character size
	uint8_t ucsz0;		// Character size
	uint8_t ucpol;		// Clock polarity
	uint8_t xck;		// XCK Pin


} UsartDescriptor;

extern UsartDescriptor usart0;
extern UsartDescriptor usart1;

#ifdef __cplusplus
extern "C" {
#endif

void usart_set_mode(UsartDescriptor* usart, UsartMode mode);

bool usart_is_mode(UsartDescriptor* usart, UsartMode mode);

void usart_set_parity_mode(UsartDescriptor* usart, UsartParityMode mode);

void usart_set_number_of_stop_bits(UsartDescriptor* usart,
		UsartNumberOfStopBits number_of_stop_bits);

void usart_set_character_size(UsartDescriptor* usart,
		UsartCharacterSize character_size);

void usart_set_clock_polarity(UsartDescriptor* usart,
		UsartClockPolarity polarity);

void usart_set_baud(UsartDescriptor* usart, unsigned long baud);

void usart_enable_reading(UsartDescriptor* usart);

void usart_enable_writing(UsartDescriptor* usart);

void usart_enable_reading_and_writing(UsartDescriptor* usart);

void usart_disable_reading(UsartDescriptor* usart);

void usart_disable_writing(UsartDescriptor* usart);

void usart_disable_reading_and_writing(UsartDescriptor* usart);

bool usart_is_reading_enabled(UsartDescriptor* usart);

bool usart_is_writing_enabled(UsartDescriptor* usart);

bool usart_data_received(UsartDescriptor* usart);

bool usart_data_sent(UsartDescriptor* usart);

void usart_write(UsartDescriptor* usart, uint8_t c);

uint8_t usart_read(UsartDescriptor* usart);

#ifdef __cplusplus
}
#endif

#endif /* USART_BAVAGA_AVR_ATMEGA1284P_H_ */
