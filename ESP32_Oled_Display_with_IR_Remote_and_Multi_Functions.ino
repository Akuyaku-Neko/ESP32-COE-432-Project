#define BLYNK_TEMPLATE_ID "TMPL64E6HBtpy"
#define BLYNK_TEMPLATE_NAME "ESP32 OLED"
#define BLYNK_AUTH_TOKEN "SjrCCK8S0xOv6bBEsytFP_037D_NW0tB"

#define BLYNK_PRINT Serial

#include "ESPAsyncWebServer.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <IRremote.h>
#include <WiFi.h>
#include "time.h"
#include "sntp.h"
#include <ESPping.h>

#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/* 
  Bloody Tears from Castlevania II
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
// 
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST 0

int tempo = 144;
int buzzer = 17;
int thisNote = 0;

// MELODIES
int nggyu[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,4, //repeat from 1
  NOTE_E5,-4, NOTE_FS5,-4, NOTE_A5,16, NOTE_G5,16, NOTE_FS5,8,
  NOTE_D5,-4, NOTE_E5,-4, NOTE_A4,2,
  NOTE_A4,16, NOTE_A4,16, NOTE_B4,16, NOTE_D5,8, NOTE_D5,16,
  REST,4, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_D5,8, NOTE_E5,8, NOTE_CS5,-8,
  NOTE_B4,16, NOTE_A4,2, REST,4, 

  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,4, NOTE_A4,8, //7
  NOTE_A5,8, REST,8, NOTE_A5,8, NOTE_E5,-4, REST,4, 
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,8, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, REST,4,
   
  NOTE_D5,2, NOTE_E5,8, NOTE_FS5,8, NOTE_D5,8, //13
  NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, NOTE_A4,4,
  REST,2, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8,
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,-8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //18
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,8, NOTE_A4,8, NOTE_A4,8, 
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,

  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  //23
  NOTE_E5,4, NOTE_D5,2, REST,4,
  REST,8, NOTE_B4,8, NOTE_D5,8, NOTE_B4,8, NOTE_D5,8, NOTE_E5,4, REST,8,
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  REST,8, NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4,
  REST,8, NOTE_A5,8, NOTE_A5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_D5,8,
  
  REST,8, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //29
  REST,8, NOTE_CS5,8, NOTE_B4,8, NOTE_A4,-4, REST,4,
  NOTE_B4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, NOTE_A4,4, REST,8,
  REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_FS5,4, NOTE_E5,-4, 
  NOTE_D5,2, NOTE_D5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,4, 
  NOTE_E5,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,8, NOTE_A4,8, NOTE_A4,4,

  REST,-4, NOTE_A4,8, NOTE_B4,8, NOTE_CS5,8, NOTE_D5,8, NOTE_B4,8, //35
  REST,8, NOTE_E5,8, NOTE_FS5,8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_E5,-8, NOTE_E5,-8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

   NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //40
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
   
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8,  
  NOTE_E5,4, NOTE_D5,2, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_FS5,-8, NOTE_FS5,-8, NOTE_E5,-4, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16, //45
  
  NOTE_A5,4, NOTE_CS5,8, NOTE_D5,-8, NOTE_CS5,16, NOTE_B4,8, NOTE_A4,16, NOTE_B4,16, NOTE_D5,16, NOTE_B4,16,
  NOTE_D5,4, NOTE_E5,8, NOTE_CS5,-8, NOTE_B4,16, NOTE_A4,4, NOTE_A4,8, 

  NOTE_E5,4, NOTE_D5,2, REST,4
};

