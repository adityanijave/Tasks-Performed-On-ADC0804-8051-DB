//including required libs
#include<reg51.h>

//micro decleration
#define ADC_port P2;											// port 2 is assign as ADC_port

//special function register								//another method of assigning
//sfr ADC_port = 0xA0;

//sbit decleration
sbit Rd   = P1^3;													//Read pin
sbit Wr   = P1^4;													//write pin
sbit INTR = P1^5;													//INTR pin

//forword decleration
void pre_data();													//pre_data function forword decleration
void ADC_display(unsigned int);						//ADC_display function forword decleration with one parameter
unsigned char ADC_read();									//ADC_read function forword decleration