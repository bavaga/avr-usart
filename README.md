#AVR-USART

AVR-USART is my collection of useful methods to configure USART on AVRs.

Currently I implemented some methods for AVR ATMEGA1284p but will extend it
in the future.

## Installation
1. Copy `usart.h` and `usart.c` into your project source folder.
2. Add `#include "usart.h"` into your source code

## Usage Examples

### Writing "Hello World"
    usart_set_baud(&usart0, USART_BAUD_RATE_9600);
    usart_enable_writing(&usart0);
    usart_write(&usart0, 'H');
    usart_write(&usart0, 'e');
    usart_write(&usart0, 'l');
    usart_write(&usart0, 'l');
    usart_write(&usart0, 'o');
    usart_write(&usart0, ' ');
    usart_write(&usart0, 'W');
    usart_write(&usart0, 'o');
    usart_write(&usart0, 'r');
    usart_write(&usart0, 'l');
    usart_write(&usart0, 'd');
    usart_write(&usart0, '!');

### Reading
    usart_set_baud(&usart0, USART_BAUD_RATE_9600);
    usart_enable_reading(&usart0);
    char c = usart_read(&usart0);

This is a work in progress!
