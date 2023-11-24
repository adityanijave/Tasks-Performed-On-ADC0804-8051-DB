//including required libs
#include<reg51.h>
#include"lcd.h"
#include"delay.h"

//micro decleration
#define ADC_port P0;

//sbit decleration
sbit Rd   = P1^3;													//Read pin
sbit Wr   = P1^4;													//write pin
sbit INTR = P1^5;													//INTR pin

sbit IN1 = P1^6;
sbit IN2 = P1^7;
sbit EN1 = P3^7;

sbit low = P3^6;
sbit mid = P3^5;
sbit high = P3^4;
sbit stop = P3^3;

sbit change_motion_sw = P3^2;
sbit emergency_sw = P2^0;
sbit forword_motion = P3^1;
sbit reverse_motion = P3^0;

void timer();
void timer_20ms();
void timer_40ms();
void timer_60ms();

void stop_led();
void low_led();
void mid_led();
void high_led();

void change_motion();

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
	
	TMOD = 0x01;
	EN1 = 1;
	IN1 = 1;
	IN2 = 0;
	forword_motion = 1;
	reverse_motion = 0;
	
	
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
		
		
		if (0 <= ADC_value && ADC_value <= 5)
		{
			stop_led();
			EN1 = 0;
		}
		else if (5 < ADC_value && ADC_value <= 85)
		{
			low_led();
			EN1 = 1;
			timer_20ms();
			timer();
			
			EN1 = 0;
		}
		else if (85 < ADC_value && ADC_value <= 180)
		{
			mid_led();
		
			EN1 = 1;
			timer_40ms();
			timer();
			
			EN1 = 0;
		}
		else if (181 < ADC_value && ADC_value <= 250)
		{
			high_led();
			
			EN1 = 1;
			timer_60ms();
			timer();
		}
		else if (251 <= ADC_value && ADC_value <= 255)
		{
			
			stop_led();
			EN1 = 0;
		}
		
		if (change_motion_sw == 0)
		{
			change_motion();
		}
		else if (change_motion_sw == 0)
		{
			stop_led();
			EN1 = 0;
		}
	}
}


void timer_20ms()
{
	TH0 = 0xB7;
	TL0 = 0xFF;
}

void timer_40ms()
{
	TH0 = 0x6F;
	TL0 = 0xFE;
}

void timer_60ms()
{
	TH0 = 0x27;
	TL0 = 0xFC;
}

void timer()
{
	TR0 = 1;
	while(TF0 == 0);
	TR0 = 0;
	TF0 = 0;
}


void stop_led()
{
	low = 0;
	mid = 0;
	high = 0;
	stop = 1;
}

void high_led()
{
	low = 0;
	mid = 0;
	high = 1;
	stop = 0;
}

void mid_led()
{
	low = 0;
	mid = 1;
	high = 0;
	stop = 0;
}

void low_led()
{
	low = 1;
	mid = 0;
	high = 0;
	stop = 0;
}

void change_motion()
{
	IN1 = ~IN1 ; 
	IN2 = ~IN2;
	
	forword_motion = ~forword_motion;
	reverse_motion = ~reverse_motion;
}