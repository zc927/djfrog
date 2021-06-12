#include <Keyboard.h>

//hey amber!! heres the basic setups:

#include <U8g2lib.h>
#include <AsyncDelay.h>
#include <Wire.h>
#include "LIS3DHTR.h"
LIS3DHTR<TwoWire> LIS;
#define WIRE Wire
#include "Adafruit_NeoPixel.h"

#define DHTPIN 3
#define DHTTYPE DHT11

AsyncDelay tick;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);

//pop the image files here:

//define frame1:
//define frame2:

//defining variables:

#define screen_width 128
#define screen_height 64
const int fps = 0; //fast as possible b/c sensors make it slow
const int currentFrame = 0;

/*const int display_width = 164;
int current_pos = -display_width;
int move_int = 50; //movement interval
int animate_frame = 0;
float movement = 0.00;*/ //this is like the movement stuff? dont think we need it rn

char button = 6;
char led = 4;
char rotary = A0;
char sound = A2;

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Keyboard.begin();

  tick.start(fps, AsyncDelay::MILLIS);
}

void duckAnimate() {
  u8g2.firstPage();
  do {
    switch (currentFrame) {
      case 0:
        //u8g2.drawXBMP(screen_width / 2,0, screen_width, screen_height, frame1);
        break;
      case 1: 
        //u8g2.drawXBMP(screen_width / 2,0, screen_width, screen_height, frame2);
        break;
    }
  }
  while(u8g2.nextPage());
}

void changeSong()
{
  Keyboard.press(KEY_LEFT_GUI);
  delay(100);
  Keyboard.release();
}

void pulse()
{
  //insert
}

void loop() { 
  // put your main code here, to run repeatedly:
    if (digitalRead(button) == HIGH)
    {
      changeSong();
    }
    if (analogRead(sound) >  300)
    {
      pulse();
    }
    
    duckAnimate();
   
      if (animate_frame == 0)
      {
         animate_frame++;
      }
      else if (animate_frame == 1)
      {
        animate_frame--;
      }
      
    tick.repeat();
}

}
