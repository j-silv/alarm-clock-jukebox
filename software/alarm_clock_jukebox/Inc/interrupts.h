#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

void update_second_isr(void* isr_context);
int registerTimerInterrupt(void);
void enableTimerInterrupt(void);


#endif