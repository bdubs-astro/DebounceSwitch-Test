#include <Arduino.h>
#include "DebounceSwitch.h"

// I/O ...
#define swPin 12                // ! Arduino Nano Every D12
#define intPullup true          // ! use internal pullup resistor?
void loCallback(), hiCallback();
DebounceSwitch mySwitch(swPin, intPullup, loCallback, hiCallback);
#ifndef LED_BUILTIN 
#define LED_BUILTIN 13          // ! Arduino Nano Every
#endif

void setup() {
  // establish serial comms ...
  Serial.begin(115200);
  while(!Serial) {;}                // wait for connection
  Serial.println(); Serial.println("Serial monitor connected."); 
  Serial.println();

  // configure indicator LED ...
  pinMode(LED_BUILTIN, OUTPUT); 

  // initialize switch ...
  bool swStateInit = mySwitch.initPin(); 
  digitalWrite(LED_BUILTIN, swStateInit);

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
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Input just went LOW."); Serial.println();
}

void hiCallback() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Input just went HIGH."); Serial.println();
}