/*
* memory.c
* Created on 10-May-2017
*	Author: Nigel Bomett
*/

#include "MKL25Z4.h"
#include "memory.h"

int8_t my_memmove(uint8_t *src, uint8_t *dst,uint32_t length){
	uint32_t i = 0;
	uint8_t temp[5000];
	
	if(src){
		while(i<length){
			*(temp+i)=*(src+i);
			i++;
		}
		return 0;
	}
	else{
		return 1;
	}
}
void my_memzero(uint8_t *src,uint32_t length){
	uint16_t i=0,len=0;
	while(*(src+i)!='\0'){
		len++;
		i++;
	}
	i=0;
	
	if(src){
		while(i<length){
			*(src+i)=0;
			i++;
		}
		i=0;
	}
	else{
		return 1;
	}
	
}
int8_t my_reverse(uint8_t *src,uint32_t length){
	uint16_t counter;
	if(src){
		int8_t temp=0;
		for(counter=0;counter<(length/2);counter++){
			temp=*(src+counter);
			*(src+counter)=*(src+length-counter-1);
			*(src+length-counter-1)=temp;
		}
		return 0;
	}
	else{
		return 1;
	}
}
