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
  lcd.setupLCD();
  lcdInputMessage();  //call method that tells user to input via serial monitor on the lcd

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);    
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  
  Serial.begin(9600);
  
  Serial.println("1 is for Labubu Song, and 2 is for Bags (Clairo)."); //tells the user via serial monitor which song is which
}

void setupLCD() {
  lcd.clear();
  lcd.setCursor(0,0);
}

// when user inputs something invalid, this prints an error message onto the lcd
void lcdErrorMessage() {
  lcd.setupLCD();
  lcd.print("invalid input");
  delay(200);
}

// when the user needs to input which song they want to play, this method is called
void lcdInputMessage() {
      lcd.setupLCD();
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
    
    //send an error message to the user if they didn't input 1 or 2 and then ask them for input again
    if (userInputInt != 1 && userInputInt != 2)
    {
      lcd.setupLCD();
      lcdErrorMessage();
      delay(1000);
      lcdInputMessage();
      return;
    } 

    //play the labubu song when user inputs 1. after the song ends, ask them for input again & return
    if (userInputInt == 1) 
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

void playSong(int song[], int durations[], String lyrics[], int totalLyrics, int melodyTotalNotes, int melodySpeed, int lyricsSpeed) { //the higher the melodySpeed, the slower the song plays
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
    if (melodyCurrentNote < melodyTotalNotes) { //if a note isn't currently playing, it plays notes
      if (!melodyIsPlayingNote) 
      {
        melodyNoteDuration = melodySpeed/durations[melodyCurrentNote]; //calculate melody note duration (ms)

        if(song[melodyCurrentNote] != NOTE_REST) //if the current note isn't a rest, play a note and turn on the LED
        {
          tone(BUZZER_PIN, song[melodyCurrentNote], melodyNoteDuration);
          digitalWrite(ledPinNumber, HIGH);
        } 
        melodyNoteStartTime = melodyCurrentTime; //record time the note started playing
        melodyIsPlayingNote = true;

        if (melodyCurrentNote % lyricsSpeed == 0 && currentLyrics < totalLyrics - 1) //if the remainder of the current melody note / notes per lyric = 0 (modulo), and the lyrics aren't done playing:
        {
          lcd.setupLCD();
          lcd.print(lyrics[currentLyrics]); //prints the first line of lyrics
          lcd.setCursor(0,1); //moves down 1 line 
          lcd.print(lyrics[currentLyrics + 1]); //prints the 2nd line of lyrics by adding 1 to the first line's index
          currentLyrics++; // increases index so the next line of lyrics will be printed
        } 
      }
      else // if a note is currently being played, pause for a bit before playing the next note
        {
          unsigned long pauseBetweenNotes = melodyNoteDuration * 1.30; //declare pause time between notes - 30% of the note duration
          if (melodyCurrentTime - melodyNoteStartTime >= pauseBetweenNotes) //if the pause is finished, continue
          {
            digitalWrite(ledPinNumber, LOW); //turn off the led
            melodyCurrentNote++; //go to the next note 
            melodyIsPlayingNote = false; // make this condition false so if(!melodyIsPlayNote) will be true and that condition can run
            ledPinNumber++; //go to the next LED
            if (ledPinNumber > 7) {
              ledPinNumber = 3;
            } //if the bright LED is at the end of the line of LEDs, go back to the start
          }
        }
    }
  }
}