const PROGMEM int bloodyTears[] = {
  // Bloody Tears, from Castlevania II
  // Arranged by Bobby Lee. THe flute part was used 
  // https://musescore.com/user/263171/scores/883296

  REST, 4, NOTE_G5, 4,
  NOTE_A5, 4, NOTE_AS5, 4,
  NOTE_A5, 4, NOTE_F5, 4,
  NOTE_A5, 4, NOTE_G5, 4,
  REST, 4, NOTE_G5, 4,
  NOTE_A5, 4, NOTE_AS5, 4,
  NOTE_C6, 4, NOTE_AS5, 4,

  NOTE_A5, 4, NOTE_G5, 4, //8
  REST, 4, NOTE_G5, 4,
  NOTE_A5, 4, NOTE_AS5, 4,
  NOTE_A5, 4, NOTE_F5, 4,
  NOTE_A5, 4, NOTE_G5, 4,
  NOTE_D6, 4, REST, 8, NOTE_C6, 8,
  REST, 4, NOTE_AS5, 4,

  NOTE_A5, 4, NOTE_AS5, 8, NOTE_C6, 8, //15
  NOTE_F6, 8, REST, 8, REST, 4,
  NOTE_G5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,

  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16, //20
  NOTE_G5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,

  NOTE_G5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, //25
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
  NOTE_AS5, 16, NOTE_D5, 16, NOTE_D6, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,

  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16, NOTE_C6, 16, NOTE_D5, 16, NOTE_AS5, 16, NOTE_D5, 16,
  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 16, NOTE_D5, 16, NOTE_G5, 16, NOTE_D5, 16,
  NOTE_C6, 16, NOTE_C6, 16, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8,
  REST, 4, NOTE_C6, 16, NOTE_AS5, 16,

  NOTE_C6, -8,  NOTE_F6, -8, NOTE_D6, -4, //35
  NOTE_C6, 8, NOTE_AS5, 8,
  NOTE_C6, 8, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8,
  REST, 4, NOTE_C6, 8, NOTE_D6, 8,
  NOTE_DS6, -8, NOTE_F6, -8,

  NOTE_D6, -8, REST, 16, NOTE_DS6, 8, REST, 8, //40
  NOTE_C6, 8, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8,
  REST, 4, NOTE_C6, 8, NOTE_AS5, 8,
  NOTE_C6, -8,  NOTE_F6, -8, NOTE_D6, -4,
  NOTE_C6, 8, NOTE_AS5, 8,

  NOTE_C6, 8, NOTE_F6, 16, NOTE_D6, 8, REST, 16, REST, 8, //45
  REST, 4, NOTE_C6, 8, NOTE_D6, 8,
  NOTE_DS6, -8, NOTE_F6, -8,
  NOTE_D5, 8, NOTE_FS5, 8, NOTE_F5, 8, NOTE_A5, 8,
  NOTE_A5, -8, NOTE_G5, -4,

  NOTE_A5, -8, NOTE_G5, -4, //50
  NOTE_A5, -8, NOTE_G5, -4,
  NOTE_AS5, 8, NOTE_A5, 8, NOTE_G5, 8, NOTE_F5, 8,
  NOTE_A5, -8, NOTE_G5, -8, NOTE_D5, 8,
  NOTE_A5, -8, NOTE_G5, -8, NOTE_D5, 8,
  NOTE_A5, -8, NOTE_G5, -8, NOTE_D5, 8,

  NOTE_AS5, 4, NOTE_C6, 4, NOTE_A5, 4, NOTE_AS5, 4,
  NOTE_G5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,//56 //r
  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,
  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
  NOTE_A5,16, NOTE_D5,16, NOTE_F5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,

  NOTE_G5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,//61
  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
  NOTE_A5,16, NOTE_D5,16, NOTE_F5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,
  NOTE_G5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,

  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,//66
  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
  NOTE_A5,16, NOTE_D5,16, NOTE_F5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,
  NOTE_AS5,16, NOTE_D5,16, NOTE_D6,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,
  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_A5,16, NOTE_D5,16, NOTE_G5,16, NOTE_D5,16,

  NOTE_A5,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16, NOTE_C6,16, NOTE_D5,16, NOTE_AS5,16, NOTE_D5,16,//71 //
  NOTE_A5, 16, NOTE_D5, 16, NOTE_F5, 16, NOTE_D5, 16, NOTE_A5, 8, NOTE_G5, 32, NOTE_A5, 32, NOTE_AS5, 32, NOTE_C6, 32,
  NOTE_D6, 16, NOTE_G5, 16, NOTE_AS5, 16, NOTE_G5, 16, NOTE_C6, 16, NOTE_G5, 16, NOTE_D6, 16, NOTE_G5, 16,
  NOTE_C6, 16, NOTE_G5, 16, NOTE_A5, 16, NOTE_G5, 16, NOTE_F6, 16, NOTE_G5, 16, NOTE_D6, 16, NOTE_DS5, 16,
  NOTE_D6, 4, REST, 4,

  NOTE_C5, 8, REST, 8, NOTE_A4, -16, NOTE_AS4, -16, NOTE_C5, 16, //76
  NOTE_D6, 16, NOTE_G4, 16, NOTE_AS4, 16, NOTE_G4, 16, NOTE_C5, 16, NOTE_G4, 16, NOTE_D6, 16, NOTE_G4, 16,
  NOTE_C6, 16, NOTE_F4, 16, NOTE_A4, 16, NOTE_F4, 16, NOTE_F5, 16, NOTE_F4, 16, NOTE_D6, 16, NOTE_DS4, 16,
  NOTE_D6, 16, REST, 8, NOTE_E4, 16, NOTE_F4, 16,
  
  //change of key B Major A# C# D# F# G#
  NOTE_GS4, 8, REST, 8, NOTE_AS4, 8, REST, 8,

  NOTE_DS5, 16, NOTE_GS4, 16, NOTE_B4, 16, NOTE_GS4, 16, NOTE_CS5, 16, NOTE_GS4, 16, NOTE_DS5, 16, NOTE_GS4, 16, //81
  NOTE_CS5, 16, NOTE_FS4, 16, NOTE_AS4, 16, NOTE_FS4, 16, NOTE_FS5, 16, NOTE_FS4, 16, NOTE_DS5, 16, NOTE_E5, 16,
  NOTE_D5, 4, REST, 4,
  NOTE_CS5, 8, REST, 8, NOTE_AS4, -16,  NOTE_B4, -16, NOTE_CS5, 16,
  NOTE_DS5, 16, NOTE_GS4, 16, NOTE_B4, 16, NOTE_GS4, 16, NOTE_CS5, 16, NOTE_GS4, 16, NOTE_DS5, 16, NOTE_GS4, 16,
  
  NOTE_CS5, 16, NOTE_FS4, 16, NOTE_AS4, 16, NOTE_FS4, 16, NOTE_FS5, 16, NOTE_FS4, 16, NOTE_DS5, 16, NOTE_E5, 16,
  NOTE_DS5, 4, REST, 8, NOTE_DS5, 16,  NOTE_E5, 16,
  NOTE_FS5, 16, NOTE_CS5, 16, NOTE_E5, 16, NOTE_CS4, 16, NOTE_DS5, 16, NOTE_E5, 16, NOTE_G5, 16, NOTE_AS5, 16,
  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16, //90
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,//94
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,//98
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
  NOTE_GS5, 16, NOTE_DS5, 16, NOTE_DS6, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,

  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,//102
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16, NOTE_CS6, 16, NOTE_DS5, 16, NOTE_B5, 16, NOTE_DS5, 16,
  NOTE_AS5, 16, NOTE_DS5, 16, NOTE_FS5, 16, NOTE_DS5, 16, NOTE_AS5, 16, NOTE_DS5, 16, NOTE_GS5, 16, NOTE_DS5, 16,
  
  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8, //107
  REST,4, NOTE_CS6, 8, NOTE_B5, 8,
  NOTE_CS6,-8, NOTE_FS6, -8, NOTE_DS6, -4,
  NOTE_CS6, 8, NOTE_B5, 8,
  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8,
  REST,4, NOTE_CS6, 8, NOTE_B5, 8,
  NOTE_E6, -8, NOTE_F6, -8,
  
  NOTE_DS6,-8, REST,16, NOTE_E6,8, REST,16, REST,16, //112
  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8,
  REST,4, NOTE_CS6, 8, NOTE_B5, 8,
  NOTE_CS6,-8, NOTE_FS6, -8, NOTE_DS6, -4,
  NOTE_CS6, 8, NOTE_B5, 8,
  
  NOTE_CS6, 8, NOTE_FS6, 16, NOTE_DS6, 8, REST,16, REST,8, //117
  REST,4, NOTE_CS5, 8, NOTE_DS5, 8,
  NOTE_E5, -8, NOTE_F5, -8,
  NOTE_DS5, 8, NOTE_G5, 8, NOTE_GS5, 8, NOTE_AS5, 8,
  NOTE_AS5, -8, NOTE_GS5, -8,

  NOTE_AS5, -8, NOTE_GS5, -8,//122
  NOTE_AS5, -8, NOTE_GS5, -8,
  NOTE_B6, 8, NOTE_AS5, 8, NOTE_GS5, 8, NOTE_FS5, 8,
  NOTE_AS5,-8, NOTE_GS6, -8, NOTE_DS5, 8,
  NOTE_AS5,-8, NOTE_GS6, -8, NOTE_DS5, 8,
  NOTE_AS5,-8, NOTE_GS6, -8, NOTE_DS5, 8,

  NOTE_B5,8, NOTE_CS6, 8, NOTE_AS5, 8, NOTE_B5, 8,//128
  NOTE_GS5,8, REST,8, REST, 16
  
};

int notes = sizeof(bloodyTears) / sizeof(bloodyTears[0]) / 2;
int notes2 = sizeof(nggyu) / sizeof(nggyu[0]) / 2;
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

//SNAKE GAME from https://wokwi.com/projects/296135008348799496
#define SNAKE_PIECE_SIZE     3
#define MAX_SANKE_LENGTH   165
#define MAP_SIZE_X          20
#define MAP_SIZE_Y          20
#define STARTING_SNAKE_SIZE  5

int8_t snake[MAX_SANKE_LENGTH][2];
uint8_t snake_length;

int8_t fruit[2];

int buttonDir;
int buttonGo;
int snakePlay;
int moveTime = 0;
int spdSnake = 30;

typedef enum {
  START,
  RUNNING,
  GAMEOVER
} State;

typedef enum {
    LEFT,
    UP,
    RIGHT,
    DOWN
} Direction;

