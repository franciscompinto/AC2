#include <detpic32.h>
void send2display(unsigned char );
void delay(unsigned int );
unsigned char toBcd(unsigned char);
void setPWM(unsigned int dutyCycle);

int Namostras=8;
const static unsigned char pwmValues[]={3, 15, 40, 90};
volatile unsigned char value2display = 0; // Global variable 
float temperature = 0; 
int main(void){
	

	TRISE = TRISE | 0xF0;

	//adc
	TRISBbits.TRISB14=1;//rb14 ativo input
	AD1PCFGbits.PCFG14=0;//rb14 analog
	AD1CON1bits.SSRC = 7;   					
	AD1CON1bits.CLRASAM = 1; 	
	AD1CON3bits.SAMC = 16;  	 
	AD1CON2bits.SMPI = Namostras-1; 
	AD1CHSbits.CH0SA = 14; 		
	AD1CON1bits.ON = 1; 		
	//configure interup
	IPC6bits.AD1IP=1;
	IEC1bits.AD1IE=1;
	

	//configure interuo of T1
	T1CONbits.TCKPS = 3; 	// 1:256 prescaler (i.e fin = 625 KHz)
 	PR1 = PBCLK/256/4-1; 	// Fout = 20MHz / (256 * (78125 + 1)) = 4 Hz
 	TMR1 = 0; 		// Reset timer T2 count register
 	T1CONbits.TON = 1; 	// Enable timer T2 (must be the last command of the timer configuration sequence)	

	IFS0bits.T1IF = 0; // Reset timer T2 interrupt flag
	IPC1bits.T1IP = 2; // Interrupt priority (must be in range [1..6])
 	IEC0bits.T1IE = 1; // Enable timer T2 interrupts 


	//configure interup of T3
	T3CONbits.TCKPS = 2; 	// 1:4 prescaler 
 	PR3 = PBCLK/4/200-1; 	// Fout = 20MHz / (2 * (62499 + 1)) = 100 Hz
 	TMR3 = 0; 		// Reset timer T2 count register
 	T3CONbits.TON = 1; 	// Enable timer T2 (must be the last command of the timer configuration sequence)	

	IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag
	IPC3bits.T3IP = 1; // Interrupt priority (must be in range [1..6])

 	IEC0bits.T3IE = 1; // Enable timer T2 interrupts 
		
	OC1CONbits.OCM = 6; 	// PWM mode on OCx; fault pin disabled
 	OC1CONbits.OCTSEL=1;	// Use timer T2 as the time base for PWM generation
 	setPWM(0);		// Ton constant
	OC1CONbits.ON = 1; 	// Enable OC1 module 
		

 	IFS1bits.AD1IF = 0; // Reset AD1IF flag
	EnableInterrupts();

	while(1){
		char readSwitch = PORTE & 0x00F0;
		readSwitch = readSwitch >> 4;
		char op1 = readSwitch & 0x0003;
		char op2 = (readSwitch >> 2) & 0x0003;
		printf("OP1 -> %d    OP2 -> %d\r ", op1, op2);

		switch(op1){
			case 0:	// 00 – funciona como voltímetro (o LED deve ficar OFF) 

				IEC0bits.T1IE = 1; // Enable timer T1 interrupts 
				setPWM(0);
				//printf("case 0\n");
				break;
			case 1:	//01 – congela o valor da tensão (o LED fica ON com o brilho no máximo) 
				IEC0bits.T1IE = 0; // Desenable timer T1 interrupts 
				setPWM(100);
				//printf("case 1\n");

				break;
			case 2:	// 10 - controlo do brilho do LED (dependente dos bits RE7 e RE6) 
				//printf("case 2\n");
				setPWM(pwmValues[(int)op2]);
				value2display=pwmValues[(int)op2];
				break;
			default:
				break;
		}
	
	}
	return 0;
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
void _int_(4) isr_T1(void) // Replace VECTOR by the timer T1
 // vector number
 {	
	AD1CON1bits.ASAM=1;
	IFS0bits.T1IF = 0;
 } 

void _int_(12) isr_T3(void) // Replace VECTOR by the timer T3
 // vector number
 {	
	send2display(toBcd((char) value2display));
	IFS0bits.T3IF = 0;
 } 

void send2display(unsigned char value){
	TRISB = (TRISB & 0xFC00);
	static unsigned char displayFlag=0;
	static unsigned char  d7seg[]={0x77,0x41,0x3B,0x6B,0x4D,0x6E,0x7E,0x43,0x7F,0x6F,0x5F,0x7C,0x36,0x79,0x3E,0x1E};
	//printf("displayFlag= %d\n", displayFlag);	
		
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
void setPWM(unsigned int dutyCycle){

	if(dutyCycle >= 0 && dutyCycle <= 100){
		OC1RS = (int)(((20000000/4)/200) * dutyCycle/100);	
	}

}

