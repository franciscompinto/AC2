#include <detpic32.h>
void delay(unsigned int );
void main(void){
	TRISBbits.TRISB14=1;//rb14 ativo input
	AD1PCFGbits.PCFG14=0;//rb14 analog


	AD1CON1bits.SSRC = 7;   // Conversion trigger selection bits: in this
				// mode an internal counter ends sampling and
				// starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
				// interrupt is generated. At the same time,
				// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16;   // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 0; // Interrupt is generated after XX samples
				// replace XX by the desired number of
				// consecutive samples
	AD1CHSbits.CH0SA = 14; 	// replace YY by the desired input
				// analog channel 14
	AD1CON1bits.ON = 1; 	// Enable A/D converter
				// This must the last command of the A/D
				// configuration sequence 

	IPC6bits.AD1IP=1;
	IEC1bits.AD1IE=1;

 	IFS1bits.AD1IF = 0; // Reset AD1IF flag
 	EnableInterrupts(); // Global Interrupt Enable
 	AD1CON1bits.ASAM=1; // Start A/D conversion

	TRISEbits.TRISE0=0;//RE0 ativo output
	LATEbits.LATE0=0;
	AD1CON1bits.ASAM=1; 		// Start conversion 
	while(1){
	delay(500);
}
}
 void _int_(27) isr_adc() 	// Replace VECTOR by the A/D vector
 				// number - see "PIC32 family data
 				// sheet" (pages 122-124)
 {
 	LATEbits.LATE0=1;		// Set RE0 
 	printInt(ADC1BUF0,0x00030010);	// Print ADC1BUF0 value // Hexadecimal (3 digits format)
	printStr("\n");	
	LATEbits.LATE0=0;		// Reset RE0 =1		
	AD1CON1bits.ASAM=1; 			// Start A/D conversion
 	IFS1bits.AD1IF = 0; 			// Reset AD1IF flag
 } 
void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 5000; i != 0; i--)
		;
	;
}
