#ifndef SYSTICK_H_
#define SYSTICK_H_

void  Init_Systick();
#define SYSTICK_FREQUENCY 1000
void delay_ms(unsigned int TicksIn_ms);
extern volatile unsigned int Ticker[4];

#endif /* BUTTON_H_ */

