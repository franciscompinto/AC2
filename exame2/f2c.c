#include <detpic32.h>
void send2displays(unsigned char value);
void delay(unsigned int );
char value =0;
	int Namostras = 8;
int main(void){
	int i = 0, j = 0, z=0;
	

	TRISE = (TRISE & 0xFFF0) | 0x00F0;
	LATE = LATE | 0x0F;

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
	 EnableInterrupts(); // Global Interrupt Enabl

	 AD1CON1bits.ASAM = 1; // Start conversion 



	while(1){
		//delay(10);
		if(i++ == 25){
			AD1CON1bits.ASAM = 1; // Start conversion 
			printInt(value,10); 
			putChar('\n');
			i=0;
		}
		j=0;
		 do
		 {
		delay(5);
			//if(z== 3){
				send2displays((char)value);
				//z=0;
		
			//}
		z++;
		 } while(++j < 4); 
		
		
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
 			int *p = (int *)(&ADC1BUF0);
			int j;
			int sunAmostras=0;
	 		for( j = 0; j < Namostras; j++ )
	 		{
	 			 sunAmostras += p[j*4]; 
	 		} 

			value=sunAmostras/Namostras;
 		IFS1bits.AD1IF = 0; // Reset AD1IF flag
 } 