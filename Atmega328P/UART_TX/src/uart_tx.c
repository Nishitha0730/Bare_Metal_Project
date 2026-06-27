#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdint.h>

#define baud_rate 9600U
#define fosc 16000000UL  // system clk 16MHz


// Async uart
#define UCSR0C *(volatile uint8_t *)0xC2 
#define UCSR0B *(volatile uint8_t *)0xC1
#define UCSR0A *(volatile uint8_t *)0xC0

#define UMSELn1 7
#define UMSELn0 6

// Frame format
#define UCSZn0 1  // 8 bit frame
#define UCSZn1 2
#define UCSZn2 2
#define UPMn0 4
#define UPMn1 5
#define USBSn 3

#define TXENn 3


#define TXCIEn 6
#define TXCn 6
#define UDRIEn 5
#define UDREn 5

#define TXB8n 0   // UART 9 th bit

#define SREG *(volatile uint8_t *)0x5F 
#define  Global_Interrupt_Enable 7


// Baud rate register
#define UBRR0H *(volatile uint8_t *)0xC5
#define UBRR0L *(volatile uint8_t *)0xC4

// USART I/O Data Register
#define UDR0 *(volatile uint8_t *)0xC6

char data[]={'a','b'};
volatile uint8_t buffer_empty = 1;
uint8_t data_index = 0;

volatile uint8_t lower_data_send=0;

 /* USART, Data Register Empty */
ISR(USART_UDRE_vect){
    buffer_empty = 1; 
    
}

  /* USART Tx Complete */
// ISR(USART_TX_vect){
//     tx_complete=true;
// }

int main(void){
    // UCSR0C = (1 << UPMn1) | (1 << UPMn0) | (1 << USBSn) | (1 << UCSZn1) | (1 << UCSZn0);
    UCSR0C = (1 << UCSZn1) | (1 << UCSZn0);

    // UCSR0C |= (1<<UCSZn0) | (1<<UCSZn1); // 8 bit frame set  

    UCSR0C |= (1<<UCSZn0) | (1<<UCSZn1) | (1<<UCSZn2); // 9 bit frame set

    // 5 bit UART
    // UCSR0C &= ~(1<<UCSZn0);
    // UCSR0C &= ~(1<<UCSZn1);

    UCSR0C |= (1<<UPMn0)|(1<<UPMn1);  // enable odd parity
    UCSR0C |= (1<<USBSn); // 2 bit stop
    UCSR0C &= ~(1<<UMSELn1); // enable async mode
    UCSR0C &= ~(1<<UMSELn0); 


    UCSR0B |= (1<<TXENn);  // Enable transmitter

    UCSR0B &= ~(1<<UCSZn2);// 8 bit frame set

    // Clear  global interrupt flag
    SREG &= ~(1<<Global_Interrupt_Enable);

    // USART transmit complete interrupt will be generate
    // UCSR0B |= (1<<TXCIEn);
    // UCSR0A |= (1<<TXCn);

    // Data register empty interrupt will be generated
    UCSR0B |= (1<<UDRIEn);   
    UCSR0A |= (1<<UDREn);

    // Set baud rate
    UBRR0H=0x00;
    UBRR0L = 0x67;   // 9600bps

    // Set  global interrupt flag
    SREG |= (1<<Global_Interrupt_Enable);

    while(1){
        if(buffer_empty){
            // buffer_empty = 0;
            if(data_index>=sizeof(data)){
                UCSR0B &= ~(1<<UDRIEn);
            }else{
                uint8_t upper_data = data[data_index % sizeof(data)] >>5;
                uint8_t lower_data = data[data_index % sizeof(data)];

                // UDR0 = data[data_index % sizeof(data)] & 0x0F;

                UCSR0B |= (1<<UCSR0B);  // 9 th bit

                if(!lower_data_send){
                    lower_data_send=1;
                    UDR0 = lower_data;
                }else{
                    UDR0 = upper_data;
                    lower_data_send=0;
                    data_index++;
                }

                // data_index++;
                buffer_empty = 0;
            }
        }

    }


    return 0;
}