State gameState;

Direction dir;
Direction newDir;

//IR Remote
#pragma once
#define irrec 16 // IR Receiver PIN

//Time
#define TZ_Asia_Manila	PSTR("PST-8")

//Thermistor
int thermPin = 36;
int thermVal;

//Counter Millis
unsigned long prevMil = 0;
unsigned long prevMil1 = 0;
unsigned long nowMil;
unsigned long nowMil1;
const long interval = 1000;

//Time Setup
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 28800;
const int   daylightOffset_sec = 28800;

//Motor Driver PINS
int ENA = 2;
int ENB = 0;
int out1 = 4;
int out2 = 12;
int out3 = 32;
int out4 = 27;

//Motor Driver Values
int setMode6 = 0;
int spdMotor = 0;
int spdMotorVal = 125;

//Regulator
String vIn = "";
String vOut = "";

//Date / Time
char hrDisp[3];
char minDisp[3];
char secDisp[3];
char dateDisp[18];
char dayDisp[10];

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

//String Variables
String btnPress;
String serialPayload;
String tempString;

//Int Variables
int x;
int i = 0;
int count = 0;
int modeBTN = 0;
int dispSel;
int runMode = 0;
int tempVal = 0;
int timeStatus = 0;
int d;

int setMode9 = 0;

//Proximity

float distance;
float duration;
float inch;

float targetVal;
int lockStatus = 2;

int trigPin = 33;
int echoPin = 14;

//ESP32 Cam
const char* ssidCam = "ESP32-Cam-AccesPoint";
const char* passwordCam = "1431434455";

String ESP32CamCon;
String ESP32IP;

// IPAddress ping_ip1(192,168,4,3);
// IPAddress ping_ip2(192,168,4,4);
// IPAddress ping_ip3(192,168,4,5);
// IPAddress ping_ip4(192,168,4,6);

AsyncWebServer server(80);

char auth[] = BLYNK_AUTH_TOKEN;
WidgetTerminal terminal(V0);

int BlynkStatus = 0;
int val1;

String toString(IPAddress& ip) { // IP v4 only
  String ips;
  ips.reserve(16);
  ips = ip[0];  ips += '.';
  ips += ip[1]; ips += '.';
  ips += ip[2]; ips += '.';
  ips += ip[3];
  return ips;
}

BLYNK_WRITE(V1){
  val1 = param.asInt();

  if (val1 == 0) {
    // terminal.println("Mode Off");
    Serial.println("Blynk Mode 0");
    lockStatus = 0;
  } else if (val1 == 1) {
    // terminal.println("Mode Temperature Check");
    Serial.println("Blynk Mode 1");
    lockStatus = 0;
  } else if (val1 == 2) {
    distancePulse();
    delay(50);
    targetVal = distance;
    lockStatus = 1;
    // terminal.println("Mode Anti Theft");
    Serial.println("Blynk Mode 2");
  }
}

void buzzTone1() {
  if (thisNote < (notes * 2)) {
    thisNote = thisNote + 2;
    divider = pgm_read_word_near(bloodyTears+thisNote + 1);
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }

    tone(buzzer, pgm_read_word_near(bloodyTears+thisNote ), noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void buzzTone2() {
  if (thisNote < (notes2 * 2)) {
    thisNote = thisNote + 2;
    divider = pgm_read_word_near(nggyu+thisNote + 1);
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }

    tone(buzzer, pgm_read_word_near(nggyu+thisNote ), noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void distancePulse() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.034436)/2;
  inch = distance/2.54;
}

void setup() {
  Serial.begin(9600);
  EEPROM.begin(512);
  delay(10);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  sntp_set_time_sync_notification_cb( timeavailable );
  sntp_servermode_dhcp(1); 
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  oledClear();
  oledLn("Loading", 1, 1, 1, WHITE, BLACK);
  Serial.print("\n Trying to connect to wifi... \n");
  //Reading SSID and PASS from EEPROM to connect WiFi
  Serial.println("\n SSID: " + readStrEEPROM(1));
  Serial.println("\n PASS: " + readStrEEPROM(16));

  WiFi.begin(readStrEEPROM(1), readStrEEPROM(16));
  for (i = 0; i < 4; i++) {
    delay(500);
    if (WiFi.status() == WL_CONNECTED) {

      delay(500);
      oledClear();
      oledLn("Complete!", 1, 3, 5, WHITE, BLACK);
      break;
    } else {
      oledClear();
      oledLn("Trying to Connect...", 1, 3, 5, WHITE, BLACK);
    }
  }
  delay(1500);
  oledClear();
  oledLn("Select : ", 1, 3, 5, WHITE, BLACK);
  Serial.print("\n Program Started \n");

  pinMode(irrec, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);

  pinMode(trigPin, OUTPUT); // Trigger PIN
  pinMode(echoPin, INPUT); // Echo PIN

  IrReceiver.begin(irrec, ENABLE_LED_FEEDBACK);
}

void setupGame() {
  gameState = START;
  dir = RIGHT;
  newDir = RIGHT;
  buttonGo = 4;
  oled.clearDisplay();
  drawPressToStart();
  resetSnake();
  generateFruit();
  drawMap();
  drawScore();
  oled.display();
}

void resetSnake() {
  snake_length = STARTING_SNAKE_SIZE;
  for(int i = 0; i < snake_length; i++) {
    snake[i][0] = MAP_SIZE_X / 2 - i;
    snake[i][1] = MAP_SIZE_Y / 2;
  }
}

void buttonPress() {
  buttonDir = buttonGo;
  if (buttonGo < 4) {
    gameState = RUNNING;
  }
}

void readDirection() {
  buttonDir = buttonGo;
  newDir = (Direction)buttonGo;
  buttonGo = 4;
}

bool moveSnake() {
  int8_t x = snake[0][0];
  int8_t y = snake[0][1];

  switch(dir) {
    case LEFT:
    Serial.println("MOVE : LEFT");
      x -= 1;
      break;
    case UP:
    Serial.println("MOVE : UP");
      y -= 1;
      break;
    case RIGHT:
    Serial.println("MOVE : RIGHT");
      x += 1;
      break;
    case DOWN:
    Serial.println("MOVE : DOWN");
      y += 1;
      break;
  }
  if(collisionCheck(x, y))
    return true;

  for(int i = snake_length - 1; i > 0; i--) {
    snake[i][0] = snake[i - 1][0];
    snake[i][1] = snake[i - 1][1];
  }

  snake[0][0] = x;
  snake[0][1] = y;
  return false;
}

void checkFruit() {
  if(fruit[0] == snake[0][0] && fruit[1] == snake[0][1])
  {
    tone(buzzer, 1175, 200);
    if(snake_length + 1 <= MAX_SANKE_LENGTH)
      snake_length++;
    generateFruit();
  }
}

void generateFruit() {
  bool b = false;
  do {
    b = false;
    fruit[0] = random(0, MAP_SIZE_X);
    fruit[1] = random(0, MAP_SIZE_Y);
    for(int i = 0; i < snake_length; i++) {
      if(fruit[0] == snake[i][0] && fruit[1] == snake[i][1]) {
        b = true;
        continue;
      }
    }
  } while(b);
}

bool collisionCheck(int8_t x, int8_t y) {
  for(int i = 1; i < snake_length; i++) {
    if(x == snake[i][0] && y == snake[i][1]) return true;
  }
  if(x < 0 || y < 0 || x >= MAP_SIZE_X || y >= MAP_SIZE_Y) return true;
  return false;
}

void drawMap() {
  int offsetMapX = 128 - SNAKE_PIECE_SIZE * MAP_SIZE_X - 2;
  int offsetMapY = 2;

  oled.drawRect(fruit[0] * SNAKE_PIECE_SIZE + offsetMapX, fruit[1] * SNAKE_PIECE_SIZE + offsetMapY, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SSD1306_INVERSE);
  oled.drawRect(offsetMapX - 2, 0, SNAKE_PIECE_SIZE * MAP_SIZE_X + 4, SNAKE_PIECE_SIZE * MAP_SIZE_Y + 4, SSD1306_WHITE);
  for(int i = 0; i < snake_length; i++) {
    oled.fillRect(snake[i][0] * SNAKE_PIECE_SIZE + offsetMapX, snake[i][1] * SNAKE_PIECE_SIZE + offsetMapY, SNAKE_PIECE_SIZE, SNAKE_PIECE_SIZE, SSD1306_WHITE);
  }
}

void drawScore() {
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2,2);
  oled.print(F("Score:"));
  oled.println(snake_length - STARTING_SNAKE_SIZE); 
  // writeStrEEPROM(33, String(snake_length - STARTING_SNAKE_SIZE));
  // EEPROM.commit();
  // oledLn("HIGH \nSCORE: " + String(readStrEEPROM(33)), 1, 1, 13, WHITE, BLACK);
}

void drawPressToStart() {
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2, 24);
  oled.print(F("Press an\narrow to\nstart!"));
}

