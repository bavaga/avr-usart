/*
 * atmega1284p/usart.c
 *
 * USART configuration for AVR ATMEGA1284P
 *
 * Created on: 11.09.2014
 *     Author: Wilhelm Haas
 *     E-Mail: wilhelm.haas@bavaga.com
 *    Website: http://embedded.bavaga.com
 */

#include "usart.h"
#include <avr/io.h>
#include <stdlib.h>

UsartDescriptor usart0 = {
	.ubrrh = &UBRR0H,
	.ubrrl = &UBRR0L,
	.ucsra = &UCSR0A,
	.ucsrb = &UCSR0B,
	.ucsrc = &UCSR0C,
	.udr = &UDR0,
	.ddr_xck = &DDRB,

	.u2x = U2X0,
	.rxen = RXEN0,
	.txen = TXEN0,
	.udre = UDRE0,
	.rxc = RXC0,
	.umsel1 = UMSEL01,
	.umsel0 = UMSEL00,
	.upm1 = UPM01,
	.upm0 = UPM00,
	.usbs = USBS1,
	.ucsz2 = UCSZ02,
	.ucsz1 = UCSZ01,
	.ucsz0 = UCSZ00,
	.ucpol = UCPOL0,
	.xck = PB0
};

UsartDescriptor usart1 = {
	.ubrrh = &UBRR1H,
	.ubrrl = &UBRR1L,
	.ucsra = &UCSR1A,
	.ucsrb = &UCSR1B,
	.ucsrc = &UCSR1C,
	.udr = &UDR1,
	.ddr_xck = &DDRD,

	.u2x = U2X1,
	.rxen = RXEN1,
	.txen = TXEN1,
	.udre = UDRE1,
	.rxc = RXC1,
	.umsel1 = UMSEL11,
	.umsel0 = UMSEL10,
	.upm1 = UPM11,
	.upm0 = UPM10,
	.usbs = USBS1,
	.ucsz2 = UCSZ12,
	.ucsz1 = UCSZ11,
	.ucsz0 = UCSZ10,
	.ucpol = UCPOL1,
	.xck = PD4
};

void usart_set_mode(UsartDescriptor* usart, UsartMode mode) {
	switch (mode) {
		case USART_MODE_ASYNCHRONOUS:
			*usart->ucsrc &= ~(_BV(usart->umsel1) | _BV(usart->umsel0));
			break;
		case USART_MODE_SYNCHRONOUS:
			*usart->ddr_xck &= ~(_BV(usart->xck));
			*usart->ucsrc &= ~(_BV(usart->umsel1));
			*usart->ucsrc |= _BV(usart->umsel0);
			break;
		case USART_MODE_SYNCHRONOUS_MASTER:
			*usart->ddr_xck |= _BV(usart->xck);
			*usart->ucsrc &= ~(_BV(usart->umsel1));
			*usart->ucsrc |= _BV(usart->umsel0);
			break;
		case USART_MODE_MASTER_SPI:
			*usart->ddr_xck |= _BV(usart->xck);
			*usart->ddr_xck |= _BV(usart->xck);
			*usart->ucsrc |= _BV(usart->umsel1) | _BV(usart->umsel0);
			break;
		default:
			break;
	}
}

bool usart_is_mode(UsartDescriptor* usart, UsartMode mode) {
	uint8_t mask = ((*usart->ucsrc & _BV(usart->umsel1)) >> (usart->umsel1 - 1)) |
			((*usart->ucsrc & _BV(usart->umsel0)) >> usart->umsel0);

	if (mask == USART_MODE_SYNCHRONOUS) {
		if (*usart->ddr_xck & _BV(usart->xck)) {
			if (mode == USART_MODE_SYNCHRONOUS_MASTER) {
				return true;
			} else if (mode == USART_MODE_SYNCHRONOUS) {
				return false;
			}
		}
	}

	return mask == mode;
}

void usart_set_parity_mode(UsartDescriptor* usart, UsartParityMode mode) {
	switch (mode) {
		case USART_PARITY_MODE_DISABLED:
			*usart->ucsrc &= ~(_BV(usart->upm1) | _BV(usart->upm0));
			break;
		case USART_PARITY_MODE_EVEN_PARITY:
			*usart->ucsrc |= _BV(usart->upm1);
			*usart->ucsrc &= ~(_BV(usart->upm0));
			break;
		case USART_PARITY_MODE_ODD_PARITY:
			*usart->ucsrc |= _BV(usart->upm1) | _BV(usart->upm0);
			break;
		default:
			break;
	}
}

void usart_set_number_of_stop_bits(UsartDescriptor* usart,
		UsartNumberOfStopBits number_of_stop_bits) {
	switch (number_of_stop_bits) {
		case USART_TWO_STOP_BITS:
			*usart->ucsrc |= _BV(usart->usbs);
			break;
		default:
			*usart->ucsrc &= ~(_BV(usart->usbs));
			break;
	}
}

