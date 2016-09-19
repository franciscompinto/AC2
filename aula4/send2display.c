void send2dispaly(unsigned char value){
	static unsigned char  d7seg[] = {0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
	int hi = value/16; 	//(value&0xF0)>>4
	int lo = value-(hi*16)	//value&0x0F
	
	LATB = LATB & 0xFC00;
	LATBbits.LATB8=0;
	LATBbits.LATB9=1;
	LATB=LATB|d7seg[lo]
	delay(1);

	//send digit high
	LATBbits.LATB8=1;
	LATBbits.LATB9=0;
	LATB=LATB|d7seg[hi]
	delay(1);

}

void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 10000; i != 0; i--)
		;
	;
}
