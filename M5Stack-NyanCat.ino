/*
 * 
 
  M5Stack NyanCat

  Copyright 2018 tobozo http://github.com/tobozo
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
 
 *
 */

#include <M5Stack.h>             // https://github.com/m5stack/M5Stack/
#include "M5StackUpdater.h"      // https://github.com/tobozo/M5Stack-SD-Updater

#include "Game_Audio.h" // from http://www.buildlog.net/blog/2018/02/game-audio-for-the-esp32/

#include "nyan-audio.h"
#include "nyan-video.h"

Game_Audio_Class GameAudio(25,0);
Game_Audio_Wav_Class pmNyan(nyan_loop_aiff); 
Game_Audio_Wav_Class pmWav(pmNyan);

long count = 0; // Loop count
int iconpointer = 0;
int totalframes = 11;
long duration = 90;
long last = 0;

void animloop() {
  long now = millis();
  if(duration + last < now) {
    last = now;
    switch(iconpointer) {
      case 0:  M5.Lcd.drawJpg(nyan01_jpg, nyan01_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 1:  M5.Lcd.drawJpg(nyan02_jpg, nyan02_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 2:  M5.Lcd.drawJpg(nyan03_jpg, nyan03_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 3:  M5.Lcd.drawJpg(nyan04_jpg, nyan04_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 4:  M5.Lcd.drawJpg(nyan05_jpg, nyan05_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 5:  M5.Lcd.drawJpg(nyan06_jpg, nyan06_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 6:  M5.Lcd.drawJpg(nyan07_jpg, nyan07_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 7:  M5.Lcd.drawJpg(nyan08_jpg, nyan08_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 8:  M5.Lcd.drawJpg(nyan09_jpg, nyan09_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 9:  M5.Lcd.drawJpg(nyan10_jpg, nyan10_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 10: M5.Lcd.drawJpg(nyan11_jpg, nyan11_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
      case 11: M5.Lcd.drawJpg(nyan00_jpg, nyan00_jpg_len, 80, 60, 160, 120, 0, 0,  JPEG_DIV_NONE); break;
    }
    iconpointer++;
    if(iconpointer>totalframes-1) iconpointer = 0;
  }
}


void setup() {
  Serial.begin(115200); 
  Serial.println("Begin...");
  M5.begin();
  Wire.begin();
  if(digitalRead(BUTTON_A_PIN) == 0) {
    Serial.println("Will Load menu binary");
    updateFromFS(SD,"/menu.bin");
    ESP.restart();
  }
  delay(2000);
  Serial.println("Will load mp3");
  delay(2000);
  
  M5.Lcd.setBrightness(100);
  M5.Lcd.fillScreen(BLACK);
  
}

void loop() {

  M5.update();
  GameAudio.PlayWav(&pmWav, false, 1.0);
  while(GameAudio.IsPlaying()) { 
    animloop();
  }
  
}


