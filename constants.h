#include <Arduino.h> //for the String type

const int BUZZER_PIN = 8; //buzzer connects to pin 8
const int lcdWidth = 16; //how many characters wide the lcd is
const int lcdHeight = 2; //how many lines the lcd has

/*---- Bags - Clairo ----*/
int bagsNotes[51] = {NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
NOTE_G4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_G4,
NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,NOTE_G4, NOTE_C4, NOTE_D4,
NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4,
NOTE_G4, NOTE_G4, NOTE_F4, NOTE_D4, NOTE_C4};
//2 = half note, 4 = quarter note, 8 = eigth note... etc
int bagsNoteDurations[51] = {
4,4,2,4,4,2,4,4,4,4,1,4,4,4,4,4,4,4,8,8,4,4,4,4,2,2,4,4,2,4,4,2,
4,4,4,4,1,4,4,4,4,4,4,4,8,8,4,4,4,4,1
};

int totalBagsNotes = 51;

String bagsLyrics[] = {"", ""};

/*---- Labubu Song ----*/
int labubuSongNotes[] = {

};
//2 = half note, 4 = quarter note, 8 = eigth note... etc
int labubuSongNoteDurations[] = {

};

String labubuSongLyrics[] = {"", ""};

int totalLabubuSongNotes = 51;

