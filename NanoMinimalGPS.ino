#include <Time.h>
#include <Wire.h>
#include <SoftwareSerial.h>

//FOLLOWING LIBRARIES MUST BE INSTALLED IN THE arduino/libraries folder
#include <Adafruit_GFX.h>      //https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h>  //https://github.com/adafruit/Adafruit_SSD1306
#include <Adafruit_GPS.h>      //https://github.com/adafruit/Adafruit-GPS-Library

/*
********************************************************************
  This is the sketch to display the serial GPS data stream from the Adafruit GPS breakout 
  on a SSD1306 OLED display using the Arduino Nano. Connect the components like this:
  
  WIRING 
  ------------------------------
  Nano.pin9  -> OLED.dc
  Nano.pin10 -> OLED.res
  Nano.pin11 -> OLED.din
  Nano.pin12 -> OLED.ss
  Nano.pin13 -> OLED.clk
  
  Nano.tx - > GPS.rx
  Nano.rx - > GPS.tx
  ------------------------------
  
  For questions or comments please contact me at http://google.com/+jameswolf
 
  SEEN IN STREAM
  $GPGGA - Global Positioning System Fix Data
  $GPVTG - Track made good and ground speed
  $GPGSA - GPS DOP and active satellites 
  $GPGSV - GPS Satellites in view
  $GPRMC - Recommended minimum specific GPS/Transit data
      
  //OTHER POTENTIAL SENTENCES
  http://aprs.gids.nl/nmea/#gga
  
********************************************************************
*/

// arduino nano pins for the OLED
#define OLED_DC 9
#define OLED_CS 12
#define OLED_CLK 13
#define OLED_MOSI 11
#define OLED_RESET 10

//start display communication
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


String content = "";
char character;
int count = 0;
int display_count = 0;

bool listen = false;
String marker = "";

//setup: start screen and gps serial communication
void setup()   {                
  Serial.begin(9600);//for gps tx and rx
  //GPS.tx - > Nano.rx
  //GPS.rx - > Nano.tx
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
 
  // init done
  display.clearDisplay();
  
  // text display tests
  display.setCursor(0,0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("MINIMALGPS");
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Nano Started: v1.3");
  display.println(" ");    
  display.println("time, position, data");
  display.display();
  
  delay(3000);
}

//loop executes continously, grabs serial gps data and combines the incoming characters to make the GPS sentences
//if it sees the GPGGA sentence it grabs the data from the sentence that is the time and position data as well as
//the number of satellites
void loop() {
  count++;
  
  while(Serial.available()) {
      character = Serial.read();
      
      if(character=='$'){
        //start of gps sentence marker
        content = "";
        listen = true; 
      }else if(character=='*'){
        //end of gps sentence marker 
        listen = false; 
        
        //show just GPGGA sentence because it contains all of the data we need
        if(content.substring(0,6)=="$GPGGA"){
          display.clearDisplay();
          display.setCursor(0,0);
          
          display.setTextSize(2);
          display.setTextColor(WHITE);
          
          // show time
          display.print(" ");          
          display.print(content.substring(7,9));
          display.print(":");
          display.print(content.substring(9,11));  
          display.print(":");         
          display.println(content.substring(11,13));         
        
          //smaller, to fit position data
          display.setTextSize(1);
          display.setTextColor(WHITE);
          
          //space between
          display.println(" ");   
          
          // show NS position 
 
 
          display.print("     ");   
          display.print(content.substring(18,27));
          display.println(content.substring(28,29));         
         
          // show EW position  
          display.print("     ");             
          display.print(content.substring(31,40));          
          display.println(content.substring(41,42));      
               
                    
          display.setTextSize(1);
          display.setTextColor(WHITE);
          
          //show other data
          display.println(content);           
          
          display.display();
        }
        
        /*
        SHOWS LIST OF ALL SENTENCES
        if(display_count%8==0){
          display.clearDisplay();
          display.setCursor(0,0);
        }
        // text display tests
        display.println(content.substring(0,20));
        display.display();
        display_count++;
        */
       
        content = "";
      }
      
      if(listen){
        content.concat(character);
      }
  }

 // delay(200);
}


