#include <detpic32.h>
void send2displays(unsigned char value);
void delay(unsigned int );
char value =0;
	int Namostras = 8;
	int i = 0, z=0;
int main(void){
	
	

	TRISE = (TRISE & 0xFFF0) | 0x00F0;
	LATE = LATE | 0x0F;
	TRISDbits.TRISD0=0;
	LATDbits.LATD0=0;	
	LATBbits.LATB14=1;
	AD1PCFGbits.PCFG14 = 0;

	 AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	 AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	 AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	 AD1CON2bits.SMPI = Namostras-1; // Interrupt is generated after XX samples
	 AD1CHSbits.CH0SA = 14; // replace YY by the desired input
	 AD1CON1bits.ON = 1; // Enable A/D converter

	 IPC6bits.AD1IP=1;
	 IEC1bits.AD1IE=1;
	 IFS1bits.AD1IF = 0; // Reset AD1IF flag
	
	 AD1CON1bits.ASAM = 1; // Start conversion 

	 //timer
	 T3CONbits.TCKPS = 6; // 1:32 prescaler (i.e. fin = 625 KHz)
	 PR3 = PBCLK/64/50-1; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
	 TMR3 = 0; // Reset timer T2 count register
	 T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
	 // timer configuration sequence) 


	 IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag
 	IPC3bits.T3IP = 1; // Interrupt priority (must be in range [1..6])
 	IEC0bits.T3IE = 1; // Enable timer T2 interrupts 
 	 EnableInterrupts(); // Global Interrupt Enabl



	while(1){
		//delay(10);
	//	if(i++ == 25){
			printInt((int)value,10); 
			putChar('\n');
	/*		i=0;
		}*/
		

		
		i = 0;
 do
 {
delay(5);
 send2displays((char)value);
 } while(++i < 4); 
		
		
	
	}
		
	





	return 0;
}
void send2displays(unsigned char value)
{
	TRISB = (TRISB & 0xFC00);
	static unsigned char displayFlag=0;
	static unsigned char  d7seg[] ={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
	//printf("displayFlag= %d\n", displayFlag);
	//delay(500);
	LATB = (LATB & 0xFC00);
			//ponto activo
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

 void _int_(27) isr_adc(void)
 {
 			LATDbits.LATD0=1;
 			int *p = (int *)(&ADC1BUF0);
			int j;
			int sunAmostras=0;
	 		for( j = 0; j < Namostras; j++ )
	 		{
	 			 sunAmostras += p[j*4]; 
	 		} 

			value=sunAmostras/Namostras;
			LATDbits.LATD0=0;
 		IFS1bits.AD1IF = 0; // Reset AD1IF flag
 } 

  void _int_(12) isr_T3(void) // Replace VECTOR by the timer T3
 // vector number
 {
 	AD1CON1bits.ASAM = 1; // Start conversion 
  send2displays((char)value);

 	IFS0bits.T3IF = 0;

 } 