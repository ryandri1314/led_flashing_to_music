#ifndef _IC_74HC595_H_ 
#define _IC_74HC595_H_

#define LOW 0
#define HIGH 1
#define MSBFIRST 1
	
class ic74hc595 
{
private:
	int latch_pin;
	int clock_pin;
	int data_pin;
	int length;
	int loic;
	int* led;
public:
	ic74hc595(int latch_pin, int clock_pin, int data_pin) {
		this->latch_pin = latch_pin;
		this->clock_pin = clock_pin;
		this->data_pin = data_pin;
		this->led = 0b00000000;
	}
	void ic74hc595Init();
	void setLength(int length);
	bool writeLED(int nums_led);
	void resetLED();
};

#endif