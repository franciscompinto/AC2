#include<detpic32.h>
int main(void){
	T3CONbits.TCKPS = 7; 	// 1:256 prescaler (i.e fin = 625 KHz)
 	PR3 = 39061.5; 		// Fout = 20MHz / (256 * (62499 + 1)) = 10 Hz
 	TMR3 = 0; 		// Reset timer T2 count register
 	T3CONbits.TON = 1; 	// Enable timer T2 (must be the last command of the
 				// timer configuration sequence)
	
	IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag
	IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6])
 	IEC0bits.T3IE = 1; // Enable timer T2 interrupts 	
	EnableInterrupts();
	while(1);	
	
	
	
	return 0;
}
void _int_(12) isr_T3(void) // Replace VECTOR by the timer T3
 // vector number
 {	
	 putChar('.');
	IFS0bits.T3IF = 0;
 } 

