#include <SFEMP3ShieldConfig.h>
#include <SFEMP3Shield.h>
#include <SFEMP3Shieldmainpage.h>



#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include "LedControl.h"

//LCD pins
#define DIN 42
#define CS 44
#define CLK 46

#define MOTION_PIR_SENSOR 36

#define NUMBER_OF_TRACKS 9

SdFat sd;
SFEMP3Shield MP3player;

LedControl lc = LedControl(DIN,CLK,CS,0);

void setup() {
  if (!sd.begin(SD_SEL, SPI_HALF_SPEED)) 
  {
    sd.initErrorHalt(); 
  }

  MP3player.begin();
  MP3player.setBitRate(192);
  MP3player.setVolume(22,22); 
  
  //lcdSetup();

  //byte smile[8] = {0x00,0x66,0x66,0x00,0x00,0x42,0x3C,0x00};
  //printByte(smile);
}


void lcdSetup()
{
  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,15);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
}


void loop() {
  motionPirCheck();
  delay(500);
}

void motionPirCheck()
{
  if (digitalRead(MOTION_PIR_SENSOR) == 1)
  {
    MP3player.playTrack(random(1, NUMBER_OF_TRACKS + 1));
    delay(50);
    
    while (MP3player.isPlaying() == 1)
    {
      delay(50);
    }

    delay(5000);
  }
}


void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
  
}


