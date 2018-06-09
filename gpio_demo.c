#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

//compile cmd: gcc -o demo gpio_demo.c -lwiringPi -lpthread
int initialization(void)
{
	int ret = 0;
	if(wiringPiSetup() == -1){
		printf("fail to wringPi set up.\n");
		return 1;
	}
	
	//software pwm
	int pinL = 21;
	int pinR = 23;
	
	pinMode(pinL, OUTPUT);
	pinMode(pinR, OUTPUT);
	
	ret = softPwmCreate(pinL,0,100);
	delay(1000);
	if(0!=ret){
		printf("fail to create L pwm!\n");
		return ret;
	}
	ret = softPwmCreate(pinR,0,100);
	if(0!=ret){
		printf("fail to create R pwm!\n");
		return ret;
	}
	delay(1000);
	printf("initialization!\n");
	return ret;
}
int test_pwm (void)
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
	ret = softPwmCreate(pinL, 0, 100);  //int softPwmCreate (int pin, int initialValue, int pwmRange);
	if (ret != 0){
		printf("fail to softPwmCreate, pin num is %d, ret is %d\n", pinL, ret);
		return ret;
	}
	ret = softPwmCreate(pinR, 0, 100);
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

void test_encoder()
{
	int ret = 0;
  	if (wiringPiSetup () == -1){
		printf("fail to wringPi set up.\n");
    	return; 
	}

	int lh_pin = 26;
	int ll_pin = 29;
	int rh_pin = 28;
	int rl_pin = 27;

	pinMode(lh_pin, INPUT);
	pinMode(ll_pin, INPUT);
	pinMode(rh_pin, INPUT);
	pinMode(rl_pin, INPUT);

	int count = 0;
	do {
		int lh = digitalRead(lh_pin);
		int ll = digitalRead(ll_pin);
		int rh = digitalRead(rh_pin);
		int rl = digitalRead(rl_pin);
		printf("%d, %d, %d, %d\n", lh, ll, rh, rl);
		delay(10);
		count++;
	} while(count <= 1000);
}


void reset()
{
	
}

int main()
{
	int ret = 0;
//	ret = initialization();
	test_pwm();
	test_encoder();
}
