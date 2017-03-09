#include <detpic32.h>
void send2display(unsigned char );
	void delay(unsigned int );
void main(void){ 



	TRISB=TRISB & 0xFC00;
	int cont=0, i;
	while(1){
		i=0;
		do{
			delay(10);
			send2display(cont);
		}while(++i <4);
		
		if(cont == 255){
			cont=0;
		}else{
			cont++;
		}
			
		}



}
void send2display(unsigned char value){

	static unsigned char displayFlag=0;
	static unsigned char  d7seg[] ={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
	
	
	LATB = (LATB & 0xFC00);
	
	int low =  (value & 0x0F);
	int high = value >> 4;
	if(displayFlag)
	{
		LATBbits.LATB8=0;
		LATBbits.LATB9=1;
		LATB = (LATB & 0xFF00) | (d7seg[(low)]);
	}else{
		//send digit high
		LATBbits.LATB8=1;
		LATBbits.LATB9=0;
		LATB = (LATB & 0xFF00) | d7seg[(high)];
	}
	displayFlag=!displayFlag;
}

void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 5000; i != 0; i--)
		;
	;
}
