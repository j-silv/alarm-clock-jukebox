/****************************************************************************************/
/* Copyright © 2004 Altera Corporation, San Jose, California, USA. All rights reserved. */
/* Permission is hereby granted, free of charge, to any person obtaining a copy of this */
/* software and associated documentation files (the "Software"), to deal in the Software*/
/* without restriction, including without limitation the rights to use, copy, modify,   */
/* merge, publish, distribute, sublicense, and/or sell copies of the Software, and to   */
/* permit persons to whom the Software is furnished to do so, subject to the following  */
/* conditions:  The above copyright notice and this permission notice shall be included */
/* in all copies or substantial portions of the Software.                               */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,  */
/* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A        */
/* PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT   */
/* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF */
/* CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE */
/* OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                        */
/* This agreement shall be governed in all respects by the laws of the State of         */
/* California and by the laws of the United States of America.  Altera does not         */
/* recommend, suggest or require that this reference design file be used in conjunction */
/* or combination with any other product.                                               */
/****************************************************************************************/

//Includes
#include "altera_avalon_pwm_regs.h"
#include "altera_avalon_pwm_routines.h"
#include "system.h"
#include <stdio.h>
//Function Protypes
void print_error(unsigned int address, int return_code);
void check_return_code(unsigned int address, int return_code);

int main(void)

{
 
 unsigned int duty_cycle;
 int return_code = ALTERA_AVALON_PWM_OK;
 
 printf("Hello from the PWM test program.\n");
 printf("The starting values in the PWM registers are:\n");
 printf("Period = %u\n", IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(Z_PWM_0_BASE) );
 printf("Duty cycle = %u\n", IORD_ALTERA_AVALON_PWM_DUTY_CYCLE(Z_PWM_0_BASE) );

 printf("\nNotice the pulsing LED on the development board.\n");
 
 //Initialize PWM and Check Return Code
 return_code = altera_avalon_pwm_init(Z_PWM_0_BASE, 500000, 1);  
 check_return_code(Z_PWM_0_BASE, return_code);
 
 //Enable PWM and Check Return Code
 return_code = altera_avalon_pwm_enable(Z_PWM_0_BASE); 
 check_return_code(Z_PWM_0_BASE, return_code);

//init duty_cycle with the value written to duty_cycle register during initialization
 duty_cycle = IORD_ALTERA_AVALON_PWM_DUTY_CYCLE(Z_PWM_0_BASE);
 
 
 while(1)
   {
     while(duty_cycle++ < IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(Z_PWM_0_BASE))
     {
      	return_code = altera_avalon_pwm_change_duty_cycle(Z_PWM_0_BASE, duty_cycle);
      	check_return_code(Z_PWM_0_BASE, return_code);
     }          
     while(--duty_cycle > 1)
      	altera_avalon_pwm_change_duty_cycle(Z_PWM_0_BASE, duty_cycle);
        check_return_code(Z_PWM_0_BASE, return_code);
   }
return 0;
}

void check_return_code(unsigned int address, int return_code)
{
	if(return_code != ALTERA_AVALON_PWM_OK)
      		print_error(address, return_code);	
}

void print_error(unsigned int address, int return_code)
{
	printf("Program Terminated Due to an error with Avalon PWM located at 0x%x:\n", address);
	switch(return_code)
	{
	case ALTERA_AVALON_PWM_DUTY_CYCLE_GREATER_THAN_CLOCK_CYCLE_ERROR:
		printf("The value in the clock cycle register must be greater than the value in the duty cycle register\n");
		printf("Value in the Clock Divide Register: 0x%x\n", IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(address)); 
		printf("Value in the Duty Cycle Register: 0x%x\n", IORD_ALTERA_AVALON_PWM_DUTY_CYCLE(address));
		break;
        case ALTERA_AVALON_PWM_ENABLED_CONFIRMATION_ERROR:
                printf("Unable to confirm that the PWM is enabled\n");
		printf("Value in the Enable Register: 0x%x\n", IORD_ALTERA_AVALON_PWM_ENABLE(address)); 
        	break;
        case ALTERA_AVALON_PWM_DISABLED_CONFIRMATION_ERROR:
        	printf("Unable to confirm that the PWM is disabled\n");
		printf("Value in the Enable Register: 0x%x\n", IORD_ALTERA_AVALON_PWM_ENABLE(address)); 
        	break;
        default:
        	break; 		     
	}

while(1);
}
// end of file
