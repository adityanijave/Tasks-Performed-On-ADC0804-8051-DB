//including header files
#include<reg51.h>
#include"delay.h"

//micro define
#define ADC_port P2																																			//adc port = P2 = 0x0A
#define segmenet_port P3																																//segment port = P3 = 0xB0

//sbit decleration
//for adc
sbit Rd = P1^3;																																					//read pin
sbit Wr = P1^4;																																					//write/read pin
sbit INTR = P1^5;																																				//intr pin
//for 7-segment
sbit digit1 = P1^0;																																			//for hunderds place segment
sbit digit2 = P1^1;																																			//for tens place segment
sbit digit3 = P1^2;																																			//for units place segment


//forward decleration of user defined funcation
void ADC_read();																																				//proto-type of adc read funcation which reads the adc values
void Segment_Display(unsigned char);																											//proto-type of segment display funcation used to display adc value

//main funcaiton
void main()
{
	//decleration of local variables
	unsigned char ADC_value;
	
	//forever loop
	while(1)																																							//or we can use for(;;)
	{
		ADC_read();																																					//calling funcation to read adc values
		ADC_value = ADC_port;																																//data is resived at variable ADC_value
		Segment_Display(ADC_value);																													//calling funcation to show adc values on segments
	}
}

//funcation defination of user defined funcations
void ADC_read()																																					//funcation used to read adc values
{
		Rd = 1;																																							//read pin is high (pluse start)
		Wr = 0;																																							//write pin is low (pluse start)
		
		delay(1);																																						//calling delay funcation to generate pluse
		
		Wr = 1;																																							//write pin is high (pluse end)
		while(INTR == 1);																																		//this loop will be terminate when INTR becomes 0
		
		Rd = 0;																																							//read pin is low (pluse end)
}

void Segment_Display(unsigned char ADC_value)																						//funcation used to display adc value on segments
{
	//array contains hex values from 0 to 9 digits
	unsigned int segmenet_array[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; 
	
	//decleration of variable inside the funcation
	unsigned int i;
	
	//for loop to reduce the filkering effect
	for(i = 0; i < 50; i++)
	{
		//for hundered place digit
		segmenet_port = segmenet_array[(ADC_value / 100)];
		digit1 = 1;																																					//hundered place digit segment is ON
		digit2 = 0;																																					//tens place digit segment is OFF
		digit3 = 0;																																					//units place digit segment is OFF
		
		delay(1);																																						//calling delay funcation with one
		
		segmenet_port = segmenet_array[((ADC_value / 10) % 10)];
		digit1 = 0;																																					//hundered place digit segment is OFF
		digit2 = 1;																																					//hundered place digit segment is ON
		digit3 = 0;																																					//hundered place digit segment is OFF
		
		delay(1);																																						//calling delay funcation with one
		
		
		segmenet_port = segmenet_array[(ADC_value % 10)];
		digit1 = 0;																																					//hundered place digit segment is OFF
		digit2 = 0;																																					//hundered place digit segment is OFF
		digit3 = 1;																																					//hundered place digit segment is ON
		
		delay(1);																																						//calling delay funcation with one
	}
}