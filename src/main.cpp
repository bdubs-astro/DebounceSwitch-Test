#include <Arduino.h>
#include "DebounceSwitch.h"

// Switch ...
#define swPin 12                // ! Arduino Nano Every D12
#define intPullup true          // ! use internal pullup resistor?
void loCallback(), hiCallback();
DebounceSwitch mySwitch(swPin, intPullup, loCallback, hiCallback);

// LED ...
// ! Arduino Nano Every: builtin LED on pin 13, active high
#ifndef LED_BUILTIN 
#define LED_BUILTIN 13          
#endif
#ifndef LED_ON
#define LED_ON HIGH      
#endif

#ifndef LED 
#define LED LED_BUILTIN          
#endif

void setup() {
  // establish serial comms ...
  Serial.begin(115200);
  while(!Serial) {;}                // wait for connection
  Serial.println(); Serial.println("Serial monitor connected."); 
  Serial.println();

  // configure indicator LED ...
  pinMode(LED, OUTPUT); 

  // initialize switch ...
  bool swStateInit = mySwitch.initPin(); 
  digitalWrite(LED, swStateInit ? !LED_ON : LED_ON);  // ! NO switch, active low

  const char *swStateStr[] = {"LOW", "HIGH"};
  Serial.print("Initial input state is ");
  Serial.print(swStateStr[swStateInit]);
  Serial.println("."); Serial.println();
}

void loop() {
  int debounceDelay = 100;          // (ms)
  bool swState = mySwitch.readPin(debounceDelay); 
}

// callback functions ...
void loCallback() {
  digitalWrite(LED, LED_ON);
  Serial.println("Input just went LOW."); Serial.println();
}

void hiCallback() {
  digitalWrite(LED, !LED_ON);
  Serial.println("Input just went HIGH."); Serial.println();
}