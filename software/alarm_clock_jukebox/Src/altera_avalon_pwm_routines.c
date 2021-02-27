/****************************************************************************************/
/* Copyright � 2004 Altera Corporation, San Jose, California, USA. All rights reserved. */
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

#include "altera_avalon_pwm_routines.h"


int altera_avalon_pwm_init(unsigned int address, unsigned int clock_divider, unsigned int duty_cycle)
{
	if(duty_cycle > clock_divider)  //duty cycle reg must be less than or equal to clock divider
	{
		return ALTERA_AVALON_PWM_DUTY_CYCLE_GREATER_THAN_CLOCK_CYCLE_ERROR;
	}
	else
	{
		IOWR_ALTERA_AVALON_PWM_CLOCK_DIVIDER(address, clock_divider - 1);
		IOWR_ALTERA_AVALON_PWM_DUTY_CYCLE(address, duty_cycle);
	}
	 return ALTERA_AVALON_PWM_OK;
}

int altera_avalon_pwm_enable(unsigned int address)
{
  IOWR_ALTERA_AVALON_PWM_ENABLE(address, ALTERA_AVALON_PWM_ENABLE_MSK);
  
  if(IORD_ALTERA_AVALON_PWM_ENABLE(address) != ALTERA_AVALON_PWM_ENABLED) //Confirm PWM is enabled
  {
  	return ALTERA_AVALON_PWM_ENABLED_CONFIRMATION_ERROR;
  }
  return ALTERA_AVALON_PWM_OK;
}

int altera_avalon_pwm_disable(unsigned int address)
{
  IOWR_ALTERA_AVALON_PWM_ENABLE(address, ~ALTERA_AVALON_PWM_ENABLE_MSK);

  if(IORD_ALTERA_AVALON_PWM_ENABLE(address) != ALTERA_AVALON_PWM_DISABLED)  //Confirm PWM is disabled 
  {
  	return ALTERA_AVALON_PWM_DISABLED_CONFIRMATION_ERROR;
  }
  return ALTERA_AVALON_PWM_OK;
}


int altera_avalon_pwm_change_duty_cycle(unsigned int address, unsigned int duty_cycle)
{
	if(duty_cycle > IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(address))  //duty cycle reg must be less than or equal to clock divider
	{
		return ALTERA_AVALON_PWM_DUTY_CYCLE_GREATER_THAN_CLOCK_CYCLE_ERROR;
	}
	else
	{
    IOWR_ALTERA_AVALON_PWM_DUTY_CYCLE(address, duty_cycle);
	}
  return ALTERA_AVALON_PWM_OK;
}

