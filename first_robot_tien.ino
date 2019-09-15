//https://surtrtech.com/2018/01/27/how-to-simply-use-ds1302-rtc-module-with-arduino-board-and-lcd-screen/
#include <virtuabotixRTC.h>

#include <DHT.h>
#include <DHT_U.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//conflict with virtuabotixRTC.h and solved by below method
#include <Servo.h>

/*
 * This bug is specific to the 5.4.0-atmel3.6.1-arduino2 version of avr-gcc used by Arduino AVR Boards 1.6.22 and newer. It has been reported here:
https://github.com/arduino/Arduino/issues/7949

Here's the workaround:
Tools > Board > Boards Manager
Wait for downloads to finish.
When you move the mouse pointer over "Arduino AVR Boards", you will see a "Select version" dropdown menu appear. Select "1.6.21".
Click "Install".
Wait for installation to finish.
Click "Close" -> restart IDE and disconnect, reconnect the board

Due to a bug, this workaround doesn't work with Arduino IDE 1.8.6, but it will work with any other version of the Arduino IDE.

If you have File > Preferences > Check for updates on startup checked, turn it off
the Arduino IDE may occasionally notify you that a new version of Arduino AVR Boards is available, 
you'll need to refrain from updating back to the new Arduino AVR Boards version, 
otherwise you'll be back to seeing the segmentation fault error again.
 */
