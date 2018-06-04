#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

//compile cmd: gcc -o demo gpio_demo.c -lwiringPi -lpthread

int main (void)
{
	int ret = 0;
  	if (wiringPiSetup () == -1){
		printf("fail to wringPi set up.\n");
    	return 1;
	}
 
	//hardware pwm
	pinMode(1, OUTPUT);
	pwmWrite(1, 512); //The Raspberry Pi has one on-board PWM pin, pin 1 (BMC_GPIO 18, Phys 12) and the range is 0-1024

	//software pwm
	int pinL = 21;	
	int pinR = 23;
	pinMode(pinL, OUTPUT);      
	pinMode(pinR, OUTPUT);
	ret = softPwmCreate(pinL, 20, 100);  //int softPwmCreate (int pin, int initialValue, int pwmRange);
	if (ret != 0){
		printf("fail to softPwmCreate, pin num is %d, ret is %d\n", pinL, ret);
		return ret;
	}
	ret = softPwmCreate(pinR, 20, 100);
	if (ret != 0){
		printf("fail to softPwmCreate, pin num is %d, ret is %d\n", pinR, ret);
		return ret;
	}

	delay(10*1000);
	softPwmWrite(pinL, 50);
	softPwmWrite(pinR, 50);

	delay(20 * 1000);
	
	return 0 ;
}
