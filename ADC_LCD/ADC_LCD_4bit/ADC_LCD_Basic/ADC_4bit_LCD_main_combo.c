//including required libs
#include<reg51.h>
#include"lcd.h"
#include"delay.h"

//micro decleration
#define ADC_port P2;

//special function register
//sfr ADC_port = 0xA0;

//sbit decleration
sbit Rd   = P1^3;													//Read pin
sbit Wr   = P1^4;													//write pin
sbit INTR = P1^5;													//INTR pin

void main()																//main function (1time exe.able)
{
	unsigned char ADC_value;								//ADC_value variable req. for ADC_port
	init();																	//calling init() function to activate the LCD
	LCD_cmd(0x80);													//calling LCD_cmd function row-1, col-0
	LCD_string("ADC = ");										//calling LCD_string function 
	LCD_cmd(0x89);													//calling LCD_cmd function row-1, col-9
	LCD_data(0xDF);													//calling LCD_data function with the hex value of degree symbol
	LCD_data('C');													//calling LCD_data function with 'C' argument
	
	LCD_cmd(0xC0);
	LCD_string("ADITYA A NIJAVE");
	
	while(1)																//forever loop (or we can use for(;;))
	{
		Rd = 1;																//Read pin is high
		Wr = 0;																//Write pin is low
		delay(1);															//calling delay function which is used here to create pluse
		Wr = 1;																//Write pin is high
		while(INTR == 1);											//if INTR pin is 1 then conversion is in process and if INTR is 0 then conversion is complate
		Rd = 0;																//Read pin is low
		
		ADC_value = ADC_port;									//assigning the value of ADC_port to ADC_value variable (who's range is from 0 to 255)
		
		LCD_cmd(0x86);												//calling LCD_cmd function row-1, col-6
		LCD_data((ADC_value / 100) + 48);			//calling LCD_data function to pass hundereds place integer 
		LCD_data(((ADC_value/10)%10)+48);			//calling LCD_data function to pass tens place integer
		LCD_data((ADC_value % 10) + 48);			//calling LCD_data function to pass units place integer
	}
}


