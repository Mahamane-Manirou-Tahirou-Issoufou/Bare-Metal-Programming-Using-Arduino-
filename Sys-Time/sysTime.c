#include<stdint.h>
#include<avr/io.h>
#include<avr/interrupt.h>
volatile static uint32_t ms_counter=0;

void sysTime_init(void){
//1.waveform setting
//2. Prescaler
//3.Calling interrupts



// Initialisation du compteur de millisecondes
// Configuration du mode de génération d'onde
TCCR0A |= (1<<WGM01); // Mode CTC (Clear Timer on Compare Match)
TCCR0A &= ~(1<<WGM00);
TCCR0B &= ~(1<<WGM02);

// Configuration du prescaler à 64
TCCR0B |= (1<<CS01); // Division par 64
TCCR0B |= (1<<CS00);
TCCR0B &= ~(1<<CS02);
// Enable Timer Compare Interrupt
OCR0A = 249; // Set Compare Value for 1ms at 16MHz with 64 prescaler
TIMSK0 |= (1<<OCIE0A);
// Enable Global Interrupts
sei();       

}

ISR(TIMER0_COMPA_vect){
ms_counter++;
}
uint32_t sysTime(void){
    uint32_t time;
    cli();// Disable interrupts
    time = ms_counter;
    sei();// Enable interrupts
    return time;
}