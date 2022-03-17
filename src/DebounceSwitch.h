/*
DebounceSwitch - a class for de-bouncing a mechanical switch

The parameters are the GPIO pin #, a flag that's true if using an internal pullup 
resistor, a pair of callback functions that get called when the pin goes either high 
or low, and a debounce delay in ms. 

The initPin() command configures the input pin, and returns the inital state of 
the switch. It must be called first.

The readPin() command returns the current state (de-bounced), and calls 
the corresponding callback function whenever the state changes.

Visit https://github.com/bdubs-astro/DebounceSwitch for more details.

*/

#ifndef DebounceSwitch_h
#define DebounceSwitch_h

#include "Arduino.h"

class DebounceSwitch {

public:
  DebounceSwitch(const int _pin, bool _intPullup, void (*_loCallback)(void), void (*_hiCallback)(void)):
    intPullup(_intPullup), pin(_pin), loCallback(_loCallback), hiCallback(_hiCallback) {
    
    // configure input pin
    if (intPullup)
      pinMode(pin, INPUT_PULLUP);     // use internal pullup resistor 
    else
      pinMode(pin, INPUT);    
  }

  bool initPin();    
  bool readPin(int debounceDelay); 
    
private:
  bool intPullup;
  int pin;
  void (*loCallback)(void);
  void (*hiCallback)(void);
  bool reading;
  bool currState;                       
  bool prevState;  
  unsigned long timePrev;                  
};

#endif
