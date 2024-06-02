#ifndef TIMER_H_
#define TIMER_H_

#include <avr/io.h>

void Timer1_Init(void);

extern volatile uint8_t Flag_TemHum;

#endif /* TIMER_H_ */
