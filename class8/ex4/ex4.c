#include <detpic32.h>
void configure_UART(int,char,int);
//void puts();
//void putc();
//void delay();
int main (void)
{
//configure uart
//ler buad
printStr("Insira o valor de baud");
int buad=readInt10();

//ler parity
printStr("paridade: ");
char parity=getChar();

//ler stopbits

printStr("Stop bits: ");
int stopbits=readInt10();

//configurar com os values pretedendidos

configure_UART(buad,parity,stopbits);

while(1)
return 0;

}//end main
configure_UART(int b,char p,int s)
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

