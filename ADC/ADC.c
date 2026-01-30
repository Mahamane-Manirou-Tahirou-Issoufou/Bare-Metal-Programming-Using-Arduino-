#include<stdint.h>
#include<stdbool.h>
#include<avr/io.h>
#include<avr/interrupt.h>

int adc_Init(){
  // Initialisation  de ADEN à 1 et aussi les  ADPSi à 1 (Avec i = 0,1,2)
  // De même avec les ADPSi on  va choisir la valeur du  Prescaler
  // Ça va nous permettre de configurer l'horloge de l'ADC qui a une fréquence entre 50 KHZ à 200 KHZ
ADMUX |= (1<<REFS0); // configuration de ADMUX pour mettre REFS0 à 1 
ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ADC_read(uint8_t channel){
  // Security: S'assurer que le canal est entre 0 et 7
//channel &= 0x07; // Masquer les bits supérieurs pour ne garder que les 3 bits de poids faible
// Début de la conversion (Et aucours de la conversion ADSC reste à 1)
ADMUX = (ADMUX & 0b11110000) | (channel & 0b00001111); // Sélectionner le canal 
ADCSRA |= (1<<ADSC); 
  // Verifications si la conversion est terminée ( c'est-à-dire si ADSC est toujours à 1 ou à 0)
while( ADCSRA & (1<<ADSC));
  // Dès que ADSC devient égale à 0, la boucle prend fin et on retourne la valeur ADC qui est égale  ADC = (Vin *1024)/Vref.
return ADC ;
}
/*
// L'exemple d'utilisation de notre fonction 
int main(void){
adc_Init(); // Initialisation 
Serial.begin(9600); // Communication Série 
while(1){ // Boucle infini
uint16_t val0 = analogRead_LowLevel(0); // la broche A0
Serial.println("val0 :"); // Affichage 
Serial.print(val0);
_delay_ms(1000); // Délai de 1 seconde 
uint16_t val1 = analogRead_LowLevel(1); // la broche A0
println("val1"); // Affichage 
Serial.println(val1);
delay_ms(1000); // Délai de 1 seconde 
}
}
*/