#include <detpic32.h>
void delay(unsigned int);
 int main(void)
 {
 	TRISDbits.TRISD0 = 0; // RD0 configured as output
	LATDbits.LATD0 = 0;	//comeca apagado
	while(1)
	{
			
 			LATDbits.LATD0 = !LATDbits.LATD0;
			delay(1);
	 }
	return 0;
 } 

void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 6000; i != 0; i--)
		;
	;
}
