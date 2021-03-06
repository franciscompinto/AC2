#include <detpic32.h>
void send2displays(unsigned char);
void delay(unsigned int );
unsigned char toBcd(unsigned char);
int adc_val=0;
int main(void){
int v=0,i=0;
	TRISE = TRISE | 0xF0;
	

	TRISBbits.TRISB14=1;
	AD1PCFGbits.PCFG14=0;

	AD1CON1bits.SSRC = 7; 
	AD1CON1bits.CLRASAM = 1; 
	AD1CON3bits.SAMC = 16; 
	AD1CON2bits.SMPI = 0; 
	AD1CHSbits.CH0SA = 14; 
	AD1CON1bits.ON = 1; 
	while(1){
		AD1CON1bits.ASAM = 1; // Start conversion 
 		while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done 
		 IFS1bits.AD1IF = 1;
		adc_val=ADC1BUF0;
		
		
		v=(((adc_val*66)+33)/1024)-9;
		printf("test: %d\n", v);
		i=0;
		if(v<0){
			do{
				delay(5);
				send2displays(toBcd((char)v));
			
			}while(++i <4);
			delay(500);
			LATBbits.LATB8=0;
			LATBbits.LATB9=0;
			delay(500);
		}else{
			do{
				delay(5);
				send2displays(toBcd((char)v));
			
			}while(++i <4);
		}
	

	}
	return 0;
}
void send2displays(char unsigned value)
 {
	//printf("ola %d\n",  value);
	TRISB = TRISB & 0xFC00;
 	static unsigned char displayFlag = 0;
	static unsigned char d7seg[]={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
 
	LATB = (LATB & 0xFC00);		//ponto activo
	int low = value & 0x0F;
 	int high = value >> 4;

  	if (displayFlag==0){
		LATBbits.LATB8=0;
		LATBbits.LATB9=1;
		if(value<=90 && value >=0){
		
			LATB= (LATB & 0xFF00) |( d7seg[(low)]);
		}else{
			if(value >= 144){

				LATB= (LATB & 0xFF00) |( d7seg[(abs(value-149))]);
			}else{
				LATB= (LATB & 0xFF00) |( d7seg[(abs(value-131))]);
			}
			
			
		}


	}else{
		LATBbits.LATB8=1;
		LATBbits.LATB9=0;
		if(value<=90 && value >=0){
		
			LATB= (LATB & 0xFF00) |( d7seg[(high)]);
		}else{
			
 			LATB= (LATB & 0xFF00) |(0x008);
			
		}	
	}
	displayFlag=!displayFlag;
 
 } 
void delay(unsigned int n_intervals)
{
	 volatile unsigned int i;

	 for(; n_intervals != 0; n_intervals--)
	 for(i = 5000; i != 0; i--)
	 ;
} 
unsigned char toBcd(char unsigned valBin)
{
	return ((valBin / 10) << 4) + (valBin % 10);
}

