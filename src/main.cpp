#include <Arduino.h>
#include "DebounceSwitch.h"

#define DEVICE 0    // ! Arduino Nano Every = 0, ESP8266 = 1

// I/O ...
#if DEVICE == 0
// ? Arduino Nano Every
#define LED_BUILTIN 13          // ? built in LED on pin 13     
#define LED_ON HIGH             // ? active high
#define swPin 12                // ? Arduino Nano Every D12
#define intPullup true          // ? use internal pullup resistor?
#elif DEVICE == 1
// ? ESP8266
#define LED_BUILTIN 2           // ? built in LED on pin 2  
#define LED_ON LOW              // ? active low
#define swPin 13                // ? ESP8266 D7
#define intPullup false         // ? use internal pullup resistor?
#endif

#ifndef LED 
#define LED LED_BUILTIN          
#endif

// configure switch ...
void loCallback(), hiCallback();
DebounceSwitch mySwitch(swPin, intPullup, loCallback, hiCallback);

void setup() {
  // establish serial comms ...
  Serial.begin(115200);
  while(!Serial) {;}                // wait for connection
  delay(3000);                      // settling time
  Serial.println(); Serial.println("Serial monitor connected."); 
  Serial.println();

  // configure indicator LED ...
  pinMode(LED, OUTPUT); 

  // initialize switch ...
  bool swStateInit = mySwitch.initPin(); 
  digitalWrite(LED, swStateInit ? !LED_ON : LED_ON);  // ! active low

  const char *swStateStr[] = {"LOW", "HIGH"};
  Serial.print("Initial input state is ");
  Serial.print(swStateStr[swStateInit]);
  Serial.println("."); Serial.println();
}

void loop() {
  int debounceDelay = 50;           // (ms)
  mySwitch.readPin(debounceDelay); 
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