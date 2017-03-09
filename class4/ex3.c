#include <detpic32.h>





int main(void){
	TRISB=TRISB & 0xFC00;
	LATBbits.LATB8 = 1;
	LATBbits.LATB9 = 0;


	while(1){
		printStr("\nintroduza uma letra entre A e G: ");
		char x = getChar();
		putChar(x);
		LATB=(LATB & 0xFC00) | 0x0200;
		if(x=='a' || x=='A'){
			//LATBbits.LATB1 = 1;
			LATB = LATB|0x02;
		}
		else if(x=='b' || x=='B'){
			//LATBbits.LATB0 = 1;
			LATB = LATB|0x01;
		}
		else if(x=='c' || x=='C'){
			//LATBbits.LATB6 = 1;
			LATB = LATB|0x40;
		}
		else if(x=='d' || x=='D'){
			//LATBbits.LATB5 = 1;
			LATB = LATB|0x20;
		}
		else if(x=='e' || x=='E'){
			//LATBbits.LATB4 = 1;
			LATB = LATB|0x10;
		}
		else if(x=='f' || x=='F'){
			//LATBbits.LATB2 = 1;
			LATB = LATB|0x04;
			}
		else if(x=='g' || x=='G'){
			//LATBbits.LATB3 = 1;
			LATB = LATB|0x08;
		}
		else if(x=='.'){
			//LATBbits.LATB7 = 1;
			LATB = LATB|0x80;
		}
		else{	
			LATB = LATB|0x02FF;
		}
	}
	
}





