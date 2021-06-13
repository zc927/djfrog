#include <Wire.h>
#include <AsyncDelay.h>

#include <U8g2lib.h>
#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIXEL_PIN 6
#define PIXEL_COUNT 24
#define BUTTON_PIN 2

#include "grove_two_rgb_led_matrix.h"
 
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif

int currentFrame = 0;
const int fps = 200;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, 7, NEO_GRB + NEO_KHZ800);
GroveTwoRGBLedMatrixClass matrix;
AsyncDelay tick;

static const uint64_t ledFrog[] = {
 
  0x5555ffffff555555,
  0x55ff55555555ff55,
  0xecec55fbfb55ecec,
  0xecec55555555ecec,
  0x5555555555555555,
  0x5555552a2a555555,
  0xff552a2a2a2a55ff,
  0xffff2a2a2a2affff,
 
  0xffffffffffffffff,
  0x5555ffffff555555,
  0x55ff55555555ff55,
  0xecec55fbfb55ecec,
  0xecec55555555ecec,
  0x5555555555555555,
  0x5555552a2a555555,
  0xff552a2a2a2a55ff,
 
  0xffffffffffffffff,
  0xffffffffffffffff,
  0x5555ffffff555555,
  0x55ff55555555ff55,
  0xecec55fbfb55ecec,
  0xecec55555555ecec,
  0x5555555555555555,
  0x5555552a2a555555,
 
  0xffffffffffffffff,
  0x5555ffffff555555,
  0x55ff55555555ff55,
  0xecec55fbfb55ecec,
  0xecec55555555ecec,
  0x5555555555555555,
  0x5555552a2a555555,
  0xff552a2a2a2a55ff
};

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.setBrightness(255);
  strip.begin();

  tick.start(fps, AsyncDelay::MILLIS);

  //----------------------------------
  Wire.begin();

  //WRITE
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0,10,"yooooooo suck it green boyyy");
  u8g2.sendBuffer();

  //rainbowCycle(50);
  //colorWipe(strip.Color(0, 0, 0), 50);
  //colorWipe(strip.Color(255, 0 ,151), 10);
}


void loop() {
  // put your main code here, to run repeatedly:

  for(uint16_t i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, (255, 0 ,151));
    strip.show();
    delay(1000);
  }
  
  //pulse(strip.Color(255, 0 ,0), 10); //magenta
  //pulse(strip.Color(0, 255 ,255), 10); //aqua
  //pulse(strip.Color(30, 0 ,255), 10); //blue
  //pulse(strip.Color(255, 0 ,151), 10); //pink


  //LED ANIMATE
    
    if (tick.isExpired())
    {
      if (currentFrame == 3)
        {
            matrix.displayFrames(ledFrog+currentFrame*8, 200, false, 1);
           currentFrame = 0;
        }
       else
        {
          matrix.displayFrames(ledFrog+currentFrame*8, 200, false, 1);
          currentFrame++;
        }
      tick.repeat();
    }
}


void pulse(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+2) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();
      
      /*delay(wait);
 
      for (int i=0; i < strip.numPixels(); i=i+2) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }*/
    }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    //delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