void drawGameover() {
  oled.setTextSize(1);
  oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(2,50);
  oled.println(F("GAMEOVER"));
}

//Local Time
void printLocalTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    oledLn("Trying to Get Time...", 1, 1, 1, WHITE, BLACK);
    count++;
    if (count == 3) {
      runMode = 0;
      oledClear();
      oledLn(" Couldn't connect to \n  WiFi, please make \n    sure you are \n       connected", 1, 1, 1, WHITE, BLACK);
      return;
    }
    return;
  }
  if (timeStatus == 0) {
    oledClear();
  }
  timeStatus = 1;
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
  strftime(hrDisp,3, "%H", &timeinfo);
  strftime(minDisp,3, "%M", &timeinfo);
  strftime(secDisp,3, "%S", &timeinfo);
  strftime(dateDisp,18, "%B %d %Y", &timeinfo);
  strftime(dayDisp,10, "%A", &timeinfo);
}

void timeavailable(struct timeval *t) {
  Serial.println("Got time adjustment from NTP!");
  if (runMode == 4) {
    printLocalTime();
  }
}

//IR_Remote Setup
void BTNsetup() {
  if (IrReceiver.decode()) {

    // Serial.println(IrReceiver.decodedIRData.decodedRawData);
    switch (IrReceiver.decodedIRData.decodedRawData){
      
      case 3125149440:
      Serial.println("Button 1 was pressed");
      x = 1;
      tone(buzzer, 294, 200);
      break;
      
      case 3108437760:
      Serial.println("Button 2 was pressed");
      x = 2;
      tone(buzzer, 294, 200);
      break;
      
      case 3091726080:
      Serial.println("Button 3 was pressed");
      x = 3;
      tone(buzzer, 294, 200);
      break;
      
      case 3141861120:
      Serial.println("Button 4 was pressed");
      x = 4;
      tone(buzzer, 294, 200);
      break;
      
      case 3208707840:
      Serial.println("Button 5 was pressed");
      x = 5;
      tone(buzzer, 294, 200);
      break;
      
      case 3158572800:
      Serial.println("Button 6 was pressed");
      x = 6;
      tone(buzzer, 294, 200);
      break;
      
      case 4161273600:
      Serial.println("Button 7 was pressed");
      x = 7;
      tone(buzzer, 294, 200);
      break;
      
      case 3927310080:
      Serial.println("Button 8 was pressed");
      x = 8;
      tone(buzzer, 294, 200);
      break;
      
      case 4127850240:
      Serial.println("Button 9 was pressed");
      x = 9;
      tone(buzzer, 294, 200);
      break;     
      
      case 3860463360:
      Serial.println("Button 0 was pressed");
      x = 10;
      tone(buzzer, 294, 200);
      break;

      case 3910598400:
      Serial.println("Button * was pressed "); 
      x = 11;
      tone(buzzer, 294, 200);
      break;

      case 4061003520:
      Serial.println("Button # was pressed ");
      x = 12;
      tone(buzzer, 294, 200);
      break;

      case 3877175040:
      Serial.println("Button UP was pressed");
      if (dispSel < 10 and modeBTN == 0) {
        dispSel++;
      }
      x = 13;
      tone(buzzer, 294, 200);
      break;

      case 2907897600:
      Serial.println("Button DOWN was pressed");
      if (dispSel > 1 and modeBTN == 0) {
        dispSel--;
      }
      x = 14;
      tone(buzzer, 294, 200);
      break;

      case 4144561920:
      Serial.println("Button LEFT was pressed");
      if (dispSel > 1 and modeBTN == 0) {
        dispSel--;
      }
      x = 15;
      tone(buzzer, 294, 200);
      break;

      case 2774204160:
      Serial.println("Button RIGHT was pressed");
      if (dispSel < 10 and modeBTN == 0) {
        dispSel++;
      }
      x = 16;
      tone(buzzer, 294, 200);
      break;

      case 3810328320:
      Serial.println("Button OK was pressed");
      x = 17;
      tone(buzzer, 294, 200);
      break;

      // default:
      // Serial.println(IrReceiver.decodedIRData.decodedRawData);
      // break;
    }
    // Serial.println(IrReceiver.decodedIRData.decodedRawData);
    IrReceiver.resume();
    
  }
}

