﻿/*
#include <beepTable.h>
#include <beeper.h>


beepTable_t myBeepTable = {
    // freq, dauer(ms)
    {440, 300},          // Frequenz in Hertz
    {587, 300},          // Frequenz in Hertz
    { beepPause(500)},   // Pause (500ms) zwischen den Tönen
    {880, 300},          // Frequenz in Hertz
    {NOTE_D6, 300},      // Frequenz als Define
    { beepEnde};         // Tabele muss mit Endekennung abgeschlossen werden
}


Beeper myBeeper(BeeperPin);             // Constructor

myBeeper.beep(myBeepTable)              // Tonfolge ausgeben mit delay                               (blockierend)
myBeeper.beep(frequenz,dauer,<wait>)    // einzelnen Ton ausgeben ohne/mit delay                     (nicht blockierend / blockierend)

myBeeper.start(myBeepTable);            // Tonfolge vorbereiten, die dann über loop ausgegeben wird  (nicht blockierend)

void loop(){
  ...
  myBeeper.Update();           // muß zyklisch aufgerufen werden, damit mit myBeeper.start vorbereitete Tonfolge ausgegeben wird
  ...
}
*/

#pragma once
#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#include <Arduino.h>

#define DEBUG__EIN  //"Schalter" zum aktivieren von DEBUG-Ausgaben
#include <myDebug.h>
#include <elapsedMillis.h>


struct beep_t {
   uint16_t frequenz;
   uint32_t dauer;
};
typedef const beep_t beepTable_t;

#define beepPause(pause) 0,pause
#define beepEnde 0, 0

beepTable_t beepOne[]= {
    // freq, dauer(ms)
    {2000, 200},
    {beepEnde}};

beepTable_t beepTwo[] = {
    // freq, dauer(ms)
    {2000, 100},
    {beepPause( 200 )},
    {1000, 100},
    {beepEnde}};

beepTable_t beepThree[] = {
    // freq, dauer(ms)
    {2000, 100},
    {beepPause(200)},
    {1000, 100},
    {beepPause(200)},
    {2000, 100},
    {beepEnde}};


class Beeper {
 public:
  Beeper(const int8_t pin);  // Constructor

  void beep(uint16_t frequenz, uint32_t dauer, bool wait = false);  // einzelnen Ton ausgeben ohne/mit delay
  void beep(beepTable_t beepTable[]);                               // Tonfolge ausgeben mit delay
  void start(beepTable_t beepTable[]);                              // Tonfolge ohne delay vorbereiten, die dann über loop ausgegeben wird
  void Update();                                                    // Tonfolge ohne delay ausführen

 private:
  int8_t _pin;

  elapsedMillis _beepTimer;
  beepTable_t (*_beepTableDo);
  int8_t _beepZeiger = -1;
};

Beeper::Beeper(const int8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void Beeper::start(beepTable_t beepTable[]) {
  _beepTableDo = beepTable;
  _beepZeiger  = 0;
  _beepTimer   = 0;
}

void Beeper::Update() {
  if (_beepZeiger > -1) {
    if ((_beepTableDo[_beepZeiger].frequenz + _beepTableDo[_beepZeiger].dauer) > 0) {  // nicht beepEnde
      if ((_beepZeiger == 0) || (_beepTimer > _beepTableDo[_beepZeiger - 1].dauer)) {
        DEBUG__PRINTF("Beep-%i %i/%i\n", _beepZeiger, _beepTableDo[_beepZeiger].frequenz, _beepTableDo[_beepZeiger].dauer);
        if (_beepTableDo[_beepZeiger].frequenz > 0 /*beepPause*/) tone(_pin, _beepTableDo[_beepZeiger].frequenz, _beepTableDo[_beepZeiger].dauer);
        _beepZeiger++;
        _beepTimer = 0;
      }
    } else {
      _beepZeiger = -1;
    }
  }
}

void Beeper::beep(const uint16_t frequenz, const uint32_t dauer, const bool wait) {
  tone(_pin, frequenz, dauer);
  if (wait) delay(dauer);
}

void Beeper::beep(beepTable_t beepTable[]) {
  DEBUG__PRINT("Beeper ");
  int i = 0;
  while (beepTable[i].frequenz + beepTable[i].dauer > 0) {  // nicht beepEnde
    if (beepTable[i].frequenz > 0 /*beepPause*/) tone(_pin, beepTable[i].frequenz, beepTable[i].dauer);
    DEBUG__(Serial << i << "  " << beepTable[i].frequenz << "/" << beepTable[i].dauer << "  ";)
    delay(beepTable[i].dauer);
    i++;
  }
  DEBUG__PRINTLN("");
}
