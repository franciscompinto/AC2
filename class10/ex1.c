#include<detpic32.h>
#define fSCL 100000
//fuctoin

void i2c1_init(unsigned int clock_freq);
void i2c1_start(void);
void i2c1_stop(void);
int i2c1_send(unsigned char value);

void i2c1_init(unsigned int clock_freq)
{
	I2C1BRG = (PBCLK + fSCL) / (2 * fSCL) - 1;
	I2C1CONbits.ON = 1;

}		
void i2c1_start(void)
{
	
	I2C1CONbits.SEN = 1;
	while(I2C1CONbits.SEN == 1);

}
void i2c1_stop(void)
{
	while((I2C1CON & 0x1F) == !0);
	I2C1CONbits.PEN = 0;
	while(I2C1CONbits.PEN == 0);

}
int i2c1_send(unsigned char value)
{
	
	I2C1TRN = value;
	while(I2C1STATbits.TRSTAT == 0);
	return I2C1STATbits.ACKSTAT;
	
}
char i2c1_receive(char ack_bit)
{
	while((I2C1CON & 0x1F) == !0);
	I2C1CONbits.RCEN = 1;
	while(I2C1STATbits.RBF == 0);
	I2C1CONbits.ACKDT = ack_bit;
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN == 1);
	return I2C1RCV;
	
}
