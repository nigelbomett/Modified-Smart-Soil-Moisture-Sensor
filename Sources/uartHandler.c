/*
* uartHandler.c
* created on: 10-May-2017
*	Author: Nigel Bomett
*/

#include "MKL25Z4.h"
#include "uartHandler.h"
#include "uartBuffer.h"
#include "data.h"

volatile uint8_t da=0;

void UART0_IRQHandler(){
	state error_code = buff_empty(&tx_buf);
	
	if((UART0_S1 & UART0_S1_TDRE_MASK) && error_code==buf_not_empty){
		//If buffer is not empty and TDRE flag is set then transmit the character
		UART0_D = read_data(&tx_buf);
	}
	else if(error_code==buf_empty){
		UART0_C2 &= ~UART0_C2_TIE_MASK;
	}
	error_code = buff_full(&rx_buf);
	
	if((UART0_S1 & UART0_S1_RDRF_MASK) && error_code==buf_not_full){
	 //If buffer is not full and RDRF flag is set the receive the character	from UARTD0
	  da=UART0_D;
	  add_data(&rx_buf,da);
	}
	else if(error_code==buf_empty)
	{
		//If rx buffer is full then disable the rx interrupt
		UART0_C2 &= ~UART0_C2_RIE_MASK;
	}
}
