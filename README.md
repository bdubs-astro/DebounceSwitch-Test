<h1> DebounceSwitch </h1>

__A c++ class for de-bouncing a mechanical switch.__

- The parameters are:
  1. a GPIO pin #
  2. a flag that's true if using an internal pullup resistor
  3. a pair of callback functions that get called when the input pin goes either high or low
  4. a debounce delay in milliseconds

- The ```initPin()``` member function must be called first. It configures the input pin, and returns the inital state of 
the switch.

- The ```readPin(debounceDelay)``` member function returns the current state (de-bounced), and calls 
the corresponding callback function whenever the pin's state changes.

<h2> Sample Code:</h2>

```
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
  int debounceDelay = 100;        // (ms)
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
```

<h2> Digital Inputs: Pullup vs. Pulldown Resistors </h2>

<img src = "./images for README/NO switch active LOW.png" height = "400"/>  <img src = "./images for README/NO switch active HIGH.png" height = "400"/>

<img src = "./images for README/NC switch active LOW.png" height = "400"/>  <img src = "./images for README/NC switch active HIGH.png" height = "400"/>  


<h2>ESP8266 D1 Mini Pinout</h2>

<img src = "./images for README/WeMos D1 mini pinout.png" width = "800"/>

Source: https://www.mischianti.org/2021/04/26/wemos-d1-mini-high-resolution-pinout-and-specs/

<img src = "./images for README/WeMos D1 mini pins table.png" width = "600"/>

Source: https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/


<h2>ESP32 Dev Kit C v4 Pinout</h2>

<img src = "./images for README/ESP32 pinout.png" width = "700"/>

Source: https://forum.fritzing.org/t/esp32s-hiletgo-dev-boad-with-pinout-template/5357

<img src = "./images for README/ESP32 LOLIN pinout.png" width="800"/>

Source: https://www.mischianti.org/2021/07/17/esp32-devkitc-v4-high-resolution-pinout-and-specs/


<h2>Arduino Nano Every Pinout</h2>

<img src = "./images for README/Arduino Nano Every pinout.png" width="800"/>

Source: https://docs.arduino.cc/hardware/nano-every/