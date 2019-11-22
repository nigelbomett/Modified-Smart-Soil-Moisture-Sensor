/*
*data.c 
* Created on: 10-May-2017
*	Author: Nigel Bomett
*
*/
#include "MKL25Z4.h"
#include "data.h"

int32_t atoi(int8_t *str); 
int8_t * itoa(int32_t num,int8_t *str,int32_t base);

//Function definition for ascii string to integer function
int32_t atoi(int8_t *str){
	printf("string:%s\n",str); //Prints the input string
	int32_t i = 0;
	int32_t length=0;
	while(*(str+i)!='\0'){
		length++;
		i++;
	}
	for(i=0;i<length;i++){    //Converts the ascii character in the string to its corresponding integer value
		printf("%d",*(str+i));
	}
	return 0;
}

int8_t * itoa(int32_t num,int8_t *str, int32_t base) //function for converting data from integer to ascii string 
{
	int32_t i = 0;
	int32_t neg=0;
	//Handle 0 explicitely
	if(num==0){
		*str='0';
		i++;
		*(str+i)='\0';
		return str;
	}
	if(num<0 && base==16){
		sprintf(str,"%X",num);
		return str;
	}
	if(num<0 && base==8){
	
		sprintf(str,"%o",num);
		return str;
	}
	if(num<0 && (base == 10 || base == 2))
	{
		neg = 1;
		num = -num;
	}
	while(num != 0){
		int32_t rem = num % base;
		*(str+i) = (rem>9)?(rem-10) + 'a' : rem + '0';
		i++;
		num = num/base;
	}
	if(neg==1){
		*(str+i) = '-';
		i++;
	}
	reverse(str,i);
	*(str+i)='\0';
	return str;
	
}
void reverse(int8_t *str,int32_t length){
	int32_t start = 0;
	int32_t end = length -1;
	while(start<end){
		int8_t temp = *(str+start);
		*(str+start) = *(str+end);
		*(str+end) = temp;
		start++;
		end--;
	}
}
void ftoa(float n,int8_t *res,int32_t dec_place){
	int32_t neg = 0;
	if(n<0)
	{
		n = -n;
		neg=1;
		}
		//Extract integer part
		int32_t ipart = (int32_t)n;
		//Extract floating part
		float fpart = n -(float)ipart;
		
		//Convert integer part to string
		int32_t i = intToStr(ipart,res,0,neg);
		neg=0;
		if(dec_place != 0){
			*(res+i) = '.';
			
			fpart = fpart * pow(10,dec_place);
			intToStr((int)fpart,res+i+1,dec_place,neg);
		}
		
		
	}
	int intToStr(int32_t x,int8_t str[], int32_t d,int32_t negative){
		int32_t i = 0;
		while(x){
			str[i++] = (x%10) + '0';
			x = x/10;
		}
		while(i<d)
		 str[i++] = '0';
		 if(negative==1){
		 	str[i++] = '-';
		 }
		 reverse(str,i);
		 str[i] = '\0';
		 return i;
	}