//IR_Remote Conditions
void BTNsel() {

  if (modeBTN == 0) {
    if (x <= 10 and x >= 1) {
      dispSel = x;
    } else if (x == 17) {
      oledClear();
      runMode = dispSel;
      modeBTN = 1;
      count = 0;
      delay(10);
    }
    if (modeBTN == 0) {
      switch(dispSel) {
        case 1:
          oledLn("[1] WiFi  \n    Setup     ", 2, 1, 24, WHITE, BLACK); // WIFI SETUP
        break;
        
        case 2:
          oledLn("[2] WiFi  \n    Detail    ", 2, 1, 24, WHITE, BLACK); // WIFI DETAIL
        break;

        case 3:
          oledLn("[3] WiFi  \n   Dis/Rec   ", 2, 1, 24, WHITE, BLACK); // WIFI DISCONNECT/RECONNECT
        break;

        case 4:
          oledLn("[4] Date  \n   Time     ", 2, 1, 24, WHITE, BLACK); // DATE AND TIME
        break;

        case 5: 
          oledLn("[5] Snake \n    Game      ", 2, 1, 24, WHITE, BLACK); // SNAKE GAME
        break;

        case 6:
          oledLn("[6]Cooling\n    Fan        ", 2, 1, 24, WHITE, BLACK); // COOLING FAN 
        break;

        case 7:
          oledLn("[7] Volt  \n Regulator   ", 2, 1, 24, WHITE, BLACK); // CAMERA
        break;

        case 8:
          oledLn("[8] Prox  \n   Sensor    ", 2, 1, 24, WHITE, BLACK); // REGULATOR
        break;

        case 9:
          oledLn("[9] Camera\n            ", 2, 1, 24, WHITE, BLACK); // MANUAL
        break;

        case 10:
          oledLn("  BLYNK   \n  LINK     ", 2, 1, 24, WHITE, BLACK); // RESTART DEVICE
        break;
      } 
    }
  } else if(modeBTN == 1) {
    if (x == 11) {
      oledClear();
      oledLn("Select : ", 1, 1, 5, WHITE, BLACK);
      delay(10);
      modeBTN = 0;
      dispSel = 0;
      tempVal = 0;
      tempString = "";
      setMode6 = 0;
      thisNote = 0;
      x = 0;
    }
  }
}

//Read and Write String to EEPROM
void writeStrEEPROM(int addrOffset, const String &strToWrite) {
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}
String readStrEEPROM(int addrOffset) {
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  return String(data);
}

// [ MODE 1 ] Connecting to a WIFI (Use Serial to INPUT)
void selMode1() {
  if (modeBTN == 1 and runMode == 1 and tempVal == 0) {
    oledLn("Enter SSID : ", 1, 1, 1, WHITE, BLACK);
    oledLn("Use Serial Monitor", 1, 1, 15, WHITE, BLACK);
    if(Serial.available()>0) {
      serialPayload = Serial.readStringUntil('\r\n');
      Serial.print("\nSSID : " + serialPayload);
      writeStrEEPROM(1, serialPayload);
      tempVal = 1;
    }
  } else if (modeBTN == 1 and runMode == 1 and tempVal == 1) {
    oledLn("Enter PASS : ", 1, 1, 1, WHITE, BLACK);
    oledLn("Use Serial Monitor", 1, 1, 15, WHITE, BLACK);
    if(Serial.available()>0) {
      serialPayload = Serial.readStringUntil('\r\n');
      Serial.println("\nPASS : " + serialPayload);
      writeStrEEPROM(16, serialPayload);
      tempVal = 0;
      WiFi.begin(readStrEEPROM(1), readStrEEPROM(16));
      Serial.println("\nSSID : " + readStrEEPROM(1));
      Serial.println("PASS : " + readStrEEPROM(16));
      Serial.println("CONNECTING...");
      oledClear();
      oledLn("Trying to Connect...", 1, 3, 5, WHITE, BLACK);
      for (i = 0; i < 4; i++) {
        delay(500);
        if (WiFi.status() == WL_CONNECTED) {
          Serial.println("\nConnected Successfully!");
          delay(500);
          oledClear();
          oledLn("Complete!", 1, 3, 5, WHITE, BLACK);
          runMode = 2;
          modeBTN = 1;
          delay(1000);
          oledClear();
        } else {
          oledClear();
          oledLn("WiFi Error...", 1, 3, 5, WHITE, BLACK);
          oledClear();
        }
      }
    }
  }
  EEPROM.commit();
}

// [ MODE 2] Checking WiFi Connectivity
void selMode2() {
  if (modeBTN == 1 and runMode == 2 and tempVal == 0) {
    if (BlynkStatus == 1) {
      // terminal.println("SSID:" + readStrEEPROM(1));
      // terminal.println("PASS:" + readStrEEPROM(16));
    }
    tempString = "";
    tempVal = 1;
  } else if (modeBTN == 1 and runMode == 2 and tempVal == 1) {
    if (nowMil - prevMil >= interval) {
      prevMil = nowMil;
      oledLn("SSID:" + readStrEEPROM(1), 1, 1, 1, WHITE, BLACK);
      oledLn("PASS:" + readStrEEPROM(16), 1, 1, 10, WHITE, BLACK);
      oledLn("STATUS:" + tempString, 1, 1, 20, WHITE, BLACK);
      if (BlynkStatus == 1) {
        oledLn("  BLYNK CONNECTED  ", 1, 1, 32, WHITE, BLACK);
      } else {
        oledLn("                   ", 1, 1, 32, WHITE, BLACK);
      }
      if (WiFi.status() == WL_CONNECTED) {
        tempString = "CONNECTED   ";
      } else {
        tempString = "DISCONNECTED";
      }
    }
  }
}

// [ MODE 3 ] Disconnecting and Reconnecting
void selMode3() {
  if (modeBTN == 1 and runMode == 3 and tempVal == 0) {
    if (WiFi.status() == WL_CONNECTED) {
      oledLn("[1] DISCONNECT", 1, 1, 7, WHITE, BLACK);
      oledLn("[2] RECONNECT ", 1, 1, 19, WHITE, BLACK);
      if (x == 1) {
        WiFi.disconnect();
        Serial.println("\n WiFi Disconnected Successfully");
        oledClear();
        x = 0;
      } else if (x == 2) {
        oledClear();
        WiFi.disconnect();
        Serial.println("\n WiFi Disconnected Successfully");
        Serial.println("Trying to Reconnect WiFi");
        Serial.println("SSID: " + readStrEEPROM(1));
        Serial.println("PASS: " + readStrEEPROM(16));
        WiFi.begin(readStrEEPROM(1), readStrEEPROM(16));
        for (i = 1; i < 6; i++) {
          oledClear();
          oledLn("Attempt #" + String(i) + "\n to Connect", 1, 10, 10, WHITE, BLACK);
          delay(1000);
          if (WiFi.status() == WL_CONNECTED) {
            i = 6;
            oledClear();
            oledLn("Connected!", 1, 10, 10, WHITE, BLACK);
            delay(500);
            break;
          }
        }
        x = 0;
        if (WiFi.status() != WL_CONNECTED) {
          oledClear();
          oledLn("Failed", 1, 10, 10, WHITE, BLACK);
        }
        oledClear();
      }
    } else {
      oledClear();
      oledLn("   NOT CONNECTED \n PLEASE SETUP WIFI", 1, 1, 7, WHITE, BLACK);
      delay(1500);
      oledClear();
      runMode = 1;
    }
  }
}

