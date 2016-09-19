#include<detpic32.h>


int main(void){

	
	TRISD = TRISD & 0xF00F;

	TRISBbits.TRISB14=1;//rb14 ativo input
	AD1PCFGbits.PCFG14=0;//rb14 analog

	AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
	 // mode an internal counter ends sampling and
	 // starts conversion
	 AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
	 // interrupt is generated. At the same time,
	 // hardware clears the ASAM bit
	 AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	 AD1CON2bits.SMPI = 0; // Interrupt is generated after XX samples
	 // replace XX by the desired number of
	 // consecutive samples
	 AD1CHSbits.CH0SA = 14; // replace YY by the desired input
	 // analog channel (0 to 15)
	 AD1CON1bits.ON = 1; // Enable A/D converter
	 // This must the last comman
	int adc_val=0;

	while(1){
		AD1CON1bits.ASAM = 1; // Start conversion 
		while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done
		IFS1bits.AD1IF = 0;

		adc_val=ADC1BUF0;
		printf("%d \n",adc_val);
		if(adc_val>= 0 && adc_val < 128){
			LATD = (LATD & 0xF00F) | 0x0010;
		}else if(adc_val>= 128 && adc_val < 256){
			LATD = (LATD & 0xF00F) | 0x0030;
		}else if(adc_val>= 256 && adc_val < 384){
			LATD = (LATD & 0xF00F) | 0x0070;
		}else if(adc_val>= 384 && adc_val < 512){
			LATD = (LATD & 0xF00F) | 0x00F0;
		}else if(adc_val>= 512 && adc_val < 640){
			LATD = (LATD & 0xF00F) | 0x01F0;
		}else if(adc_val>= 640 && adc_val < 768){
			LATD = (LATD & 0xF00F) | 0x03F0;
		}else if(adc_val>= 768 && adc_val < 896){
			LATD = (LATD & 0xF00F) | 0x07F0;
		}else if(adc_val>= 896 && adc_val < 1024){
			LATD = (LATD & 0xF00F) | 0x0FF0;
		}

	}


}
