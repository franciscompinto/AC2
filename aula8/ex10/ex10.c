#include <detpic32.h>
char getc(void);
void putc(char);
void puts(char *);
void delay(unsigned int);
void configureUART(int,char,int);
int main (void)
{
configureUART(115200,'N',1);

IEC0bits.U1RXIE=1;
IEC0bits.U1EIE=1;
IPC6bits.U1IP=1;
IFS0bits.U1RXIF=0;
EnableInterrupts();
while(1);
	return 0;//
}
configureUART(int b,char p,int s)
{
if(b>=600 && b<=115200)
	U1BRG=(int)((20000000+8*b)/(16*b))-1;
else
	U1BRG=10;
U1MODEbits.BRGH=0;
//brg configurated com diferentes cases
	switch(p)
	{
	case 'e':
	case 'E':
		U1MODEbits.PDSEL=1;//8 -bit data no parity
		break;
	case 'n':
	case 'N':
		U1MODEbits.PDSEL=0;//8 -bit data no parity
		break;
	case'o':
	case 'O':
		U1MODEbits.PDSEL=2;//8 -bit data no parity
		break;
	default:
		U1MODEbits.PDSEL=0;//8 -bit data no parity
		break;
	}	
	switch(s)
	{
	case 2:
	U1MODEbits.STSEL=1;//8 -bit data no parity	
	break;
	case 1:
	U1MODEbits.STSEL=0;//8 -bit data no parity
	break;
	default:
	U1MODEbits.STSEL=0;//8 -bit data no parity

	}
U1STAbits.UTXEN=1;//uart transmitter enabled
U1STAbits.URXEN=1;//receiver enabled
U1MODEbits.ON=1;//URXEN is activated because of this code line
}
puts(char *str)
{
while(*str!='\n')
	{
	putc(*str);
	str++;
	}
}
putc(char byte2send)
{
while(U1STAbits.UTXBF==1);
U1TXREG=byte2send;
}
delay(unsigned int n_intervals)
{
        volatile unsigned int i;
        for(; n_intervals != 0; n_intervals--)
                for(i = 4998; i != 0; i--)
                ;
        ;
}
void _int_(24) isr_uart1(void)
{
putc(U1RXREG);
//clear uart rx interrupt flag
IFS0bits.U1RXIF=0;
}