// [ MODE 4 ] Clock Display
void selMode4() {
  if (modeBTN == 1 and runMode == 4 and tempVal == 0) {
    if (nowMil - prevMil >= interval) {
      prevMil = nowMil;
      printLocalTime();
      sscanf(hrDisp, "%d", &tempVal);
      Serial.println(timeStatus);
      if (timeStatus == 1) {
        oledPr(String(secDisp), 1, 76, 17, WHITE, BLACK);
        oledPr(tempString, 1, 90, 17, WHITE, BLACK);
        oledPr("  " + String(dateDisp) + "         ", 1, 1, 37, WHITE, BLACK);
        oledPr("           " + String(dayDisp) + "     ", 1, 1, 50, WHITE, BLACK);
        if (tempVal > 11) {
          tempString = "PM";
          if (tempVal > 12) {
            tempVal = tempVal - 12;
            oledPr(String(tempVal) + ":" + String(minDisp), 2, 10, 11, WHITE, BLACK);
            tempVal = 0;
          } else {
            oledPr(String(hrDisp) + ":" + String(minDisp), 2, 10, 11, WHITE, BLACK);
          }
        } else {
          if (tempVal == 0) {
            oledPr("12:" + String(minDisp), 2, 10, 11, WHITE, BLACK);
            tempString = "AM";
          } else {
            oledPr(String(hrDisp) + ":" + String(minDisp), 2, 10, 11, WHITE, BLACK);
            tempString = "AM";
          }
        }
      }
      tempVal = 0;
    }
  }
}

// [ MODE 5 ] Snake Game
void selMode5() {
  if (modeBTN == 1 and runMode == 5 and tempVal == 0) {
    // Serial.println("Play : " + buttonGo);
    
    switch (x) {
      case 15:
        buttonGo = 0;
      break;

      case 13:
        buttonGo = 1;
      break;

      case 16:
        buttonGo = 2;
      break;

      case 14:
        buttonGo = 3;
      break;

      case 12:
        switch(spdSnake) {
          case 30:
           spdSnake = 15;
           oledLn("Difficulty : Normal", 1, 1, 56, WHITE, BLACK);
           delay(1000);
           Serial.println("Normal");
          break;

          case 15:
           spdSnake = 5;
           oledLn("Difficulty : Hard  ", 1, 1, 56, WHITE, BLACK);
           delay(1000);
           Serial.println("Hard");
          break;

          case 5:
           spdSnake = 30;
           oledLn("Difficulty : Easy  ", 1, 1, 56, WHITE, BLACK);
           delay(1000);
           Serial.println("Easy");
          break;
        }
        Serial.println(spdSnake);
        x = 0;
      break;
    }
    // Serial.println("PRESSED : " + String(buttonGo));
    switch(gameState) {
      case START:
        buzzTone1();
        buttonPress();
        if (nowMil - prevMil >= interval) {
          prevMil = nowMil;
          setupGame();
        }
        // Serial.println("GAME START");
      break;
      
      case RUNNING:
      // Serial.println("GAME RUNNING");
        moveTime++;
        Serial.println("Movetime : " + String(moveTime));
        Serial.println("x : " + String(x));

        readDirection();
        if(moveTime >= spdSnake) {
          dir = newDir;
          oled.clearDisplay();
          if(moveSnake()) {
            gameState = GAMEOVER;
            drawGameover();
            delay(1000);
          }
          drawMap();
          drawScore();
          oled.display();
          checkFruit();
          moveTime = 0;
        }
        break;
      
      case GAMEOVER:
        // Serial.println("GAME OVER");
        if(x == 17) {
          delay(500);
          setupGame();
          gameState = START;
        }
        break;
    }
  
    delay(10);
  }
}

// [ MODE 6 ] Cooling Fan
void selMode6() {
  if (modeBTN == 1 and runMode == 6 and tempVal == 0) {
    spdMotor = map(spdMotorVal, 0, 255, 0, 100);
    if (setMode6 == 0) {
      oledLn("[1] Manual", 2, 1, 1, WHITE, BLACK);
      oledLn("[2] Auto", 2, 1, 20, WHITE, BLACK);
      if (x == 1) {
        setMode6 = 1;
        oledClear();
      } else if (x == 2) {
        setMode6 = 2;
        oledClear();
      }
    } else if (setMode6 == 1) {
      oledLn("    Manual    ", 1, 1, 1, WHITE, BLACK);
      if (d == 0 or d == 2) {
        if (digitalRead(out4) == 1) {
          oledLn("State: < ON  >", 1, 1, 15, WHITE, BLACK);
          oledLn("Speed :   " + String(spdMotor) + "  ", 1, 1, 30, WHITE, BLACK);
        } else if (digitalRead(out4) == 0) {
          oledLn("State: < OFF >", 1, 1, 15, WHITE, BLACK);
          oledLn("Speed :   " + String(spdMotor) + "  ", 1, 1, 30, WHITE, BLACK);
        }

        if (x == 17) {
          int showTemp = 0;
          if (digitalRead(out4) == HIGH) {
            digitalWrite(out4, LOW);
            digitalWrite(out3, LOW);
            delay(10);
          } else {
            digitalWrite(out4, HIGH);
            digitalWrite(out3, LOW);
            delay(10);
          }
          x = 0;
        }
      } else if (d == 1) {
        if (digitalRead(out4) == 1) {
          oledLn("State:  ON ", 1, 1, 15, WHITE, BLACK);
          oledLn("Speed : < " + String(spdMotor) + " >  ", 1, 1, 30, WHITE, BLACK);
        } else if (digitalRead(out4) == 0) {
          oledLn("State:  OFF", 1, 1, 15, WHITE, BLACK);
          oledLn("Speed : < " + String(spdMotor) + " >  ", 1, 1, 30, WHITE, BLACK);
        }
        analogWrite(ENB, spdMotorVal);
        Serial.println("Speed :" + String(spdMotorVal));
        if (x == 16) {
          if (spdMotorVal < 255) {
            spdMotorVal = spdMotorVal + 10;
            delay(10);
            Serial.println("Speed ++");
            x = 0;
          } else {
            spdMotorVal = 255;
          }
        } else if (x == 15) {
          if (spdMotorVal > 0) {
            spdMotorVal = spdMotorVal - 10;
            delay(10);
            Serial.println("Speed --");
            x = 0;
          } else {
            spdMotorVal = 0;
          }
        }
      }

      switch(x) {
        case 13:
          if (d == 0) {
            oledClear();
            d = 1;
            x = 0;
          } else {
            oledClear();
            d = 0;
            x = 0;
          } 
        break;

        case 14:
          if (d == 1) {
            oledClear();
            d = 0;
            x = 0;
          } else {
            oledClear();
            d = 1;
            x = 0;
          } 
        break;
      }
      
    } else if (setMode6 == 2) {
      if (nowMil - prevMil >= interval) {
        prevMil = nowMil;
        thermVal = analogRead(thermPin);
        thermVal = map(thermVal, 0, 4095, 0, 50);
        Serial.println("Temp : " + String(thermVal));
        oledLn(String(thermVal) + char(247) + "C", 2, 40, 25, WHITE, BLACK);
        if (BlynkStatus == 1) {
          // Blynk.virtualWrite(V2, thermVal);
          // terminal.println("Temperature : " + String(thermVal) + char(227) + "C");
        }
        if (thermVal >= 40) {
          digitalWrite(ENB, 255);
          digitalWrite(out4, HIGH);
          digitalWrite(out3, LOW);
          if (BlynkStatus == 1) {
            Blynk.virtualWrite(V3, 0);
          }
        } else if (thermVal <= 32) {
          digitalWrite(ENB, 0);
          digitalWrite(out4, LOW);
          digitalWrite(out3, LOW);
          if (BlynkStatus == 1) {
            Blynk.virtualWrite(V3, 0);
          }
        } else if (thermVal >= 47) {
          tone(buzzer, 1175, 200);
          delay(200);
          noTone(buzzer);
          if (BlynkStatus == 1) {
            Blynk.virtualWrite(V3, 1);
          }
        }
      }
    }
  }
}

