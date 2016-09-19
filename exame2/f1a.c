#include <detpic32.h>





int main(void){

	TRISE = (TRISE & 0xFFF0) | 0x00F0;
	LATE = LATE | 0x0F;
	while(1){

		char value = (PORTE & 0xF0);
		value = value >> 4;

		LATE = (LATE & 0xF0 )| value;
	}





	return 0;
}