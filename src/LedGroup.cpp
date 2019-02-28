
#include "LedGroup.h"

bool Led::state() {
	return digitalRead(_pin)==HIGH;
}
void Led::set(bool state) {
	digitalWrite(_pin, state ? HIGH : LOW);
}



LedGroup::LedGroup(int* pins, int state) {
	_count=0;
	int* p = pins;
	while(*p++!=-1) _count++;
	leds = (Led**)new Led*[_count];
	for (int i=0;i<_count;i++){
		leds[i] = new Led(*pins++);
	}
	setState(state);
}

LedGroup::~LedGroup() {
	for(int i=0;i<_count; i++){
		delete leds[i];
	}
	delete[] leds;
}

void LedGroup::set(int led, bool state) {
	if (checkLed(led)) leds[led]->set(state);
}
bool LedGroup::state(int led) {
	if (checkLed(led)) return leds[led]->state();
	return false;
}

int LedGroup::getState() {
	int st=0;
	for(int i=_count-1; i>=0; i--){
		st <<= 1;
		st |= state(i) ? 1 : 0;
	}
	return st;
}

void LedGroup::setState(int state){
	for(int i=0; i<_count; i++) {
		set(i, state&1);
		state >>= 1;
	}
}