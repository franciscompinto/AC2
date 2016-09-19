#include <detpic32.h>
void send2displays(unsigned char );
void delay(unsigned int );
unsigned char toBcd(unsigned char);
int main(void){
	TRISE = TRISE | 0xF0;
	while(1){
		int c=PORTE;
		c=c & 0x70;
		c=c>>4;
		send2displays(toBcd((char)c));
		
		printf("ola %d\n", c);
	}
	return 0;
}
void send2displays(unsigned char value)
 {
	TRISB = TRISB & 0xFC00;
 	static unsigned char displayFlag = 0;
	static unsigned char d7seg[]={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
 
	LATB = (LATB & 0xFC00);		//ponto activo
	int low = value & 0x0F;
 	int high = value >> 4;

  	//if (displayFlag==0){
		LATBbits.LATB8=1;
		LATBbits.LATB9=0;
		LATB = (LATB & 0xFF00) | (d7seg[(low)]);

	/*}else{
	
		LATBbits.LATB8=1;
		LATBbits.LATB9=0;
		LATB= (LATB & 0xFC00) |( d7seg[high]);
 
	}*/
 
 } 
void delay(unsigned int n_intervals)
{
	 volatile unsigned int i;

	 for(; n_intervals != 0; n_intervals--)
	 for(i = 5000; i != 0; i--)
	 ;
} 
unsigned char toBcd(unsigned char valBin)
{
	return ((valBin / 10) << 4) + (valBin % 10);
}

