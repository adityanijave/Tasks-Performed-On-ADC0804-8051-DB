//including header file of lcd 4 bit
#include"lcd.h"

// init() function defination
void init()												
{
	
	delay(5);                       // calling delay function
	LCD_cmd(0x28);								  // calling lcd command function for 4 bit data (2 line)
	LCD_cmd(0x0C);									// calling lcd command function for display on and curser off
	LCD_cmd(0x06);									// calling lcd command function for entry mode
}

// LCD_cmd() function defination with one argument "cmd"
void LCD_cmd(unsigned char cmd)
{
	
	RS = 0;													//the register select is in active low mode for command
	RW = 0;													//open (or GND)
	
	LCD_port = (cmd & 0xF0);				//assigning the value of cmd (anding with 0xF0) to  LCD_port
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//calling delay function for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//calling delay function delay for EN
	
	LCD_port = ((cmd << 4) & 0xF0);	//assigning the value of cmd (left shift by 4 and anding with 0xF0) to  LCD_port
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//calling delay function for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//calling delay function for EN
}

// LCD_data() function defination with one argument "dat"
void LCD_data(unsigned char dat)
{
	RS = 1;													//the register select is in active high mode for data
	RW = 0;													//open (or GND)
	
	LCD_port = (dat & 0xF0);			  //assigning the value of dat (anding with 0xF0) to  LCD_port
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//calling delay function for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//calling delay function for EN
	
	LCD_port = ((dat << 4)& 0xF0);	//assigning the value of dat (left shift by 4 and anding with 0xF0) to  LCD_port
	EN = 1;													//creating pluse for EN (high)
	delay(5);												//calling delay function for EN
	EN = 0;													//creating pluse for EN (low)
	delay(5);												//calling delay function for EN
}

// LCD_string() function defination with one pointer argument "*string"
void LCD_string(unsigned char *string)
{
	while(*string)									//while loop will terminated when it get a null value (i.e., '\0' that the end of string)
	{
		LCD_data(*string++);					//passing the value present at that location through LCD_data() function with increment by 1
	}
}