#ifndef __LED_H
#define __LED_H

// altera bsp
#include "system.h"
#include  "altera_avalon_pio_regs.h"

void alarmLEDoff(void);
void alarmLEDon(void);
void alarmLEDtoggle(void);

#define LED_OFF 0
#define LED_ON 1

#endif
