#include <detpic32.h>
void delay(unsigned int );
void main(void){
	int volatile aux;
	TRISBbits.TRISB14=1;//rb14 ativo input
	AD1PCFGbits.PCFG14=0;//rb14 analog


	AD1CON1bits.SSRC = 7;   // Conversion trigger selection bits: in this
				// mode an internal counter ends sampling and
				// starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
				// interrupt is generated. At the same time,
				// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16;   // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 16; // Interrupt is generated after XX samples
				// replace XX by the desired number of
				// consecutive samples
	AD1CHSbits.CH0SA = 14; 	// replace YY by the desired input
				// analog channel 14
	AD1CON1bits.ON = 1; 	// Enable A/D converter
				// This must the last command of the A/D
				// configuration sequence 
	TRISEbits.TRISE0=0;//rb14 ativo input
	LATEbits.LATE0=1;

	while(1){

		LATEbits.LATE0=1;		// Set RE0 
		AD1CON1bits.ASAM=1; 		// Start conversion 
		while(IFS1bits.AD1IF==0);	// Wait while conversion not done (AD1IF == 0) 
		LATEbits.LATE0=0;		// Reset RE0 
		aux=ADC1BUF0;	//passar para a aux o ADC1BUF0;
		IFS1bits.AD1IF=0;		// Reset AD1IF
		//printInt(ADC1BUF0,16);		//print
		//printStr("\n");

		int *p = (int *)(&ADC1BUF0);
		int i;
 		for( i = 0; i < 16; i++ )
 		{
 			printInt( p[i*4], 0x0004000A );
			 putChar('-');
 		} 
		 putChar('\n');
		
		
	}
}


