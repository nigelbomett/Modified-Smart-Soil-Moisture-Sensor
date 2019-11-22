/*
 *     SMART SOIL MOISTURE SENSOR
 *  F17/1592/2012 Bomett Nigel Kimutai
 * 
 */



#include "derivative.h" /* include peripheral declarations */
#include "mcg.h"
#include "Systick.h"
#include <string.h>
#include <stdio.h>
#include "ConsoleIO.h"
#include <mcg.h>
#include <Systick.h>
#include "uartBuffer.h"
#include "data.h"
#include "memory.h"
#include "uartHandler.h"

typedef unsigned char bool;
#define  FALSE  0
#define  TRUE   1
#define RED_LED (1<<18)
#define GREEN_LED (1<<19)
#define BLUE_LED (1<<1)

int soilmoist;
uint8_t rx_str[1000];
uint8_t tx_str[1000];
int sample=10;
int sensorReading[10];
int readIndex = 0;
int total =0;
int average=0;
char *data1,*data2,str2[100],str1[100];
int main(void)
{
	
	uint16_t sbr;					/*Variable to configure the baud rate*/
	uint8_t temp;
	
	//Clock gating
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;      /*Enable the UART clock*/
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1); //Select  48MHz clock
		
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK; // Enable Port B and Port D clocks for the LED
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK; //Enable clock for ADC
	
	ADC0_CFG1 |= ADC_CFG1_MODE(2)|ADC_CFG1_ADIV(2);//10 bits ADC and Clock divide select
			
	ADC0_SC1A  = ADC_SC1_ADCH(31); //Disable module
	

	
	//Set the function of the pins
	PORTD_PCR6 |= PORT_PCR_MUX(3); //Set Rx pin for the UART
	PORTD_PCR7 |= PORT_PCR_MUX(3); //Set Tx pin for the UART
	PORTB_PCR19 =(PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); //Green LED
	PORTB_PCR18 = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); //Red LED
	PORTD_PCR1 = (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); //Blue LED
	
	//Set the GPIO pins as output
	GPIOB_PDDR = RED_LED|GREEN_LED;
	GPIOD_PDDR = BLUE_LED;
		   	
		
	UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );  /*Disable Tx and Rx*/
	UART0_C1 = 0; /*Default settings of the register*/

	sbr = (uint16_t)((48000*1000)/(38400 * 17));/* Calculate baud settings */

    temp = UART0_BDH & ~(UART_BDH_SBR(0x1F));/*Save the value of UART0_BDH except SBR*/
	UART0_BDH = temp | (((sbr & 0x1F00) >> 8)); //Set the BDH value to zero
	UART0_BDL = (uint8_t)(sbr & UART_BDL_SBR_MASK); //Set the BDL value to 0x4E
	
	//tx buffer initialisation
	tx_buf.buff = initialize(&tx_buf);
	tx_buf.head=tx_buf.data;
	tx_buf.tail=tx_buf.data;
	tx_buf.buff=tx_buf.data;
	tx_buf.new_len= 0;

    //rx buffer initialisation
	rx_buf.buff = initialize(&rx_buf);
	rx_buf.head=rx_buf.data;
	rx_buf.tail=rx_buf.data;
	rx_buf.buff=rx_buf.data;
	rx_buf.new_len= 0;

	//Set NVIC interrupts and CPU interrupts
	NVIC_EnableIRQ(UART0_IRQn);
	UART_C2_REG(UART0_BASE_PTR) |= UART_C2_RIE_MASK; //Setup receiver interrupt
			    		

	UART0_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );    /* Enable receiver and transmitter */

	
	//Set all LEDs off
	GPIOB_PSOR |= RED_LED;
			   		
	GPIOB_PSOR |= GREEN_LED;
			   		
	GPIOD_PSOR |= BLUE_LED;
	
	//Measurement function 
	unsigned short ADC_read10b(unsigned char channelNumber) 
	   {

		ADC0_SC1A = channelNumber & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion,selecting the channel to be used
		while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  			//Conversion in progress
		while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));		//Until conversion complete
	
	    return ADC0_RA; //Get value from data return register
	
		}

	Init_Systick();
	ConsoleIO_Init(); 
	__enable_irq(); //Enable interrupt requests
  
	
						
	//Initialise all sensor readings to zero
	int currentReading;
	for(currentReading = 0;currentReading<11;currentReading++){
		sensorReading[currentReading] = 0;
	}
	
	//delay_ms(20000); //Delay to allow the GSM network reception
	char response;

	int i=0;
	//Initialise GSM
	
	puts("AT\r");
	delay_ms(2000);
	//puts("AT\r");
	//delay_ms(1000);
