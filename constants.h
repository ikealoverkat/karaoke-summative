#include <Arduino.h> //need this so I can use the String type

const int BUZZER_PIN = 8; //buzzer connects to pin 8 (plays the melody)
const int lcdWidth = 16; //how many characters wide the lcd is
const int lcdHeight = 2; //how many lines the lcd has

/*---- Bags - Clairo ----*/
int bagsNotes[] = {
    NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_A3, //Every second counts
    NOTE_REST, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_REST, NOTE_E4, NOTE_FS4, NOTE_E4, //I don't wanna talk to you anymore
    NOTE_REST, NOTE_REST, //rests
    NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_A3, NOTE_A3, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4,// All these little games, you can call me by the
    NOTE_A3, NOTE_B3, NOTE_D4, NOTE_FS4, NOTE_REST, NOTE_E4, NOTE_D4, // Name I gave you
    NOTE_REST, NOTE_REST,// rests
    NOTE_D4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_D4,  //yesterday
    NOTE_REST, NOTE_REST, NOTE_REST, NOTE_REST, NOTE_REST, //rests
    NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_REST, //every minute counts
    NOTE_REST, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_E4, NOTE_FS4, NOTE_E4, //I don't wanna watch TV anymore
    NOTE_REST, //rests
    NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_B3, NOTE_A3, NOTE_REST, // can you figure me out?
    NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_A3, NOTE_B3, NOTE_D4, NOTE_D4, NOTE_FS4, NOTE_E4, NOTE_D4, //just doing it to waste more time on the couch
    NOTE_REST, NOTE_REST, // rests
    NOTE_D4, NOTE_D4, NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_REST, // can you see me? I'm waiting for the right time it fixes itself here
    NOTE_D4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_B3, NOTE_REST, // I can't read you but if you want the pleasure's all mine 
    NOTE_D4, NOTE_D4, NOTE_A4, NOTE_A4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_E4, NOTE_E4, NOTE_REST, NOTE_REST, // Can you see me losing everything to hold back? 
    NOTE_D4, NOTE_E4, NOTE_A4, NOTE_E4, NOTE_E4, NOTE_E4, // I guess this could be worse
    NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, // Walking out the door with your bags
    NOTE_REST, // rests
    NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, // Walking out the door with your bags
    NOTE_REST, // rests
    NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, // Walking out the door with your bags
    NOTE_REST, // rests
    NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, NOTE_CS4, NOTE_B3, // Walking out the door with your bags
    NOTE_REST, NOTE_REST // rests
};

//2 = half note, 4 = quarter note, 8 = eigth note... etc
int bagsNoteDurations[] = {
    8, 8, 8, 8, 8, 8, //Every second counts
    4, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 4, //I don't wanna talk to you anymore
    1, 4, //rests
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, // All these little games, you can call me by the
    4, 8, 4, 8, 8, 4, 4, // Name I gave you
    4, 8, // rests
    8, 8, 2, 8, 8, //yesterday
    4, 2, 1, 1, 2, //rests
    8, 8, 8, 8, 8, 8, 8, //every minute counts
    4, 8, 8, 8, 8, 4, 8, 4, 8, 8, 4, //I don't wanna watch TV anymore
    2, //rests
    8, 8, 8, 8, 8, 8, 8, // can you figure me out?
    8, 8, 8, 8, 4, 4, 8, 8, 8, 4, 8, //just doing it to waste more time on the couch 
    4, 4, // rests
    8, 16, 16, 8, 8, 4, 4, 8, 8, 8, 4, 8, // can you see me? I'm waiting for the right time
    8, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 4, 8, // I can't read you but if you want the pleasure's all mine 
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 4, 8, 16, // Can you see me losing everything to hold back? 
    16, 8, 8, 8, 8, 4, // I guess this could be worse
    8, 8, 8, 8, 8, 8, 8, 8, 8, // Walking out the door with your bags
    1, // rests
    8, 8, 8, 8, 8, 8, 8, 8, // Walking out the door with your bags
    1, //rests
    8, 8, 8, 8, 8, 8, 8, 8, // Walking out the door with your bags
    1, //rests
    8, 8, 8, 8, 8, 8, 8, 4, // Walking out the door with your bags
    1, //rests
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8
};

int totalBagsNotes = sizeof(bagsNotes) / sizeof(bagsNotes[0]); //get total amount of notes from the size of the array note: research this later

String bagsLyrics[] = {"", ""};

/*---- Labubu Song ----*/
int labubuSongNotes[] = {
    NOTE_E4, NOTE_E4, NOTE_E4, //la bu bu
    NOTE_REST,
    NOTE_F4, NOTE_F4, NOTE_F4, //la bu bu
    NOTE_REST,
    NOTE_FS4, NOTE_FS4, NOTE_FS4, //la bu bu
    NOTE_REST,
    NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, //labu laa buu
    NOTE_REST,
    NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4 //la bu bu
    

};
//2 = half note, 4 = quarter note, 8 = eigth note... etc
int labubuSongNoteDurations[] = {
    4, 4, 4,
    2,
    4, 4, 4,
    2,
    4, 4, 4,
    2,
    8, 8, 4, 8, 8,
    4,
    4, 4, 8, 4
};

String labubuSongLyrics[] = {"", ""};

int totalLabubuSongNotes = sizeof(labubuSongNotes) / sizeof(labubuSongNotes[0]);

