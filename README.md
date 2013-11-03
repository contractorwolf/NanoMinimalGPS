NanoMinimalGPS
==============

Arduino Nano with Adafruit GPS breakout and OLED SSD1306 screen


  This is the sketch to display the serial GPS data stream from the Adafruit GPS breakout 
  on a SSD1306 OLED display using the Arduino Nano. Connect the components like this:
  
  WIRING 
  ------------------------------
  Nano.pin9  -> OLED.dc
  Nano.pin10 -> OLED.res
  Nano.pin11 -> OLED.data
  Nano.pin12 -> OLED.cs
  Nano.pin13 -> OLED.clk
  
  Nano.tx - > GPS.rx
  Nano.rx - > GPS.tx
  ------------------------------
  
  For questions or comments please contact me at http://google.com/+jameswolf
