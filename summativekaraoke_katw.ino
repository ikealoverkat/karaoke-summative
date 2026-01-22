/* 
Title: TEJ3M Karaoke Machine Summative
Author: Kat Wang
Date: 1/22/26
Description: 
  Karaoke machine made using an Arduino UNO R4, some LED lights, a 1602 I2C LCD, and a buzzer. 
  It plays the melody notes using the buzzer, and displays the lyrics on the LCD, while the LEDs flash every time the
  note that is being played changes.
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include "constants.h"

LiquidCrystal_I2C lcd(0x27, lcdWidth, lcdHeight); // set the LCD I2C address

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0); //initialize the lcd
  lcdInputMessage();  //call method that displays input text on the lcd

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);    
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);    
  
  Serial.begin(9600);
}

void lcdErrorMessage() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("invalid input");
  delay(200);
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
      playSong(bagsNotes, bagsNoteDurations, bagsLyrics, totalBagsLyrics, totalBagsNotes, 1700, 6);
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

  int ledPinNumber = 3;

  //play the melody of the song
  while (melodyCurrentNote < melodyTotalNotes) 
  {
    melodyCurrentTime = millis(); //update time
    if (melodyCurrentNote < melodyTotalNotes) { //if a note isn't currently playing, continues
      if (!melodyIsPlayingNote) 
      {
        melodyNoteDuration = melodySpeed/durations[melodyCurrentNote];

        if(song[melodyCurrentNote] != NOTE_REST) 
        {
          tone(BUZZER_PIN, song[melodyCurrentNote], melodyNoteDuration);
          digitalWrite(ledPinNumber, HIGH);
        } //check if melodyCurrentNote is a rest and only play a tone() if it isn't a rest         
        melodyNoteStartTime = melodyCurrentTime; //record time the note started playing
        melodyIsPlayingNote = true;

        if (melodyCurrentNote % lyricsSpeed == 0 && currentLyrics < totalLyrics - 1) //if the remainder of melodyNote divided by notes per lyric = 0 and the lyrics aren't done playing, continue
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print(lyrics[currentLyrics]);
          lcd.setCursor(0,1);
          lcd.print(lyrics[currentLyrics + 1]);
          currentLyrics++;          
        } 
      }
      else
        {
          unsigned long pauseBetweenNotes = melodyNoteDuration * 1.30; //declare pause time between notes - 30% of the note duration
          if (melodyCurrentTime - melodyNoteStartTime >= pauseBetweenNotes) //if the pause is finished, continue
          {
            digitalWrite(ledPinNumber, LOW);
            melodyCurrentNote++;
            melodyIsPlayingNote = false;
            ledPinNumber++;
            if (ledPinNumber > 7) {
              ledPinNumber = 3;
            }            
          }
        }
    }
  }
}