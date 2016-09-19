#include <detpic32.h>
void send2displays(unsigned char value);
void delay(unsigned int );

int main(void){

	TRISE = (TRISE & 0xFFF0) | 0x00F0;
	LATE = LATE | 0x0F;

	LATBbits.LATB14=1;
	AD1PCFGbits.PCFG14 = 0;

	 AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	 AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	 AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	 AD1CON2bits.SMPI = 0; // Interrupt is generated after XX samples
	 AD1CHSbits.CH0SA = 14; // replace YY by the desired input
	 AD1CON1bits.ON = 1; // Enable A/D converter


	while(1){

		AD1CON1bits.ASAM = 1; // Start conversion 
		while(IFS1bits.AD1IF == 0 );
		char value = (ADC1BUF0 & 0x000F);
		printInt(value,0x000A0002); 
		putChar('\n');
		send2displays(value);
		delay(1000);
	}





	return 0;
}
void send2displays(unsigned char value)
 {
	TRISB = (TRISB & 0xFC00);
	//static unsigned char displayFlag=0;
	static unsigned char  d7seg[]={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
 	char digit_low = value & 0x0F;
 	//digit_high = value >> 4;

	 	LATB = (LATB & 0xFF00) | d7seg[(digit_low)];
	 	LATBbits.LATB8=0;
	 	LATBbits.LATB9=1;
 }
 void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 5000; i != 0; i--)
		;
	;
}
