//including header libs
#include<reg51.h>
#include"delay.h"

//micro decleration
#define ADC_port P2;
#define segmenet_port P3

//special function register
//sfr ADC_port = 0xA0;

//sbit decleration
sbit Rd   = P1^3;													//Read pin
sbit Wr   = P1^4;													//write pin
sbit INTR = P1^5;													//INTR pin
sbit digit1 = P1^2;												//7 segment pin (hunders)
sbit digit2 = P1^1;												//7 segment pin (tens)
sbit digit3 = P1^0;												//7 segment pin (units)


void segment_display(unsigned char);

void main()																//main function (1time exe.able)
{
	
	unsigned char ADC_value;								//ADC_value variable req. for ADC_port

	while(1)																//forever loop (or we can use for(;;))
	{
		//reading adc values
		Rd = 1;																//Read pin is high
		Wr = 0;																//Write pin is low
		delay(1);															//calling delay function which is used here to create pluse
		Wr = 1;																//Write pin is high
		while(INTR == 1);											//if INTR pin is 1 then conversion is in process and if INTR is 0 then conversion is complate
		Rd = 0;																//Read pin is low
		
		ADC_value = ADC_port;									//assigning the value of ADC_port to ADC_value variable (who's range is from 0 to 255
			
		segment_display(ADC_value);
			
	}
}

void segment_display(unsigned char ADC_value)
{
		unsigned int segmenet_array[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; //hex values from 0 to 9
		unsigned int i;	
			
		for(i = 0; i < 2; i++)
		{
			segmenet_port = segmenet_array[(ADC_value / 100)];
			digit1 = 1;													//hundereds place segment is ON 
			digit2 = 0;													//tens  place segment is OFF
			digit3 = 0;													//unit  place segment is OFF
			
			delay(1);														//calling delay funcation with one
			
			//for tens place digit
			segmenet_port = segmenet_array[((ADC_value / 10) % 10)];
			digit1 = 0;													//hundereds place segment is OFF
			digit2 = 1;									  			//tens  place segment is ON
			digit3 = 0;													//unit  place segment is OFF
			
			delay(1);														//calling delay funcation with one
			
			//for units place digit
			segmenet_port = segmenet_array[(ADC_value % 10)];
			digit1 = 0;													//hundereds place segment is OFF 
			digit2 = 0;													//tens  place segment is OFF
			digit3 = 1;													//unit  place segment is ON
			
			delay(1);														//calling delay funcation with one
		}
}