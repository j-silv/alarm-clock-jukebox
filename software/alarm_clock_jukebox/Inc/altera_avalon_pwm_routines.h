/* 
The PWM modules have been taken from Altera. As per the copyright states, the following
notice has been included:
*/

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
#include "altera_avalon_pwm_regs.h"

#define ALTERA_AVALON_PWM_TYPE (volatile unsigned int*)

int altera_avalon_pwm_init(unsigned int address, unsigned int clock_divider, unsigned int duty_cycle);
int altera_avalon_pwm_enable(unsigned int address);
int altera_avalon_pwm_disable(unsigned int address);
int altera_avalon_pwm_change_duty_cycle(unsigned int address, unsigned int duty_cycle);

//Return Codes
#define ALTERA_AVALON_PWM_OK                                          0
#define ALTERA_AVALON_PWM_DUTY_CYCLE_GREATER_THAN_CLOCK_CYCLE_ERROR  -1
#define ALTERA_AVALON_PWM_ENABLED_CONFIRMATION_ERROR 	             -2
#define ALTERA_AVALON_PWM_DISABLED_CONFIRMATION_ERROR 	             -3

//Constants
#define ALTERA_AVALON_PWM_ENABLED  1
#define ALTERA_AVALON_PWM_DISABLED 0
