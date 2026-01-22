#include <analogWave.h> //r4 has a built in DAC on pin A0! I am free from tone()!!!
analogWave instrumentalPlayer(DAC);
/* 
Author: Kat Wang
Date: 1/20/26
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
  delay(1000);
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
      // playSong(labubuSongNotes, labubuSongNoteDurations, labubuSongLyrics, totalLabubuSongNotes);
      Serial.println("Pick a Song - type 1 for Labubu Song and 2 for Bags (Clairo):");
      return;
    } else if (userInputInt == 2) //play Bags when user inputs 2
    {
      // playSongOld(bagsInstrumentalNotes, bagsInstrumentalDurations, bagsInstrumentalTotalNotes);
      playSong(bagsNotes, bagsNoteDurations, bagsLyrics, totalBagsNotes, bagsInstrumentalNotes, bagsInstrumentalDurations, totalBagsInstrumentalNotes);
      Serial.println("Pick a Song - type 1 for Labubu Song and 2 for Bags (Clairo):");
      return;
    }
  }
}

void playSong(int song[], int durations[], String lyrics[], int melodyTotalNotes, int instrumental[], int instrumentalDurations[], int instrumentalTotalNotes) {
  unsigned long melodyCurrentTime = millis();
  bool melodyIsPlayingNote = false;
  int melodyNoteDuration = 0;
  unsigned long melodyNoteStartTime = 0;
  int melodyCurrentNote = 0;

  unsigned long instrumentalCurrentTime = millis();
  bool instrumentalIsPlayingNote = false;
  int instrumentalNoteDuration = 0;
  unsigned long instrumentalNoteStartTime = 0;
  int instrumentalCurrentNote = 0;

  //play the melody of the song
  while (melodyCurrentNote < melodyTotalNotes || instrumentalCurrentNote < instrumentalTotalNotes) 
  {
    melodyCurrentTime = millis(); //update time
    instrumentalCurrentTime = millis(); 
    if (melodyCurrentNote < melodyTotalNotes) {
      if (!melodyIsPlayingNote) 
      {
        melodyNoteDuration = 1700/durations[melodyCurrentNote];

        if(song[melodyCurrentNote] != NOTE_REST) 
        {
          tone(BUZZER_PIN, song[melodyCurrentNote], melodyNoteDuration);
        } //check if melodyCurrentNote is a rest and only play a tone() if it isn't a rest 
        else if (instrumentalCurrentNote != NOTE_REST) 
        {
          tone(BUZZER_PIN, instrumental[instrumentalCurrentNote], instrumentalNoteDuration);
        }
        
        melodyNoteStartTime = melodyCurrentTime; //record time the note started playing
        melodyIsPlayingNote = true;
      } //if a note isn't currently playing, continues
      else
        {
          unsigned long pauseBetweenNotes = melodyNoteDuration * 1.30; //declare pause time between notes - 30% of the note duration
          if (melodyCurrentTime - melodyNoteStartTime >= pauseBetweenNotes) //if the pause is finished, continue
          {
            melodyCurrentNote++;
            melodyIsPlayingNote = false;
          }

        }
    }

  }
  //loop that prints the lyrics onto the LCD
  // for (int currentLyrics = 0; currentLyrics < totalLyrics; currentLyrics++) {
  //   lcd.clear();
  //   lcd.setCursor(0,0);
  //   lcd.print(lyrics[currentLyrics]);
  // } note: make 2d array with lyrics later.. this is kinda pseudocode rn
}