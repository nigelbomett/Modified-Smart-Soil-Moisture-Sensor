/*
* uartBuffer.h
* Created on: 10-May-2017
*	Author: Nigel Bomett
*
*/

#ifndef INCLUDES_UARTBUF_H_
#define INCLUDES_UARTBUF_H_

#define MAX_LEN 1000

//Buffer structure containing head,tail and base address of the buffer
typedef struct{
	uint8_t *data;
	
	uint8_t *buff;
	uint8_t *head;
	uint8_t *tail;
	uint8_t new_len;
}uartBuf_t;

typedef enum{buf_full,buf_empty,buf_not_full,buf_not_empty,add_success,remove_success,add_success_with_wrap_around} state;
state buff_full(uartBuf_t *ub);
state buff_empty(uartBuf_t *ub);
state add_data(uartBuf_t *ub,uint8_t item);
uint8_t read_data(uartBuf_t *ub);
void destroy(uartBuf_t *ub);

#endif /*INCLUDES_UARTBUF_H_*/
