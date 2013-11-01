


#include <Time.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

/*********************************************************************
this is the sketch to display the serial GPS stream from the Adafruit GPS breakout 
on a SSD1306 OLED display using the Arduino Nano.  for questions or comments please 
contact me at http://google.com/+jameswolf
*********************************************************************/



//11,12,10,9,13

// arduino nano pins
#define OLED_DC 9
#define OLED_CS 12
#define OLED_CLK 13
#define OLED_MOSI 11
#define OLED_RESET 10


Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


String content = "";
char character;
int count = 0;
int pageRefreshRemaining = 147;



void setup()   {                
  Serial.begin(9600);

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
  display.println("nano started");
  
  display.display();
  
  delay(3000);
}


void loop() {
  count++;
  display.setTextSize(1);
  display.setTextColor(WHITE);
   
  content = "";
  while(Serial.available()) {
      character = Serial.read();
      content.concat(character);
      pageRefreshRemaining--;
  }

  if (content != "") {
    if(pageRefreshRemaining<0){
      display.clearDisplay();
      display.setCursor(0,0);
      pageRefreshRemaining = 147;
    }
    
    // text display tests
    display.print(content);
    //display.println("length: " + content.length());
  
    display.display();
    //delay(200);
  }
  
 // delay(200);
}


/*
String digitalClockDisplay(){
  String display_text = "" + printDigits(minute()) + ":" + printDigits(second());
  return(display_text);
}

String printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  String val = "";
  if(digits < 10)
    val = val + '0';
  val = val + digits;
  
  return(val);
}
*/
