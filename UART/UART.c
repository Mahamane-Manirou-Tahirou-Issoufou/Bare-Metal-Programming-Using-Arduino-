#include<stdint.h>
#include<stdbool.h>
#include<avr/io.h>
#include<avr/interrupt.h>

void UART_init(uint32_t baudrate){


uint16_t ubrr_value = (F_CPU / (16UL * baudrate)) - 1;
UBRR0H = (uint8_t)(ubrr_value >> 8); // Set high byte of UBRR
UBRR0L = (uint8_t)(ubrr_value );     // Set low byte of UBRR
UCSR0B = (1 << RXEN0) | (1 << TXEN0); // Enable receiver and transmitter
UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Set frame format: 8data, 1stop bit

}
void UART_sendByte(uint8_t data){
while(!(UCSR0A & (1 << UDRE0))); // Wait until buffer is    empty
UDR0 = data; // Put data into buffer, sends the data
}
void printString(const char* str){
while(*str){
UART_sendByte(*str++);
}
}
void printInt(int32_t value){
char buffer[12]; // Buffer to hold the string representation
ultoa(value, buffer, 10); // Convert integer to string 
printString(buffer); // Print the string
}  
