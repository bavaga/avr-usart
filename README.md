#AVR-USART

AVR-USART is my collection of useful methods to configure USART on AVRs.

Currently supported AVRs are:
* ATMEGA164A
* ATMEGA164PA
* ATMEGA324A
* ATMEGA324PA
* ATMEGA644A
* ATMEGA644PA
* ATMEGA1284
* ATMEGA1284PA

## Installation
1. Copy `usart.h` and `usart.c` to your project source folder.
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
