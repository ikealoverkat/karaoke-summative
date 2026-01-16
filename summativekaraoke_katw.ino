/* 
Author: Kat Wang
Date: 1/13/26
Description: karaoke
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"

int labubuSong[] = {};
//2 = half note, 4 = quarter note, 8 = eigth note... etc
int labubuNoteDurations[] = {};
String labubuSongLyrics = "";

int otherSong[] = {};
int otherNoteDurations[] = {};

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("hi"); //lcd debug
  Serial.println("Pick a Song - type 1 for Bags (Clairo) and 2 for Labubu Song:");
}

void loop() {
  if (Serial.available() > 0)
  {
    int userInput = SerialreadStringUntil('\n');
    userInput.trim();
    Serial.println("" + userInput); //prints userInput for debugging
    if (userInput !== 1 && userInput !== 2)
    {
      Serial.println("your input is invalid - try again!");
      Serial.println("Pick a Song - type 1 for Bags (Clairo) and 2 for Labubu Song:");
      return;
    } //send an error message to the user if they didn't input 1 or 2 and then ask them for input again
  }
  
  playSong(labubuSong, labubuNoteDurations, labubuSongLyrics);
}

void playSong(int song, int durations, String lyrics) {
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
