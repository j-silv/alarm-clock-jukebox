#include "pwm.h"

uint8_t volume = 5;

uint8_t getVolume(void) {
  return volume;
}
uint8_t upVolume(void) {
  volume++;
  return volume;
}
uint8_t downVolume(void) {
  volume--;
  return volume;
}

void stopPWM(void) {
  int return_code = ALTERA_AVALON_PWM_OK;
  //Disable PWM and Check Return Code
  return_code = altera_avalon_pwm_disable(PWM_BASE); 
  check_return_code(PWM_BASE, return_code);
}



void default500HzSquareWave(void) {

 unsigned int clock_divide = 100000;
 unsigned int duty_cycle =    50000;
 int return_code = ALTERA_AVALON_PWM_OK;
 
 //Initialize PWM and Check Return Code
 return_code = altera_avalon_pwm_init(PWM_BASE, clock_divide, duty_cycle);  
 check_return_code(PWM_BASE, return_code);
 
 //Enable PWM and Check Return Code
 return_code = altera_avalon_pwm_enable(PWM_BASE); 
 check_return_code(PWM_BASE, return_code);
}

void writePWM(int frequency) {

  if (frequency == 0) {
    // this happens if the note is supposed to be a pause
    stopPWM();
  }
  else {
    // conversion of input frequency to PWM clock cycle divide value
    unsigned int clock_divide = NIOS_CLOCK_FREQ/frequency;

    // 5% duty cycle by default
    unsigned int duty_cycle =    clock_divide*0.05;

    int return_code = ALTERA_AVALON_PWM_OK;
    
    //Initialize PWM and Check Return Code
    return_code = altera_avalon_pwm_init(PWM_BASE, clock_divide, duty_cycle);  
    check_return_code(PWM_BASE, return_code);
    
    //Enable PWM and Check Return Code
    return_code = altera_avalon_pwm_enable(PWM_BASE); 
    check_return_code(PWM_BASE, return_code);
  }

}

void testPWM(void) {
 
 unsigned int duty_cycle;
 int return_code = ALTERA_AVALON_PWM_OK;
 
 printf("Period = %u\n", IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(PWM_BASE) );
 printf("Duty cycle = %u\n", IORD_ALTERA_AVALON_PWM_DUTY_CYCLE(PWM_BASE) );
 
 //Initialize PWM and Check Return Code
 return_code = altera_avalon_pwm_init(PWM_BASE, 500000, 1);  
 check_return_code(PWM_BASE, return_code);
 
 //Enable PWM and Check Return Code
 return_code = altera_avalon_pwm_enable(PWM_BASE); 
 check_return_code(PWM_BASE, return_code);

//init duty_cycle with the value written to duty_cycle register during initialization
 duty_cycle = IORD_ALTERA_AVALON_PWM_DUTY_CYCLE(PWM_BASE);
 
 
 while(1)
   {
     while(duty_cycle++ < IORD_ALTERA_AVALON_PWM_CLOCK_DIVIDER(PWM_BASE))
     {
      	return_code = altera_avalon_pwm_change_duty_cycle(PWM_BASE, duty_cycle);
      	check_return_code(PWM_BASE, return_code);
     }          
     while(--duty_cycle > 1)
      	altera_avalon_pwm_change_duty_cycle(PWM_BASE, duty_cycle);
        check_return_code(PWM_BASE, return_code);
   }
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