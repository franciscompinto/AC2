#include <detpic32.h>
void send2displays(unsigned char value);


int main(void){

	TRISE = (TRISE & 0xFFF0) | 0x00F0;
	LATE = LATE | 0x0F;
	while(1){

		char value = (PORTE & 0xF0);
		value = value >> 4;
		send2displays(value);
		LATE = (LATE & 0xF0 )| value;
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