void usart_set_character_size(UsartDescriptor* usart,
		UsartCharacterSize character_size) {

	switch (character_size) {
		case USART_FIVE_BITS_CHARACTER_SIZE:
			*usart->ucsrb &= ~(_BV(usart->ucsz2));
			*usart->ucsrc &= ~(_BV(usart->ucsz1) | _BV(usart->ucsz0));
			break;
		case USART_SIX_BITS_CHARACTER_SIZE:
			*usart->ucsrb &= ~(_BV(usart->ucsz2));
			*usart->ucsrc &= ~(_BV(usart->ucsz1));
			*usart->ucsrc |= _BV(usart->ucsz0);
			break;
		case USART_SEVEN_BITS_CHARACTER_SIZE:
			*usart->ucsrb &= ~(_BV(usart->ucsz2));
			*usart->ucsrc |= _BV(usart->ucsz1);
			*usart->ucsrc &= ~(_BV(usart->ucsz0));
			break;
		case USART_EIGHT_BITS_CHARACTER_SIZE:
			*usart->ucsrb &= ~(_BV(usart->ucsz2));
			*usart->ucsrc |= _BV(usart->ucsz1);
			*usart->ucsrc |= _BV(usart->ucsz0);
			break;
		case USART_NINE_BITS_CHARACTER_SIZE:
			*usart->ucsrb |= _BV(usart->ucsz2);
			*usart->ucsrc |= _BV(usart->ucsz1);
			*usart->ucsrc |= _BV(usart->ucsz0);
			break;
		default:
			break;
	}
}

void usart_set_clock_polarity(UsartDescriptor* usart,
		UsartClockPolarity polarity) {
	switch (polarity) {
		case USART_CLOCK_POLARITY_OUTPUT_ON_RISING_AND_INPUT_ON_FALLING_EDGE:
			*usart->ucsrc &= ~(_BV(usart->ucpol));
			break;
		case USART_CLOCK_POLARITY_OUTPUT_ON_FALLING_AND_INPUT_ON_RISING_EDGE:
			*usart->ucsrc &= _BV(usart->ucpol);
			break;
		default:
			break;
	}
}

void usart_set_baud(UsartDescriptor* usart, unsigned long baud) {
	uint16_t ubrr;

	if (usart_is_mode(usart, USART_MODE_ASYNCHRONOUS)) {
		bool use_u2x = false;

		uint16_t ubrr_without_u2x = F_CPU / 16 / baud - 1;
		unsigned long error_without_u2x = abs(
				baud - ((ubrr_without_u2x + 1) * 16 * baud) / F_CPU);

		uint16_t ubrr_with_u2x = F_CPU / 8 / baud - 1;
		unsigned long error_with_u2x = abs(
				baud - ((ubrr_with_u2x + 1) * 8 * baud) / F_CPU);

		if (error_without_u2x < error_with_u2x) {
			use_u2x = false;
			ubrr = ubrr_without_u2x;
		} else {
			use_u2x = true;
			ubrr = ubrr_with_u2x;
		}

		if (use_u2x) {
			*usart->ucsra = 1 << usart->u2x;
		}
	} else if (usart_is_mode(usart, USART_MODE_SYNCHRONOUS_MASTER)
			|| usart_is_mode(usart, USART_MODE_MASTER_SPI)) {
		ubrr = F_CPU / 2 / baud - 1;
	} else {
		ubrr = 0;
	}
	*usart->ubrrh = ubrr >> 8;
	*usart->ubrrl = ubrr;
}

void usart_enable_reading(UsartDescriptor* usart) {
	*usart->ucsrb |= _BV(usart->rxen);
}

void usart_enable_writing(UsartDescriptor* usart) {
	*usart->ucsrb |= _BV(usart->txen);
}

void usart_enable_reading_and_writing(UsartDescriptor* usart) {
	usart_enable_reading(usart);
	usart_enable_writing(usart);
}

void usart_disable_reading(UsartDescriptor* usart) {
	*usart->ucsrb &= ~(_BV(usart->rxen));
}

void usart_disable_writing(UsartDescriptor* usart) {
	*usart->ucsrb &= ~(_BV(usart->txen));
}

void usart_disable_reading_and_writing(UsartDescriptor* usart) {
	usart_disable_reading(usart);
	usart_disable_writing(usart);
}

bool usart_is_reading_enabled(UsartDescriptor* usart) {
	return !!(*usart->ucsrb & _BV(usart->rxen));
}

bool usart_is_writing_enabled(UsartDescriptor* usart) {
	return !!(*usart->ucsrb & _BV(usart->txen));
}

bool usart_data_received(UsartDescriptor* usart) {
	return !!(*usart->ucsra & (1 << usart->rxc));
}

bool usart_data_sent(UsartDescriptor* usart) {
	return !!(*usart->ucsra & (1 << usart->udre));
}

void usart_write(UsartDescriptor* usart, uint8_t c) {
	while (!usart_data_sent(usart))
		;
	*usart->udr = c;
}

uint8_t usart_read(UsartDescriptor* usart) {
	while (!usart_data_received(usart))
		;
	return *usart->udr;
}