//	puts("AT+IPR=38400\r");
//		delay_ms(2000);
	
	//while(((response = read_data(&rx_buf))!='\0')&&((response = read_data(&rx_buf))!='K')){

	while((response = read_data(&rx_buf))!='K'){
			GPIOB_PCOR |= RED_LED;
			GPIOD_PCOR |= BLUE_LED;
			delay_ms(100);	
			
										
			GPIOB_PSOR |= RED_LED;
			GPIOD_PSOR |= BLUE_LED;
			delay_ms(100);
	 	     
		//	puts("AT+IPR=38400\r");
		 //    delay_ms(2000);
				 	     
		//	puts("AT\r");
	 	//     delay_ms(2000);
	 	   
			//Store the received characters into the array string[] one-by-one
			str1[i++] = response;
			
				}
			
			str1[i] = 'K';
			
			//Insert NULL to terminate the string
			str1[(i+1)] = '\0';
			
			//return the received string
			
			data1=str1;
			puts(data1);
			delay_ms(2000);
			my_memzero(rx_str,i); //remove data from rx_str
			 
	
        	puts("ATE0\r");//Turn off echo
	        delay_ms(2000);
	

	
	for(;;) {
	
		
		
		GPIOB_PSOR |= RED_LED;
								   		
		GPIOB_PSOR |= GREEN_LED;
								   		
		GPIOD_PSOR |= BLUE_LED;
		
	   int count;
	   for(count=0;count<11;count++){
	    
	   
	    soilmoist=((0.0005*(1023-ADC_read10b(0))+0.1368)*100);		
		
		sensorReading[readIndex] = soilmoist;
		
	    
		readIndex = readIndex + 1;
	   //total += sensorReading[count];
	}
	   total += sensorReading[0]+sensorReading[1]+sensorReading[2]+sensorReading[3]+sensorReading[4]
	            +sensorReading[5]+sensorReading[6]+sensorReading[7]+sensorReading[8]+sensorReading[9];  
		
		
		if(readIndex >= sample ){
			readIndex = 0;
		}
		average = total/sample;
		total=0;
		
		char value[5];
		//ftoa(average,value,4);
		itoa(average,value,10);

		//Upload data to web server using HTTP
			puts("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r");
			delay_ms(2000);
			
			puts("AT+SAPBR=3,1,\"APN\",\"bew.orange.co.ke\"\r");
			delay_ms(2000); 
	/*
			puts("AT+SAPBR=3,1,\"APN\",\"web.safaricom.com\"\r");
			delay_ms(2000);
			puts("AT+SAPBR=3,1,\"USER\",\"web\"\r");
			delay_ms(2000);
			puts("AT+SAPBR=3,1,\"PWD\",\"web\"\r");
			delay_ms(2000);
   */
	
		    puts("AT+SAPBR=1,1\r");
			delay_ms(2000);
			puts("AT+SAPBR=2,1\r");
			delay_ms(4000);
			puts("AT+HTTPINIT\r");
			delay_ms(2000);
			puts("AT+HTTPPARA=\"CID\",1\r");
			delay_ms(2000);
			printf("AT+HTTPPARA=\"URL\",\"1592project.comli.com/index.php?");
			//printf("AT+HTTPPARA=\"URL\",\"1592project.byethost22.com/index.php?");
			//printf("AT+HTTPPARA=\"URL\",\"1592project.epizy.com/index.php?");
			//printf("AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/update?api_key=EBR5LI050C7SSLT6&field1=");
			printf("soilmoisture=");
		    printf(value);
			puts("\"\r");
			delay_ms(4000);
			puts("AT+HTTPACTION=0\r");
			delay_ms(15000);
			puts("AT+HTTPTERM\r");
			delay_ms(2000);
			puts("AT+SAPBR=0,1\r");
			delay_ms(2000);
/*	
			puts("AT+COPS?\r");
			delay_ms(1000);
			puts("AT+COPS?\r");
			delay_ms(1000);
			//puts("AT+IPR?\r");
			//delay_ms(1000);

*/
		
	/* TCP/IP connection to thing speak*/
/*
	puts("AT+CPIN?\r");
	 delay_ms(1000);
	 puts("AT+CREG?\r");
	 delay_ms(1000);
	 puts("AT+CGATT?\r");
	 delay_ms(1000);
	 puts("AT+CIPSHUT\r");
	 delay_ms(1000);
	 puts("AT+CIPSTATUS\r");
	 delay_ms(2000);
	 puts("AT+CIPMUX=0\r");
	 delay_ms(2000);
	 //puts("AT+CSTT=\"web.safaricom.com\",\"web\",\"web\"\r");//Setting the APN
	 puts("AT+CSTT=\"bew.orange.co.ke\",\"\",\"\"\r");
	 delay_ms(3000);
	 puts("AT+CIICR\r");//bring up wireless connection
	 delay_ms(7000);
	 puts("AT+CIFSR\r");//get local IP address
	 delay_ms(4000);
	 puts("AT+CIPSPRT=0\r");
	 delay_ms(3000);
	 puts("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"\r");//start up the connection
	 delay_ms(7000);
	 puts("AT+CIPSEND\r");//begin to send data
	 delay_ms(4000);
	 printf("GET http://api.thingspeak.com/update?api_key=EBR5LI050C7SSLT6&field1=0");
	 //printf("GET api.thingspeak.com/update?api_key=EBR5LI050C7SSLT6&field1=");
	 printf(value);
	 delay_ms(4000);
	 putchar(0x1a);
	 delay_ms(5000);
	 printf("\n\r");
	 puts("AT+CIPSHUT\r");
	 delay_ms(1000);
	 //puts("AT+IPR=38400\r");
	 //delay_ms(1000);
	 puts("AT+COPS?");
	 delay_ms(1000);
	 puts("AT+COPS?\r");
	 delay_ms(1000);
	
	
*/	 
			
//Testing responses after commands
/*

//if(be==buf_not_empty){
int n = 0;
	 //while(((response = read_data(&rx_buf))!='Q')&&(be==buf_not_empty)){
while((response = read_data(&rx_buf))!='C'){		
                GPIOB_PCOR |= RED_LED;
	 			GPIOB_PCOR |= GREEN_LED;
	 			delay_ms(100);	
	 			
	 										
	 			GPIOB_PSOR |= RED_LED;
	 			GPIOB_PSOR |= GREEN_LED;
	 			delay_ms(100);
	 	 	     
	// 			puts("AT+IPR?\r");
	// 		     delay_ms(2000);
	 				 	     
	 			//puts("AT\r");
	 	 	    // delay_ms(2000);
	 	 	   
	 			//Store the received characters into the array string[] one-by-one
	 			str2[n++] = response;
	 			//my_memzero(rx_str,i);
	 				}
	 			
	 			str2[n] = 'C';
	 			
	 			//insert NULL to terminate the string
	 			str2[(n+1)] = '\0';
	 			
	 			//return the received string
	 			
	 			data2=str2;
	 			puts(data2);
	 			delay_ms(2000);
	 			my_memzero(rx_str,n); //remove data from rx_str
//}		
 */
		if(average<25){
		      GPIOB_PCOR |= RED_LED;
			  delay_ms(1000);	
		/*							
			  GPIOB_PSOR |= RED_LED;
			  delay_ms(1000);    
		*/
		
		}
		if((average>25) && (average<50)){
			  GPIOB_PCOR |= GREEN_LED;
				
		}
		if(average>50){
					
		      GPIOD_PCOR |= BLUE_LED;
			  delay_ms(1000);	
			  
			  //  GPIOB_PSOR |= GREEN_LED;
			  //  delay_ms(1000);
		
		}
		//my_memzero(rx_str,i); //remove data from rx_str
		delay_ms(60000);
	}

	return 0;

}


