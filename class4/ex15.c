#include <detpic32.h>
void send2display(unsigned char );
	void delay(unsigned int );
unsigned char toBcd(unsigned char);

void main(void){ 


	TRISB = (TRISB & 0xFC00);
	LATEbits.LATE0=1;
	char counter = 0;
	int counterTmp = 0;
	int cnt = 0;
	int i;
	while(1){

		if(counter == 0 && cnt <5){
			send2display(toBcd(0)); //obrogar a sempre que ser zero
			LATBbits.LATB8=0;
			LATBbits.LATB9=0;
			delay(500);
			LATBbits.LATB8=1;
			LATBbits.LATB9=1;
			delay(500);
			cnt++;
			
		if(cnt == 4)
			cnt=0;
		
	}
		i=0;
		do{
			delay(10);
			send2display(toBcd(counter));
		}while(++i <4);
		if(counterTmp++ == 4)
		{	
			counterTmp = 0;	
			if(counter >= 59)
				counter = 0;
			else
				counter ++;
		}
		

		}



}
void send2display(unsigned char value){

	static unsigned char displayFlag=0;
	static unsigned char  d7seg[] ={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
	printf("displayFlag= %d\n", displayFlag);
	//delay(500);
	LATB = (LATB & 0xFC00);
	
	int low =  (value & 0x0F);
	int high = value >> 4;
	if(displayFlag==0)
	{
		LATBbits.LATB8=0;
		LATBbits.LATB9=1;
		LATB = (LATB & 0xFF00) | (d7seg[(low)]);
		if((value %2)!=0)
			LATBbits.LATB7=1;
	}else{
		//send digit high
		LATBbits.LATB8=1;
		LATBbits.LATB9=0;
		LATB = (LATB & 0xFF00) | d7seg[(high)];
		if((value %2)==0)
			LATBbits.LATB7=1;
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
unsigned char toBcd(unsigned char valBin)
{
	return ((valBin / 10) << 4) + (valBin % 10);
}
