#include "ic74hc595.h"
#include "Arduino.h"

void ic74hc595::ic74hc595Init() {
	pinMode(latch_pin, OUTPUT);
	pinMode(clock_pin, OUTPUT);
	pinMode(data_pin, OUTPUT);
}

void ic74hc595::setLength(int length) {
	this->length = length;
	this->loic = (length % 8) ? ((length / 8) + 1) : (length / 8);
	this->led = malloc(this->loic * sizeof(int));
}

void ic74hc595::resetLED() {
	for (int i = 0; i < this->loic; i++) {
		*(this->led + i) = 0b00000000;
	}
}

bool ic74hc595::writeLED(int nums_led) {
	if (nums_led > this->length) {
		return false;
	} else {
		digitalWrite(this->latch_pin, LOW);

		int temp = (nums_led / 8);
		int t = nums_led % 8;
		for (int i = 0; i < temp; i++) {
			*(this->led + i) = 0b11111111;
		}
		if (t) {
			for (int i = 0; i < t; i++) {
				*(this->led + temp) = (*(this->led + temp) << 1) | 1;
			}
		}

		for (int i = this->loic - 1; i >= 0; i--) {
			shiftOut(this->data_pin, this->clock_pin, MSBFIRST, *(this->led + i));
		}

		digitalWrite(this->latch_pin, HIGH);
	}
	this->resetLED();
	return true;
}