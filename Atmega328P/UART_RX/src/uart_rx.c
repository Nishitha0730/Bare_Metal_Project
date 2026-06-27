#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>

#define UDR0 *(volatile uint8_t *)0xC6
#define UBRR0H *(volatile uint8_t *)0xC5
#define UBRR0L *(volatile uint8_t *)0xC4

#define UCSR0C *(volatile uint8_t *)0xC2
#define UCSR0B *(volatile uint8_t *)0xC1
#define UCSR0A *(volatile uint8_t *)0xC0


#define UMSELn1 7
#define UMSELn0 6
#define UPMn1 5
#define UPMn0 4
#define USBSn 3
#define UCSZn1 2
#define UCSZn0 1

#define UCSZn2 2

#define RXCn 7
#define RXCIEn 7


#define SREG *(volatile uint8_t *)0x5F
#define GI 7

#define RXENn 4

#define TXENn 3

volatile char data='a';

volatile uint8_t rx_complete = 0;

ISR(USART_RX_vect){
    rx_complete=1;
}

int main(void){
    SREG &= ~(1<<GI);

    UCSR0C &= ~((1<<UMSELn1) | (1<<UMSELn0)); // Async UART

    UCSR0C &= ~(1<<UPMn1); //parity disable
    UCSR0C &= ~(1<<UPMn0);

    UCSR0C &= ~(1<<USBSn); // 1 bit stop

    UCSR0C |= (1<<UCSZn1) | (1<<UCSZn0);  // 8 bit UART
    UCSR0B &= ~(1<<UCSZn2); 

    UBRR0H=0x00;
    UBRR0L=0x67;  // 9600bps

    UCSR0B |= (1<<RXCIEn); // enble rx interrupt
    UCSR0A |= (1<<RXCn); 

    UCSR0B |= (1<<RXENn);  // enable rx
    SREG |= (1<<GI);

    while(1){
        if(rx_complete){
            data = UDR0;
            rx_complete=0;

            // UCSR0B &= ~(1<<RXENn);  // disable rx

            UCSR0B |= (1<<TXENn);  // enable tx
            UDR0 = data;

        }


    }


    return 0;
}