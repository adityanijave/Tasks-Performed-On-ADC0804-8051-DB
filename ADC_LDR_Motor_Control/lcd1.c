//including header file of lcd "lcd.h and delay "delay.h"
#include<reg51.h>
#include"lcd.h"
#include"delay.h"


// init() function defination
void init()												
{
	
	delay(5);                       // delay
	LCD_cmd(0x28);								  // 4 bit data (2 line)
	LCD_cmd(0x0C);									// display on and curser off
	LCD_cmd(0x06);									// entry mode
}

// LCD_cmd() function defination with one argument "cmd"
void LCD_cmd(unsigned char cmd)
{
	
	RS = 0;													//the register select is in active low mode for command
	RW = 0;													//open
	
	LCD_port = (cmd & 0xF0);				//assigning the value of cmd to  LCD_port
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//delay for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//delay for EN
	
	LCD_port = ((cmd << 4) & 0xF0);	//assigning the value of cmd to  LCD_port   (left shift by 4)
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//delay for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//delay for EN
}

// LCD_data() function defination with one argument "dat"
void LCD_data(unsigned char dat)
{
	RS = 1;													//the register select is in active high mode for data
	RW = 0;													//open
	
	LCD_port = (dat & 0xF0);			  //assigning the value of dat to  LCD_port
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//delay for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//delay for EN
	
	LCD_port = ((dat << 4)& 0xF0);		//assigning the value of dat to  LCD_port	   (left shift by 4)
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