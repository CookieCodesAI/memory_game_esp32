# ESP32 Memory Game
A memory game created with an **ESP32** and **MPR121** in the **Arduino IDE** with ``C++``
<img src = "images/IMG_4273.png" alt = "Circuit Image" width = "350" />
## Materials Needed
- 6 LEDs
    - 1 Blue
    - 2 Green
    - 1 Yellow
    - 2 Red
- 6 220Ω Resistors
- 1 MPR121
- 1 ESP32
- Lots of Jumper Wires
- Aluminum Foil or Copper Foil Tape (for touchpads connected to MPR121)

## Features
- Uses **MPR121** for interactive touch detection
- **LEDs** for aesthetic feedback
- Touch feedback **spam prevention**
- Random sequences with ``<random>`` and ``<vector>``

## How to Use

### #1 Install Arduino IDE
> Download the IDE with this link:
> https://www.arduino.cc/en/software/

### #2 Install necessary Board Support for ESP32
> In the IDE, open **Files > Preferences > Additional Board Manager URLs** and paste this link:
> https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

### #3 Install Dependencies
> **Library Manager > Search Adafruit MPR121 > Install**

### #4 Clone this Repository
````{bash} 
git clone https://github.com/CookieCodesAI/memory_game_esp32.git
````

### #5 Open the memory_game.ino file in Arduino IDE 
### #6 Choose ESP32 board and port
> - **Tools > Board > Choose Board**
> - **Tools > Port > Choose Port**

### #7 Upload the Code
> Click the **Upload** button to upload code to **ESP32**

## Additional Things
- Based on the sensitivity, users may have to adjust the threshold of the MPR121. Update this line of code based on the sensitivity of MPR121:
````{C++}
cap.setThresholds(0, 0); 
````

## Resources Used
- Arduino IDE — https://www.arduino.cc/en/software/
- Arduino-ESP32 Core by Espressif — https://github.com/espressif/arduino-esp32
- Adafruit MPR121 Library — https://github.com/adafruit/Adafruit_MPR121

*Setup instructions were based on Arduino IDE, Espressif, and Adafruit MPR121*
