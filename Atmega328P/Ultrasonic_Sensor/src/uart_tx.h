#include <stdint.h>

#ifndef UART_TX
#define UART_TX

#define UDR0 *(volatile uint8_t *)0xC6
#define UBRR0H *(volatile uint8_t *)0xC5
#define UBRR0L *(volatile uint8_t *)0xC4

#define UCSR0C *(volatile uint8_t *)0xC2
#define UCSR0B *(volatile uint8_t *)0xC1
#define UCSR0A *(volatile uint8_t *)0xC0

#define SREG *(volatile uint8_t *)0x5F


#define UMSELn1 7
#define UMSELn0 6
#define UPMn1 5
#define UPMn0 4
#define USBSn 3
#define UCSZn1 2
#define UCSZn0 1

#define UCSZn2 2

#define U2Xn 1

#define TXENn 3

#define TXCIEn 6

#define GIE 7

#endif