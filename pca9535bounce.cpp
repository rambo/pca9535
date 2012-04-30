#include <Arduino.h>
#include "pca9535bounce.h"


void pca9535bounce::begin(pca9535 *expander, uint8_t pin, unsigned long interval_millis )
{
	interval(interval_millis);
	previous_millis = millis();
	this->device = expander;
	state = this->device->digitalRead(pin);
    this->pin = pin;
}


void pca9535bounce::write(int new_state)
       {
       	this->state = new_state;
       	digitalWrite(pin,state);
       }


void pca9535bounce::interval(unsigned long interval_millis)
{
  this->interval_millis = interval_millis;
  this->rebounce_millis = 0;
}

void pca9535bounce::rebounce(unsigned long interval)
{
	 this->rebounce_millis = interval;
}



int pca9535bounce::update()
{
	if ( debounce() ) {
        rebounce(0);
        return stateChanged = 1;
    }

     // We need to rebounce, so simulate a state change
     
	if ( rebounce_millis && (millis() - previous_millis >= rebounce_millis) ) {
        previous_millis = millis();
		 rebounce(0);
		 return stateChanged = 1;
	}

	return stateChanged = 0;
}


unsigned long pca9535bounce::duration()
{
  return millis() - previous_millis;
}


int pca9535bounce::read()
{
	return (int)state;
}


// Protected: debounces the pin
int pca9535bounce::debounce() {
#ifndef PCA9535_BOUNCE_OPTIMIZEDREADS
	uint8_t newState = this->device->digitalRead(pin);
#else
    uint8_t newState
    byte port = 0;
    if (pin > 7)
    {
        port = 1;
    }
    if (this->device->data[port] & (byte)_BV(pin % 8))
    {
        newState = 1;
    }
#endif

	if (state != newState ) {
  		if (millis() - previous_millis >= interval_millis) {
  			previous_millis = millis();
  			state = newState;
  			return 1;
	}
  }
  
  return 0;
	
}

// The risingEdge method is true for one scan after the de-bounced input goes from off-to-on.
bool  pca9535bounce::risingEdge() { return stateChanged && state; }
// The fallingEdge  method it true for one scan after the de-bounced input goes from on-to-off. 
bool  pca9535bounce::fallingEdge() { return stateChanged && !state; }

