#include <detpic32.h>
//funcoes
void delay(unsigned int );
int Namostras=8;
int posicao=0;
int VAL_AD=0;
	static unsigned int  cobra[] ={0x104,0x102,0x101,0x210,0x220,0x240,0x201,0x202, 0x204, 0x140, 0x120, 0x110};
int main(void){
	int time=0, i=0;
	TRISBbits.TRISB14=1;//rb14 ativo input
	AD1PCFGbits.PCFG14=0;//rb14 analog

	AD1CON1bits.SSRC = 7;   	// Conversion trigger selection bits: in this
					// mode an internal counter ends sampling and
					// starts conversion
	AD1CON1bits.CLRASAM = 1; 	// Stop conversions when the 1st A/D converter
					// interrupt is generated. At the same time,
					// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16;  	 // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = Namostras-1;		 // Interrupt is generated after XX samples
					// replace XX by the desired number of
					// consecutive samples
	AD1CHSbits.CH0SA = 14; 		// replace YY by the desired input
					// analog channel 14
	AD1CON1bits.ON = 1; 		// Enable A/D converter
					// This must the last command of the A/D configuration sequence 
	//configure interup
	IPC6bits.AD1IP=1;
	IEC1bits.AD1IE=1;

	IFS1bits.AD1IF = 0; // Reset AD1IF flag
	EnableInterrupts(); // Global Interrupt Enable
//	AD1CON1bits.ASAM=1; // Start A/D conversion


	TRISB = TRISB & 0xFC00; 
	LATB=(LATB & 0xFC00) | 0x0300;
	while(1){
		 
		
			AD1CON1bits.ASAM=1; 		// Start conversion 
			i=0;
	
		
		
		if(VAL_AD>= 0 && VAL_AD < 128){
			time = 250;
		}else if(VAL_AD>= 128 && VAL_AD < 256){
			time = 500;
		}else if(VAL_AD>= 256 && VAL_AD < 384){
			time = 750;
		}else if(VAL_AD>= 384 && VAL_AD < 512){
			time = 1000;
		}else if(VAL_AD>= 512 && VAL_AD < 640){
			time = 1250;
		}else if(VAL_AD>= 640 && VAL_AD < 768){
			time = 1500;
		}else if(VAL_AD>= 768 && VAL_AD< 896){
			time = 1750;
		}else if(VAL_AD>= 896 && VAL_AD < 1024){
			time = 2000;
		}
	
		printf("4adc: %d, tempo: %d \n", VAL_AD, time);
		LATB=(LATB & 0xFC00);
		LATB = LATB | cobra[posicao];
		delay(time);
		
		if(posicao++ >= 12){
			posicao=0;
		}
		 
		
	}
	return 0;
}
void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 5000; i != 0; i--)
		;
	;
} 
void _int_(27) isr_adc(){

		


		int *p = (int *)(&ADC1BUF0);
		int j;
		int sunAmostras=0;
 		for( j = 0; j < Namostras; j++ )
 		{
 			 sunAmostras += p[j*4]; 
 		} 
		VAL_AD=sunAmostras/Namostras;
		

		IFS1bits.AD1IF=0;		// Reset AD1IF

}
 
