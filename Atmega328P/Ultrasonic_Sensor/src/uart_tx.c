#include "uart_tx.h"

void Uart_Init(void){
    // disable global interrupt
    SREG &= ~(1<<GIE);

    UCSR0C &= ~((1<<UMSELn1) | (1<<UMSELn0)); // Async UART
    UCSR0C &= ~((1<<UPMn1) | (1<<UPMn0));  // parity disabled
    UCSR0C &= ~(1<<USBSn);  // stop bit - 1bit
    UCSR0C |= (1<<UCSZn1) | (1<<UCSZn0);  // 8-bit data frame
    UCSR0B &= ~(1<<UCSZn2);

    UCSR0A &= ~(1<<U2Xn);

    // baud rate - 9600 bps 
    UBRR0H = 0x00;
    UBRR0L = 0x67;

    UCSR0B |= (1<<TXENn); // Enable transmitter

    SREG |= (1<<GIE);
    UCSR0B |= (1<<TXCIEn); // interrupt tx done enable

}