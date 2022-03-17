<h1> DebounceSwitch </h1>

__A c++ class for de-bouncing a mechanical switch.__

- The required parameters are:
  - the GPIO input pin #
  - a flag that's true if using an internal pullup resistor, or false otherwise
  - a pair of callback functions that get called when the input pin goes either  low or high
  - a debounce delay in milliseconds

- The ```initPin()``` member function must be called first. It configures the input pin, and returns the inital state of 
the switch.

- The ```readPin(debounceDelay)``` member function returns the current state (de-bounced), and calls 
the appropriate callback function whenever the pin's state changes.

 <!--- <h2> Sample Code:</h2> --->

```
#include "DebounceSwitch.h"

#define swPin 12                
#define intPullup true          // ! use internal pullup resistor?

void loCallback(), hiCallback();
DebounceSwitch mySwitch(swPin, intPullup, loCallback, hiCallback);

void setup() {
.
.
. 
  bool swStateInit = mySwitch.initPin();  // initialize switch
}

void loop() {
  int debounceDelay = 50;       // (ms)
  bool swState = mySwitch.readPin(debounceDelay); 
}

void loCallback() {
  Serial.println("Input just went LOW.");
}

void hiCallback() {
  Serial.println("Input just went HIGH.");
}
```
Included is an example Platform IO project. You can choose between platforms using a single pre-processor statement. Be sure to select the correct environment before compiling - see the screenshots below.

```
[env:nano_every]
platform = atmelmegaavr
board = nano_every
framework = arduino
monitor_speed = 115200

[env:esp12e]
platform = espressif8266
board = esp12e
framework = arduino
monitor_speed = 115200
```

<img src = "./images for README/nano environment.png" width = "600"/> 

<img src = "./images for README/esp environment.png" width = "600"/> 

<h2> Digital Inputs: Pullup vs. Pulldown Resistors </h2>

<img src = "./images for README/NO switch.png" width = "600"/> 

<img src = "./images for README/NC switch.png" width = "600"/> 


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