// [ MODE 7 ] Voltage Regulator
void selMode7() {
  if (modeBTN == 1 and runMode == 7 and tempVal == 0)  {
    if (d == 0) {
      oledLn("V in  >> " + vIn, 1, 1, 1, WHITE, BLACK);
      oledLn("V out    " + vOut, 1, 1, 15, WHITE, BLACK);
      if (digitalRead(out1) == LOW) {
        oledLn("  RUN   ", 1, 1, 30, WHITE, BLACK);
      } else {
        oledLn("  STOP  ", 1, 1, 30, WHITE, BLACK);
      }
      if (x <= 9 and x >= 1) {
        vIn = vIn + String(x);
      } else if (x == 10) {
        vIn = vIn + "0";
      } else if (x == 12) {
        vIn = "";
        oledClear();
      }
      delay(10);
    } else if (d == 1) {
      oledLn("V in     " + vIn, 1, 1, 1, WHITE, BLACK);
      oledLn("V out >> " + vOut, 1, 1, 15, WHITE, BLACK);
      if (digitalRead(out1) == LOW) {
        oledLn("  RUN   ", 1, 1, 30, WHITE, BLACK);
      } else {
        oledLn("  STOP  ", 1, 1, 30, WHITE, BLACK);
      }
      if (x <= 9 and x >= 1) {
        vOut = vOut + String(x);
      } else if (x == 10) {
        vOut = vOut + "0";
      } else if (x == 12) {
        vOut = "";
        oledClear();
      }
      delay(10);
    } else if (d == 2) {
      oledLn("V in     " + String(vIn), 1, 1, 1, WHITE, BLACK);
      oledLn("V out    " + String(vOut), 1, 1, 15, WHITE, BLACK);
      if (digitalRead(out1) == LOW) {
        oledLn("> RUN < ", 1, 1, 30, WHITE, BLACK);
        if (x == 17) {
          float sol1 = 255 / vIn.toInt();
          int sol2 = (sol1 * vOut.toInt()) - 20;
          Serial.println("V out : " + String(sol2));
          analogWrite(ENA, sol2);
          digitalWrite(out1, HIGH);
          digitalWrite(out2, LOW);
        }
      } else {
        oledLn("> STOP <", 1, 1, 30, WHITE, BLACK);
        if (x == 17) {
          analogWrite(ENA, 0);
          digitalWrite(out1, LOW);
          digitalWrite(out2, LOW);
        }
      }
      
      delay(10);
    }
    switch(x) {
      case 13:
        if (d == 0) {
          oledClear();
          d = 2;
          x = 0;
        } else if (d == 1) {
          oledClear();
          d = 0;
          x = 0;
        } else if (d == 2) {
          oledClear();
          d = 1;
          x = 0;
        }
      break;

      case 14:
        if (d == 2) {
          oledClear();
          d = 0;
          x = 0;
        } else if (d == 1) {
          oledClear();
          d = 2;
          x = 0;
        } else if (d == 0) {
          oledClear();
          d = 1;
          x = 0;
        }
      break;
    }
    x = 0;
  }
}

// [ MODE 8 ] Object Detector
void selMode8() {
  if (modeBTN == 1 and runMode == 8 and tempVal == 0) {
    oledLn("Proximity Sensor", 1, 1, 1, WHITE, BLACK);
    distancePulse();
    delay(10);
    if (lockStatus == 0) {
      if (nowMil - prevMil >= interval) {
        prevMil = nowMil;
        oledLn("cm : " + String(distance) + "cm   ", 1, 1, 10, WHITE, BLACK);
        oledLn("in : " + String(inch) + "in   ", 1, 1, 20, WHITE, BLACK);
        oledLn(">  LOCK  <", 1, 30, 34, WHITE, BLACK);
      }
    } else if (lockStatus == 1) {
      oledLn("> UNLOCK <", 1, 30, 34, WHITE, BLACK);
    } else {
      x = 0;
      lockStatus = 0;
    }

    if (x == 17) {
      if (lockStatus == 0) {
        lockStatus = 1;
        targetVal = distance;
        oledClear();
        x = 0;
      } else {
        lockStatus = 0;
        oledClear();
        x = 0;
      }
    }

  }
}

// [ MODE 9 ] Camera
void selMode9() {
  if (modeBTN == 1 and runMode == 9 and tempVal == 0) {
    // if (IrReceiver.decode()) {
    //   switch(x) {
    //     case 13:
    //       if (i < 2) {
    //         i++;
    //       } else {
    //         i = 0;
    //       }
    //       oledClear();
    //       x = 0;
    //     break;

    //     case 16:
    //       if (i < 2) {
    //         i++;
    //       } else {
    //         i = 0;
    //       }
    //       oledClear();
    //       x = 0;
    //     break;

    //     case 14:
    //       if (i > 0 ) {
    //         i--;
    //       } else {
    //         i = 2;
    //       }
    //       oledClear();
    //       x = 0;
    //     break;

    //     case 15:
    //       if (i > 0 ) {
    //         i--;
    //       } else {
    //         i = 2;
    //       }
    //       oledClear();
    //       x = 0;
    //     break;
    //   }
    // }
    // if (nowMil - prevMil >= interval) {
    //   prevMil = nowMil;
    //   if (i == 0) {
    //     oledLn("Use * to go back", 1, 1, 1, WHITE, BLACK);
    //   } else if (i == 1) {
    //     oledLn("Use arrows to go \nup or down", 1, 1, 1, WHITE, BLACK);
    //   } else if (i == 2) {
    //     oledLn("Use numbers for \nselection or input", 1, 1, 1, WHITE, BLACK);
    //   }
    // }
    oledLn("   Camera   ", 1, 1, 1, WHITE, BLACK);
    if (nowMil - prevMil >= interval) {
      prevMil = nowMil;
      oledLn("IP : " + ESP32IP, 1, 1, 10, WHITE, BLACK); //
    }

    if (setMode9 == 0) {
      if (ESP32CamCon == "") {
        oledLn("> Connect  ", 1, 1, 20, WHITE, BLACK);
        oledLn("-------    ", 1, 1, 30, WHITE, BLACK);
      } else {
        oledLn("> Status : " + ESP32CamCon, 1, 1, 20, WHITE, BLACK);
        oledLn("Go Online  ", 1, 1, 30, WHITE, BLACK);
        
      }

      if (x == 17) {
        WiFi.disconnect();
        delay(10);
        WiFi.softAP(ssidCam, passwordCam);
        // IPAddress IP = WiFi.softAPIP();
        // Serial.println(toString(IP));
        // Serial.println("ESP32 Connected!");
        ESP32CamCon = "Released";
        x = 0;
      }
    } else if (setMode9 == 1) {
      if (ESP32CamCon == "") {
        oledLn("Connect    ", 1, 1, 20, WHITE, BLACK);
        oledLn("> -------  ", 1, 1, 30, WHITE, BLACK);
      } else {
        oledLn("Status :   " + ESP32CamCon, 1, 1, 20, WHITE, BLACK);
        oledLn("> Go Online", 1, 1, 30, WHITE, BLACK);

        if (x == 17) {
          // Serial.println("Ping : " + toString(ping_ip1));
          // if(Ping.ping(ping_ip1) > 0) {
          //   ESP32IP = toString(ping_ip1);
          //   Serial.println("Success!!");
          //   return;
          // } 
          for (i = 2; i < 10; i++) {
            IPAddress ping_ip(192,168,4,i);
            Serial.println("Ping : " + toString(ping_ip));
            if (Ping.ping(ping_ip) > 0) {
              ESP32IP = toString(ping_ip);
              x = 0;
              return;
            }
          }

          ESP32IP = "FAILED     ";
          
          // const char* serverNameTemp = "http://192.168.4.1/";
          // server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
          //   request->send_P(200, "text/plain", readTemp().c_str());
          // });

          // server.begin();
          
          x = 0;
          // server.on("/ssidCAM32", HTTP_GET, [](AsyncWebServerRequest *request){
          //   request->send_P(200, "text/plain", readStrEEPROM(1).c_str());
          // });
          // server.on("/passCAM32", HTTP_GET, [](AsyncWebServerRequest *request){
          //   request->send_P(200, "text/plain", readStrEEPROM(16).c_str());
          // });
        }
      }
      
    }
    
    switch(x) {
      case 13:
        if (setMode9 < 1) {
          setMode9++;
        } else {
          setMode9 = 0;
        }
        oledClear();
      break;

      case 14:
        if (setMode9 > 0) {
          setMode9--;
        } else {
          setMode9 = 1;
        }
        oledClear();
      break;
    }
    x = 0;
  }
}

