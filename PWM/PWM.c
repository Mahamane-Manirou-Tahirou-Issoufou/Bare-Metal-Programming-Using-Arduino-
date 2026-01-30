#include<stdint.h>
#include<stdbool.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<stdlib.h>

void PWM_Init(){
    // NON_inverting mode

    TCCR1A |= (1<<COM1A1);

    // WGM-Fast PWM

    TCCR1B |= (1<<WGM12);
    TCCR1A |= (1<<WGM10);

    // Prescalar
    TCCR1B |= (1<<CS11); // prescalar = 8 
}
void LED_Brightness(uint8_t brightness){
    if(brightness ==0){
        TCCR1A &= ~(1<<COM1A1);
        PORTB &= ~(1<<PB1); // Turn off LEd
    }
    else{
        TCCR1A |= (1<<COM1A1);
        //brightness value between 0-255
        OCR1A = brightness; // Set the duty cycle
    }
    
}