#include <detpic32.h>
//funcoes
void delay(unsigned int );

int posicao=0;
	static unsigned char  cobra[] ={0x04,0x02,0x01,0x08,0x10,0x20,0x40,0x08};
int main(void){

	TRISB = TRISB & 0xFC00; 
	LATB=(LATB & 0xFC00) | 0x0100;
	while(1){
		printStr("ola");
		delay(250);
		LATB=(LATB & 0xFC00) | 0x0100;
		LATB = LATB | cobra[posicao];
		delay(250);
		
		if(posicao++ >= 7){
			posicao=0;
		}
		 
		
	}
	return 0;
}
void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 5000; i != 0; i--)
		;
	;
} 
