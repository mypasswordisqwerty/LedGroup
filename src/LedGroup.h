#ifndef _LedGroup_h
#define _LedGRoup_h

#include <Arduino.h>

class Led {
public:
	Led(int pin) : _pin(pin){ pinMode(pin, OUTPUT); off(); }
	~Led() {};
	void set(bool state);
	bool state();
	void on() {set(true);};
	void off() {set(false);};
	void change() {set(!state());};
private:
	int _pin;
};


class LedGroup {
public:
	LedGroup(int* pins, int state=0);
	~LedGroup();
	void setState(int state);
	int getState();
	void set(int led, bool state);
	bool state(int led);
	void on(int led) {set(led, true);};
	void off(int led){set(led, false);};
	void change(int led){set(led, !state(led));};
private:
	bool checkLed(int led){return led<_count;}
	Led** leds;
	int _count;
};


#endif