// [MODE 10] BLYNK
void selMode10() {
  if (modeBTN == 1 and runMode == 10 and tempVal == 0) {
    Blynk.begin(auth, readStrEEPROM(1).c_str(), readStrEEPROM(16).c_str()); //BLYNK
    // Serial.println(String(readStrEEPROM(1).c_str()));
    // Serial.println(String(readStrEEPROM(16).c_str()));
    if (Blynk.connect() == 1) {
      Blynk.begin(auth, readStrEEPROM(1).c_str(), readStrEEPROM(16).c_str()); //BLYNK
      oledClear();
      oledLn("Success!", 1, 1, 1, WHITE, BLACK);
      delay(1500);
      oledClear();
      BlynkStatus = 1;
      Blynk.virtualWrite(V1, 0);
      Blynk.virtualWrite(V2, 0);
      Blynk.virtualWrite(V3, 0);
      Blynk.virtualWrite(V4, 1);
      runMode = 2;
      modeBTN = 1;
    } else {
      oledClear();
      oledLn("FAILED!", 1, 1, 1, WHITE, BLACK);
      delay(1500);
      oledClear();
      runMode = 0;
    }
  }
}

//OLED print line
void oledLn(String oledDis, int oledSize, int oledX, int oledY, char oledColor1, char oledColor2) {
  // oled.clearDisplay(); // clear display
  oled.setTextSize(oledSize);          // text size
  oled.setTextColor(oledColor1, oledColor2);     // text color
  oled.setCursor(oledX, oledY);        // position to display
  oled.println(oledDis); // text to display
  oled.display();
}

//OLED print
void oledPr(String oledDis, int oledSize, int oledX, int oledY, char oledColor1, char oledColor2) {
  // oled.clearDisplay(); // clear display
  oled.setTextSize(oledSize);          // text size
  oled.setTextColor(oledColor1, oledColor2);     // text color
  oled.setCursor(oledX, oledY);        // position to display
  oled.print(oledDis); // text to display
  oled.display();
}

//OLED clear
void oledClear() {
  oled.clearDisplay();
  oled.display();
}

void loop() {
  nowMil = millis();
  nowMil1 = millis();
  if (nowMil1 - prevMil1 >= interval*3) {
    prevMil1 = nowMil1;
    if (val1 == 1) {
    thermVal = analogRead(thermPin);
    thermVal = map(thermVal, 0, 4095, 0, 50);
      if (BlynkStatus == 1) {
        Blynk.virtualWrite(V2, thermVal);
        // terminal.println("Temperature : " + String(thermVal) + char(227) + "C");
      }
      if (thermVal >= 40) {
        digitalWrite(ENB, 255);
        digitalWrite(out4, HIGH);
        digitalWrite(out3, LOW);
        if (BlynkStatus == 1) {
          Blynk.virtualWrite(V3, 0);
        }
      } else if (thermVal <= 32) {
        digitalWrite(ENB, 0);
        digitalWrite(out4, LOW);
        digitalWrite(out3, LOW);
        if (BlynkStatus == 1) {
          Blynk.virtualWrite(V3, 0);
        }
      } else if (thermVal >= 47) {
        tone(buzzer, 1175, 200);
        delay(200);
        noTone(buzzer);
        if (BlynkStatus == 1) {
          Blynk.virtualWrite(V3, 1);
        }
      }
    }
    Serial.println("MODE BLYNK : " + String(val1) + "|" + String(BlynkStatus));
    Blynk.virtualWrite(V4, 1);
  }
  selMode1();
  // Serial.println("PASSED 1");
  selMode2();
  // Serial.println("PASSED 2");
  selMode3();
  // Serial.println("PASSED 3");
  selMode4();
  // Serial.println("PASSED 4");
  selMode5();
  // Serial.println("PASSED 5");
  selMode6();
  // Serial.println("PASSED 6");
  selMode7();
  // Serial.println("PASSED 7");
  selMode8();
  // Serial.println("PASSED 8");
  if (lockStatus == 1) {
    // Blynk.virtualWrite(V1, 2);
    distancePulse();
    delay(10);
    if (distance > (targetVal + 5) or distance < (targetVal - 5)) {
      tone(buzzer, 1175, 200);
      noTone(buzzer);
      delay(300);
      if (BlynkStatus == 1) {
        Blynk.virtualWrite(V3, 1);
        terminal.println("Movements Detected!");
        printLocalTime();
        terminal.println(String(dayDisp) + ", " + String(dateDisp) + " " + String(hrDisp) + ":" + String(minDisp) + ":" + String(secDisp));
        delay(10000);
      }
      
      // Serial.println("Distance : " + String(distance));
      // Serial.println("Target : " + String(targetVal));
      // buzzTone2();
    } else {
      if (BlynkStatus == 1) {
        Blynk.virtualWrite(V3, 0);
      }
    }
  }
  selMode9();
  selMode10();
  BTNsetup();
  BTNsel();
}
