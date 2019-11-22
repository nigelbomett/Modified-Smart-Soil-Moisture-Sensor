/*
*uartBuffer.c
*Created on: 10-May-2017
*	Author: Nigel Bomett
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "uartBuffer.h"

//Allocate memory to buffer dynamically
uint8_t* initialize(uartBuf_t *ub)
{
	ub->data = (uint8_t *)malloc(MAX_LEN);
	ub=malloc(sizeof(uartBuf_t));
    return ub->buff;
}
//Free memory block allocated to the buffer
void destroy(uartBuf_t *ub){
	free(ub);
}
state buff_full(uartBuf_t *ub){
/*
 If the head is at the end of the buffer and the tail is at the start then the buffer is full
 or if the head is one position behind the tail then also buffer is full
*/
	if(ub->new_len == MAX_LEN)
	{
		return buf_full;
	}
	else{
		return buf_not_full;
	}
}
state buff_empty(uartBuf_t *ub){
	//If head and tail of the buffer at the same position then that means the buffer is empty.
	if(ub->new_len==0){
		return buf_empty;
	}
	else{
		return buf_not_empty;
	}

}
state add_data(uartBuf_t *ub,uint8_t item){
	state error_code;
	error_code=buff_full(ub);
	
	//Check if buffer is full or not before adding item
	if(error_code==buf_not_full){
		if(ub->head==(ub->buff)+(MAX_LEN)-1){
			/*
			If head is at the last position of the buffer then add the item there and then put the head at the base address of the buffer
			*/
			ub->head=ub->buff;
			*(ub->head)=item;
			(ub->new_len)++;
			return add_success;
		}
		else{
			ub->head++;
			*(ub->head)=item;
			(ub->new_len)++;
			return add_success;
		}
	}
	else if (error_code==buf_full){
		//If buffer is full do not add item and return error
		return buf_full;
	}
}
uint8_t read_data(uartBuf_t *ub){
	state error_code;
	uint8_t rd;
	error_code=buff_empty(ub); //check for buffer empty before removing item
	if(error_code==buf_not_empty){
		if(ub->tail==((ub->buff)+(MAX_LEN))-1){
			//If tail is at the last position of the buffer, remove the item there and then put the tail at the base address of the buffer
			ub->tail=ub->buff;
			rd=*(ub->tail);
			*(ub->tail)=0;
			(ub->new_len)--;
			return rd;
		}
		else{
			//Otherwise remove the item at the location of the tail and increment
			(ub->tail)++;
			rd=*(ub->tail);
			*(ub->tail)=0;
			(ub->new_len)--;
			return rd;
		}
	}
	else if(error_code==buf_empty){
		//If buffer is empty,do not remove item and return error
		return buf_empty;
	}
}
