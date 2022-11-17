#define D0 eS_PORTD0
#define D1 eS_PORTD1
#define D2 eS_PORTD2
#define D3 eS_PORTD3
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTB0 
#define EN eS_PORTB1
#define F_CPU 16000000UL


#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
#include <string.h>
#include <stdio.h>


void analogue(void) {
	ADMUX |= (1 << REFS0) | (1 << MUX0); //reference voltage on AVCC, and use ADC1
	ADCSRA |= (1 << ADPS1) | (1 << ADPS0); //ADC clock prescaler / 8
	ADCSRA |= (1 << ADEN); //enables the ADC
}

int main(void)
{
DDRD = 0xFF;
DDRB = 0xFF;
//char* string = "Welcome to B31DD Embedded Systems!";

char* pot_val[20];
char* wet="Wet";
char* dry="Dry";

int i;
uint16_t potentiometerValue;

DDRB |= (1 << PORTB2); //Data Direction Register B: writing a 1 to the bit enables output
	
//Methods to initalise the ADC and LCD display
analogue();
Lcd4_Init();


while(1)
{
ADCSRA |= (1 << ADSC); //start ADC conversion
		while((ADCSRA & (1 << ADSC))) //wait until ADSC bit is clear, i.e., ADC conversion is done
		{}
		//read ADC value in
		uint8_t theLowADC = ADCL;
		potentiometerValue = ADCH << 8 | theLowADC;
		
//sprintf(pot_val, "%u", potentiometerValue); //Casting read potentiometer value to string

if (potentiometerValue < 440){
	Lcd4_Write_String(wet); //writing read potentiometer value to LCD
	_delay_ms(500);
	
	OCR0A = 255; //motor off
	
	Lcd4_Clear();
}
else {
	Lcd4_Write_String(dry);
	_delay_ms(500);
	
	OCR0A = 191; //motor on
	
	Lcd4_Clear();
	
}
//Lcd4_Set_Cursor(1,1);
//Lcd4_Write_String(pot_val);
//for(i=0;i<strlen(pot_val)-1;i++)
//{
//_delay_ms(500);
//Lcd4_Shift_Left();
//}
//for(i=0;i<strlen(pot_val)-1;i++)
//{
//_delay_ms(500);
//Lcd4_Shift_Right();
//}
//Lcd4_Clear();
// Lcd8_Write_Char('e');
// Lcd8_Write_Char('S');
//_delay_ms(100);
}
}