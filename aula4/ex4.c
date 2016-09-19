#include <detpic32.h>


void delay();


int main(void){
	static const unsigned char codes[] = {0x02, 0x01, 0x40, 0x20, 0x10, 0x04, 0x08};
	TRISB=TRISB & 0xFC00;
	LATBbits.LATB8 = 1;
	LATBbits.LATB9 = 0;
	int i;	

	while(1){
	
		LATB=(LATB & 0xFC00) | 0x0200;
			
		for(i=0;i<7; i++){
			LATB=LATB | codes[i];
			delay(1000);

		}
		LATB=(LATB & 0xFC00) | 0x0100;
		for(i=0;i<7; i++){
			LATB=LATB | codes[i];
			delay(1000);

		}
	}
	

}

void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 10000; i != 0; i--)
		;
	;
}




