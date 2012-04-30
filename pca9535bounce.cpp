#include "pca9535bounce.h"

// Override this...
Bounce::Bounce(uint8_t pin,unsigned long interval_millis)
{
}

void pca9535bounce::init(pca9535 *expander, uint8_t pin,unsigned long interval_millis)
{
	interval(interval_millis);
	previous_millis = millis();
	this->device = expander;
	state = this->expander->digitalRead(pin);
    this->pin = pin;
}
