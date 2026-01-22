#include <analogWave.h> //r4 has a built in DAC on pin A0! I am free from tone()!!!
analogWave instrumentalPlayer(DAC);
/* 
Author: Kat Wang
Date: 1/20/26
Description: karaoke
*/

#include <Wire.h>
#include <LiquidCrystal.h>
#include "pitches.h"
#include "constants.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcdInputMessage(); 
  Serial.begin(9600);
}

void lcdErrorMessage() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("invalid input");
  delay(200); //remove later
}

void lcdInputMessage() {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("input 1 or 2");
      lcd.setCursor(0,1);
      lcd.print("into the monitor");
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
      lcd.clear();
      lcd.setCursor(0,0);
      lcdErrorMessage();
      delay(1000);
      lcdInputMessage();
      return;
    } //send an error message to the user if they didn't input 1 or 2 and then ask them for input again

    if (userInputInt == 1) //play the labubu song when user inputs 1
    {
      playSong(labubuSongNotes, labubuSongNoteDurations, labubuSongLyrics, totalLabubuLyrics, totalLabubuSongNotes, 1200, 4);
      lcdInputMessage();
      return;
    } 
    else if (userInputInt == 2) //play Bags when user inputs 2
    {
      playSong(bagsNotes, bagsNoteDurations, bagsLyrics, totalBagsLyrics, totalBagsNotes, 1700, 7);
      lcdInputMessage();
      return;
    }
  }
}

void playSong(int song[], int durations[], String lyrics[], int totalLyrics, int melodyTotalNotes, int melodySpeed, int lyricsSpeed) { //the higher the speed, the slower the song plays
  unsigned long melodyCurrentTime = millis();
  bool melodyIsPlayingNote = false;
  int melodyNoteDuration = 0;
  unsigned long melodyNoteStartTime = 0;
  int melodyCurrentNote = 0;

  int currentLyrics = 0;
  unsigned long lyricsDisplayDuration = 0;

  //play the melody of the song
  while (melodyCurrentNote < melodyTotalNotes) 
  {
    melodyCurrentTime = millis(); //update time
    if (melodyCurrentNote < melodyTotalNotes) {
      if (!melodyIsPlayingNote) 
      {
        melodyNoteDuration = melodySpeed/durations[melodyCurrentNote];
        lyricsDisplayDuration = melodyNoteDuration * 4; //display each lyric for 4 notes

        if(song[melodyCurrentNote] != NOTE_REST) 
        {
          tone(BUZZER_PIN, song[melodyCurrentNote], melodyNoteDuration);
        } //check if melodyCurrentNote is a rest and only play a tone() if it isn't a rest         
        melodyNoteStartTime = melodyCurrentTime; //record time the note started playing
        melodyIsPlayingNote = true;

        if (melodyCurrentNote % lyricsSpeed == 0 && currentLyrics < totalLyrics - 1) //if the remainder of melodyNote/4 = 0
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(lyrics[currentLyrics]);
          lcd.setCursor(0,1);
          lcd.print(lyrics[currentLyrics + 1]);
          currentLyrics++;          
        } 
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

      // loop that prints the lyrics onto the LCD
      // for (int currentLyrics = 0; currentLyrics < totalLyrics; currentLyrics++) {
      //   lcd.clear();
      //   lcd.setCursor(0,0);
      //   unsigned long lyricsDisplayStartTime = millis();
      //   while (millis() - lyricsDisplayStartTime < lyricsDisplayDuration) {
      //       lcd.print(lyrics[currentLyrics]);
      //       lcd.setCursor(0,1);
      //       lcd.print(lyrics[currentLyrics + 1]);
      //   }
      // }  
    }

  }

  //control the LEDs in a loop (it's like a metronome so every beat that music plays a different LED lights up and they go in a line)
  // for (int i = 0; i < melodyTotalNotes; i++) {
  //   digitalWrite(LED_PIN, HIGH);
  // }
}