//including required libs
#include"adc.h"
#include"lcd.h"
#include"delay.h"

void pre_data()
{
	init();																	//calling init() function to activate the LCD
	LCD_cmd(0x80);													//calling LCD_cmd function row-1, col-0
	LCD_string("ADC = ");										//calling LCD_string function 
	LCD_cmd(0x89);													//calling LCD_cmd function row-1, col-9
	LCD_data(0xDF);													//calling LCD_data function with the hex value of degree symbol
	LCD_data('C');													//calling LCD_data function with 'C' argument
	
	LCD_cmd(0xC2);													//calling LCD_cmd function row-2, col-2
	LCD_string("ADITYA NIJAVE");						//calling LCD_string() function and passing string through it to display on LCD
}



unsigned char ADC_read()									//ADC_read() function defination
{
		unsigned char ADC_value;							//ADC_value variable req. for ADC_port
	
		Rd = 1;																//Read pin is high
		Wr = 0;																//Write pin is low
		delay(1);															//calling delay function which is used here to create pluse
		Wr = 1;																//Write pin is high
		while(INTR == 1);											//if INTR pin is 1 then conversion is in process and if INTR is 0 then conversion is complate
		Rd = 0;															  //Read pin is low
	
		ADC_value = ADC_port;									//assigning the value of ADC_port to ADC_value variable (who's range is from 0 to 255)
		return ADC_value;
}

void ADC_display(unsigned int ADC_value)	////ADC_display() function defination with one paramter
{
		LCD_cmd(0x86);												//calling LCD_cmd function row-1, col-6
		LCD_data((ADC_value / 100) + 48);			//calling LCD_data function to pass hundereds place integer 
		LCD_data(((ADC_value%10)/10)+48);			//calling LCD_data function to pass tens place integer
		LCD_data((ADC_value & 10) + 48);			//calling LCD_data function to pass units place integer
}