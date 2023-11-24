//including header file of lcd "lcd.h and delay "delay.h"
#include<reg51.h>
#include"lcd.h"
#include"delay.h"

// init() function defination
void init()												
{
	
	delay(5);                       // delay
	LCD_cmd(0x38);								  // 8 bit data (2 line)
	LCD_cmd(0x0C);									// display on and curser off
	LCD_cmd(0x06);									// entry mode
}

// LCD_cmd() function defination with one argument "cmd"
void LCD_cmd(unsigned char cmd)
{
	LCD_port = cmd;									//assigning the value of cmd to  LCD_port
	RS = 0;													//the register select is in active low mode for command
	RW = 0;													//open
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//delay for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//delay for EN
}

// LCD_data() function defination with one argument "dat"
void LCD_data(unsigned char dat)
{
	
	LCD_port = dat;									//assigning the value of dat to  LCD_port
	RS = 1;													//the register select is in active high mode for data
	RW = 0;													//open
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//delay for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//delay for EN
}

// LCD_string() function defination with one argument "*string"
void LCD_string(unsigned char *string)
{
	while(*string)
	{
		LCD_data(*string++);
	}
}