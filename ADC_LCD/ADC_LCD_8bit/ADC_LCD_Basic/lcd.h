//including the required lib
#include<reg51.h>
#include"delay.h"

//micro define for lcd port to P0
#define LCD_port P0                           //LCD port is P0
//sfr LCD_port = 0x80;

//sbit declreation
sbit RS = P1^0;																//Register Select 
sbit RW = P1^1;																//Read / Write 
sbit EN = P1^2;																//ENable select 


//forword decleration 
void init();																	// init() function to activate the LCD
void LCD_cmd(unsigned char);									// LCD_cmd() function to pass cmd to LCD_port
void LCD_data(unsigned char);									// LCD_data() function to pass data to LCD_port
void LCD_string(unsigned char *);							// LCD_string() function to pass *string to display data through LCD_data() function