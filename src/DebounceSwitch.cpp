#include "DebounceSwitch.h"

bool DebounceSwitch::initPin() {
  reading = digitalRead(pin);
  prevState = reading;              
  currState = reading;
  timePrev = millis();
  return reading;                   // return the current state
}

bool DebounceSwitch::readPin(int debounceDelay) { 
  reading = digitalRead(pin);     

  if ( reading != prevState ) 
    timePrev = millis();           	// start the timer

  if ( labs(millis() - timePrev) > long(debounceDelay) ) {    // allow to settle
    if (reading != currState) {
      currState = reading;          // update the current state
      if (currState)
	hiCallback(); 
      else
	loCallback();
    }  
  }
  
  prevState = reading;              // update the previous state 
  return currState;                 // return the current state (de-bounced)
}
