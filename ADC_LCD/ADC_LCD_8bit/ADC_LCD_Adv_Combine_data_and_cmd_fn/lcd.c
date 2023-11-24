//including header file of lcd "lcd.h and delay "delay.h"
#include<reg51.h>
#include"lcd.h"
#include"delay.h"

// init() function defination
void init()												
{
	
	delay(5);                       // delay
	LCD_cmd_data(0, 0x38);								  // 8 bit data (2 line)
	LCD_cmd_data(0, 0x0C);									// display on and curser off
	LCD_cmd_data(0, 0x06);									// entry mode
}

// LCD_cmd() function defination with one argument "cmd"
void LCD_cmd_data(unsigned char status, unsigned char cmd_or_data)
{
	LCD_port = cmd_or_data;									//assigning the value of cmd to  LCD_port
	RS = status;													//the register select is in active low mode for command
	RW = 0;													//open
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//delay for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//delay for EN
}

// LCD_data() function defination with one argument "dat"


// LCD_string() function defination with one argument "*string"
void LCD_string(unsigned char *string)
{
	while(*string)
	{
		LCD_cmd_data(1, *string++);
	}
}