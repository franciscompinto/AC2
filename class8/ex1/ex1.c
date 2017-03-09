#include <detpic32.h>
void configure_UART();
int main (void)
{
configure_UART();
while(1)
	return 0;
}
void configure_UART(void)
{
//configure uart
U1BRG=10;//115.200 bytes
U1MODEbits.BRGH=0;//standard speed
U1MODEbits.PDSEL=0;//8 -bit data no parity
U1MODEbits.STSEL=0;//1 stop bit
U1STAbits.UTXEN=1;//uart transmitter enabled
U1STAbits.URXEN=1;//receiver enabled
U1MODEbits.ON=1;//URXEN is activated because of this code line
}
