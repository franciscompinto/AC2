#include <detpic32.h>
void send2display(unsigned char );
void delay(unsigned int );
unsigned char toBcd(unsigned char);
int Namostras=8;
volatile unsigned char value2display = 0; // Global variable 
void main(void){
	int i=0;
	
	TRISBbits.TRISB14=1;//rb14 ativo input
	AD1PCFGbits.PCFG14=0;//rb14 analog
		
		


	AD1CON1bits.SSRC = 7;   	// Conversion trigger selection bits: in this
					// mode an internal counter ends sampling and
					// starts conversion
	AD1CON1bits.CLRASAM = 1; 	// Stop conversions when the 1st A/D converter
					// interrupt is generated. At the same time,
					// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16;  	 // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = Namostras-1; // Interrupt is generated after XX samples
					// replace XX by the desired number of
					// consecutive samples
	AD1CHSbits.CH0SA = 14; 		// replace YY by the desired input
					// analog channel 14
	AD1CON1bits.ON = 1; 		// Enable A/D converter
					// This must the last command of the A/D
					// configuration sequence 
	//configure interup
	IPC6bits.AD1IP=1;
	IEC1bits.AD1IE=1;
		
		

 	IFS1bits.AD1IF = 0; // Reset AD1IF flag
 	EnableInterrupts(); // Global Interrupt Enable
 	AD1CON1bits.ASAM=1; // Start A/D conversion

	while(1){
		delay(5);
		if(i++ == 25) // 250 ms	=> 4 convercoes por sec
		 { 
			AD1CON1bits.ASAM=1; 		// Start conversion 
			i=0;
		}
		
		send2display(toBcd((char) value2display));

		
	}
}
void _int_(27) isr_adc(){

		


		int *p = (int *)(&ADC1BUF0);
		int j;
		int sunAmostras=0, VAL_AD=0;
 		for( j = 0; j < Namostras; j++ )
 		{
 			 sunAmostras += p[j*4]; 
 		} 
		VAL_AD=sunAmostras/Namostras;
		value2display=(VAL_AD*33+511)/1023;

		IFS1bits.AD1IF=0;		// Reset AD1IF

}

void send2display(unsigned char value){
	TRISB = (TRISB & 0xFC00);
	static unsigned char displayFlag=0;
	static unsigned char  d7seg[]={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
	printf("displayFlag= %d\n", displayFlag);
		
		
		
		
	
		
		
		
	LATB = (LATB & 0xFC00);		//ponto activo
	int low =  (value & 0x0F);
	int high = value >> 4;
	if(displayFlag==0)
	{
		LATBbits.LATB8=0;
		LATBbits.LATB9=1;
		LATB = (LATB & 0xFF00) | (d7seg[(low)]);
		
			
	}else{
		//send digit high
		LATBbits.LATB8=1;
		LATBbits.LATB9=0;
		LATB = (LATB & 0xFF00) | d7seg[(high)];
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

