//including required libs
#include"adc.h"

void main()																//main function (1-time exe.able)
{
	pre_data();															//calling pre_data function
	while(1)																//forever loop (or we can use for(;;))
	{						
		ADC_display(ADC_read());							//calling ADC_display function having ADC_read function as parameter
	}
}