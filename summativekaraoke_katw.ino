/* 
Author: Kat Wang
Date: 1/13/26
Description: karaoke
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include "constants.h"

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // lcd.init();
  // lcd.backlight();
  // lcd.clear();
  // lcd.setCursor(0,0);
  // lcd.print("hi"); //lcd debug
  Serial.begin(9600);
  Serial.println("Pick a Song - type 1 for Labubu Song and 2 for Bags (Clairo):");
}

void loop() {
  if (Serial.available() > 0)
  {
    String userInput = Serial.readStringUntil('\n');
    userInput.trim();    
    int userInputInt = userInput.toInt();
    Serial.println(userInputInt); //prints userInput for debugging
    
    if (userInputInt != 1 && userInputInt != 2)
    {
      Serial.println("your input is invalid - try again!");
      Serial.println("Pick a Song - type 1 for Labubu Song and 2 for Bags (Clairo):");
      return;
    } //send an error message to the user if they didn't input 1 or 2 and then ask them for input again

    if (userInputInt == 1) //play the labubu song when user inputs 1
    {
      playSong(labubuSongNotes, labubuSongNoteDurations, labubuSongLyrics, totalLabubuSongNotes);
      return;
    }

    if (userInputInt == 2) //play Bags when user inputs 2
    {
      playSong(bagsNotes, bagsNoteDurations, bagsLyrics, totalBagsNotes);
      return;
    }
  }
}

void playSong(int song[], int durations[], String lyrics[], int totalNotes) {
  unsigned long currentTime = millis();
  bool isPlayingNote = false;
  int noteDuration = 0;
  unsigned long noteStartTime = 0;
  int currentNote = 0;

  //play the notes of the songs
  while (currentNote < totalNotes) {
    currentTime = millis(); //update time
    if (!isPlayingNote) 
    {
      noteDuration = 1000/durations[currentNote];
      tone(BUZZER_PIN, song[currentNote], noteDuration);
      noteStartTime = currentTime; //record time the note started playing
      isPlayingNote = true;
    } //if a note isn't currently playing, continues
    else
      {
        unsigned long pauseBetweenNotes = noteDuration * 1.30; //declare pause time between notes - 30% of the note duration
        if (currentTime - noteStartTime >= pauseBetweenNotes) //if the pause is finished, continue
        {
          currentNote++;
          isPlayingNote = false;
        }
      }

  }
}
