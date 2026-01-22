# ESPGauge
ESP32 Round gauge for your Dream Car.

## ESP32 board setup

Custom PCB with ESP32-S2 chip with native UART. 

Arduino Framework board - **Adafruit Feather ESP32-S2**. 

## Arduino Library 

* Arduino IDE 2.3.7
* esp32 by Espressif Systems version 3.3.5
* TFT_eSPI by Bodmer 2.5.43
* lvgl by kisvegabor 8.3.11 (**version compatible with SquareLine Studio**)

### Library versioning 

Library versions are handled by git submodules.

```bash
git submodule update --init --recursive
```

### Library config files 

* **lv_conf.h** is in the right place - nothing to do. 
* **User_Setup.h** config file needs to be move to TFT_eSPI folder when submodule update is finished 

