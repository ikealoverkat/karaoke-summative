/* 
Author: Kat Wang
Date: 1/13/26
Description: karaoke
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

int labubuSong[] = {}

// int otherSong[] = {}

//2 = half note, 4 = quarter note, 8 = eigth note... etc
int labubuNoteDurations[] = {} 



LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("hi"); //lcd debug
}

void loop() {
  playSong(labubuSong, labubuNoteDurations);
}

void playSong(int song, int durations) {
  bool isPlayingNote = false;
  int thisNote = 0;
  int noteDuration = 0;
  unsigned long noteStartTime = 0;

  //play the notes of the song
  unsigned long currentTime = millis();
  int totalNotes = song.size();

  if (thisNote < totalNotes)
    {
      if (!isPlayingNote)
      {
        noteDuration = 1000/durations[thisNote];
        tone(6, song[thisNote], noteDuration);

        noteStartTime = currentTime;
        isPlayingNote = true;
      }
      else
      {
        unsigned long pauseBetweenNotes = noteDuration * 1.30;

        if (currentTime - noteStartTime >= pauseBetweenNotes)
        {
          thisNote++;
          isPlayingNote = false;
        }
      }
    }
}
