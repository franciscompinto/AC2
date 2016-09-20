#include <detpic32.h>

 #define I2C_READ 1
 #define I2C_WRITE 0
 #define I2C_ACK 0
 #define I2C_NACK 1
 #define ADDR_WR ((SENS_ADDRESS << 1) | I2C_WRITE)
 #define ADDR_RD ((SENS_ADDRESS << 1) | I2C_READ)
 #define SENS_ADDRESS 0x4D // device dependent
 #define TC74_CLK_FREQ 100000 // 100 KHz
 #define RTR 0 // Read temperature command

void i2c1_init(unsigned int clock_freq);
void i2c1_start(void);
void i2c1_stop(void);
int i2c1_send(unsigned char value);
void delay(unsigned int n_intervals):


 int main(void)
 {
 	int ack, temperature;
 	i2c1_init(TC74_CLK_FREQ);
 	while(1)
	 {
	 	i2c1_start();// Send Start event
	 	i2c1_send(ADDR_WR);// Send Address + WR (ADDR_WR); copy return value to "ack" variable
		i2c1_send(ADDR_RD); // Send Command (RTR); add return value to "ack" variable
	 	i2c1_start();// Send Start event (again)
	 	i2c1_send(ADDR_RD); // Send Address + RD (ADDR_RD); add return value to "ack" variable
	 // Test "ack" variable; if "ack" != 0 then an error has occurred;
	 // send the Stop event, print an error message and exit loop
	 	// Receive a value from slave (send NACK as argument); copy
	 	i2c1_receive(I2C_ACK)// received value to "temperature" variable
	 	 i2c1_stop();// Send Stop event
	 	printInt10(temperature, 10);// Print "temperature" variable (syscall printInt10)
	 	delay(250);// Wait 250 ms
 	}
 } 
void i2c1_init(unsigned int clock_freq)
{
	I2C1BRG = (PBCLK + clock_freq) / (2 * clock_freq) - 1;
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
void delay(unsigned int n_intervals)
{
	volatile unsigned int i;
	for(; n_intervals != 0; n_intervals--)
		for(i = 5000; i != 0; i--)
		;
	;
}
