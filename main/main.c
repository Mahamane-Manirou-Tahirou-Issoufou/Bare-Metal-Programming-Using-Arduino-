#include<stdint.h>
#include<stdbool.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<stdlib.h>
#include "sysTime.h"
#include "UART.h"
#include "ADC.h"
#include "PWM.h"
uint32_t lastPotTime=0;
uint32_t lastPressTime=0;
uint32_t lastBlinkTime=0;
uint32_t lastCheckTime=0;
uint16_t BLINK_DURATION=0;
uint8_t brightness=0;
uint16_t potVal0=0;
uint16_t potVal1=0;
bool messageState=false;
static bool ledState=false;
//#include<math.h>
int main(void){
sei(); // Enable global interrupts
UART_init(9600); // Initialize UART with 9600 baud rate 
sysTime_init();
adc_Init(); // Initialize ADC
PWM_Init(); // Initialize PWM
DDRB |= (1<<PB1); // Set PB1 as output
DDRB |= (1<<PB0); // Set PB0 as output
DDRD &= ~(1<<PD7); // Set PD7 as input
PORTD |= (1<<PD7); // Enable pull-up on PD7
PORTC &= ~(1<<PC0); // Set PC0 as input (ADC0)
PORTC &= ~(1<<PC1); // Set PC1 as input (ADC1)

  while(1){
    potVal0 = ADC_read(0); // Read ADC value from channel 0
    potVal1 = ADC_read(1); // Read ADC value from channel 1
    int BLINK_DURATION =(625 * potVal0)/125; // Blink duration based on potVal0 (0-5000 ms)
    if(potVal0 <= 20) BLINK_DURATION = 0; // Minimum blink duration
    if(potVal0 >= 1000) BLINK_DURATION = 1000; // Maximum blink duration
    brightness = (255UL * potVal1)/1023; // Brightness based on potVal1 (0-255)
    if(potVal1 <= 20) brightness = 0; // Minimum brightness
    if(potVal1 >= 1000) brightness = 255; // Maximum brightness 
    uint32_t currentTime = sysTime();
    /*==========================System Time ==========================*/
    if(currentTime - lastCheckTime >= 1000){ // Toggle every 1000 ms
      printString(" Time: "); printInt(currentTime); printString(" ms\r\n");
      lastCheckTime = currentTime;  
    }
    /*========================== LED BLINKING ==========================*/
    if(currentTime - lastBlinkTime >= BLINK_DURATION){
      if(ledState){
        LED_Brightness(0); // Turn off LED

      }
      else{
        LED_Brightness(brightness); // Set LED brightness
      }
      ledState = !ledState;
      lastBlinkTime = currentTime;
    }
    /*========================== BUTTON PRESS ==========================*/
    if(currentTime - lastPressTime >= 5){
    if(!(PIND & (1<<PD7))){ // Check if button on PD7 is pressed
      PORTB |= (1<<PB0); // Turn onPB0 
      if(messageState == false){ 
      printString(" Hello World!\r\n"); 
      messageState = true;
      }
      lastPressTime = currentTime;
    }
    else{
      PORTB &= ~(1<<PB0); // Turn off PB0
      messageState = false;
    }
    }
    if(currentTime - lastPotTime >= 100){ // Every 500 ms
      printString("PotVal0: "); printInt(potVal0); printString("\r\n");
      lastPotTime = currentTime;
    }
  }
  

  return 0;
}


