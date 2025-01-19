/*

#include <fan.h>

  fan(int16_t pin);                                                         // Constructor
  fan(int16_t pin, int16_t kickTime);                                       // Constructor
  fan(int16_t pin, int16_t kickTime, int16_t kickSpeed);                    // Constructor
  fan(int16_t pin, int16_t kickTime, int16_t kickSpeed, int16_t minSpeed);  // Constructor

  Defaultwerte:
        kickTime  = 100;  // ms
        kickSpeed = 100;  // %
        minSpeed  = 20;   // %  Mindestgeschwindigkeit damit Lüfter anläuft
        analogResolution = 255;


  void speed(uint16_t speed, bool kick);  // Lüftergeschwindigkeit setzen mit/ohne Kick
  void speed(uint16_t speed);             // Lüftergeschwindigkeit setzen mit Kick falls notwendig
  void loop();                            // muß regelmässig aufgerufen werden
  bool kickRun();                         // Abfagen ob Lüfter in Kick-Phase ist


Beispiel:
        fan myFan(FAN_PIN,200,100,20);   // Constructor

setup(){
        myFan.speed(60,true);  // Geschwindigkeit auf 60% mit Kick
...
}

loop(){
  myFan.loop();   // muß regelmässig aufgerufen werden
  ...
}
*/

#pragma once
#include <Arduino.h>

//#define DEBUG__EIN  //"Schalter" zum aktivieren von DEBUG-Ausgaben
#include <myDebug.h>

class fan {
 public:
  fan(int16_t pin);                                                         // Constructor
  fan(int16_t pin, int16_t kickTime);                                       // Constructor
  fan(int16_t pin, int16_t kickTime, int16_t kickSpeed);                    // Constructor
  fan(int16_t pin, int16_t kickTime, int16_t kickSpeed, int16_t minSpeed);  // Constructor

  void speed(uint16_t speed, bool kick);
  void speed(uint16_t speed);
  void loop();
  bool kickRun();
  void setResolution(uint8_t resolution);  // Auflösung für Analogausgabe setzen 8-12

  //+=================================================================================
 private:
  uint16_t _speed           = 0;
  uint16_t _speedOld        = 0;
  int16_t _kickTime         = 100;  // ms
  int16_t _kickSpeed        = 100;  // %
  int16_t _minSpeed         = 20;   // %  Mindestgeschwindigkeit damit Lüfter anläuft
  int8_t _resolution        = 8;    // Analogauflöung in Bit
  int16_t _analogResolution = 1 << _resolution;
  int16_t _pin;

  uint32_t _fanKickTimer = 0;
};
//+=================================================================================

fan::fan(int16_t pin) {
  _pin = pin;
  pinMode(pin, OUTPUT);
}

fan::fan(int16_t pin, int16_t kickTime) {
  _pin = pin;
  pinMode(pin, OUTPUT);
  _kickTime = kickTime;
}

fan::fan(int16_t pin, int16_t kickTime, int16_t kickSpeed) {
  _pin = pin;
  pinMode(pin, OUTPUT);
  _kickTime  = kickTime;
  _kickSpeed = kickSpeed;
}

fan::fan(int16_t pin, int16_t kickTime, int16_t kickSpeed, int16_t minSpeed) {
  _pin = pin;
  pinMode(pin, OUTPUT);
  _kickTime  = kickTime;
  _kickSpeed = kickSpeed;
  _minSpeed  = minSpeed;
  fan::setResolution(_resolution);
}

void fan::setResolution(uint8_t resolution) {
  _resolution       = resolution;
  _analogResolution = 1 << _resolution;
  analogWriteResolution(_resolution);
  DEBUG__PRINTF("AnalogResolution %i --> %i\n", _resolution, _analogResolution);
}

void fan::speed(uint16_t speed, bool kick) {
  _speed = speed;
  if (kick) {
    analogWrite(_pin, map(_kickSpeed, 0, 100, 0, _analogResolution));
    _fanKickTimer = millis() + _kickTime;
    DEBUG__PRINTF("FAN kick (%ims)s:%i\n", _kickTime,  _kickSpeed);
  } else {
    analogWrite(_pin, map(_speed, 0, 100, 0, _analogResolution));
    DEBUG__PRINTF("FAN speed s: %i --> %li\n", _speed, map(_speed, 0, 100, 0, _analogResolution));
  }
}

void fan::speed(uint16_t speed) {
  _speed = speed;
  if (speed == 0) {
    _speedOld     = _speed;
    _fanKickTimer = 0;
    analogWrite(_pin, 0);
    DEBUG__PRINTF("FAN ausschalten\n");
    return;
  }
  if ((_speedOld == 0) && (speed < _minSpeed)) {  // kick notwendig ? weil Lüfter noch nicht läuft
                                                  // und Speed kleiner als Anlaufgeschwindigkeit ist
    analogWrite(_pin, _kickSpeed);
    _fanKickTimer = millis() + _kickTime;
    DEBUG__PRINTF("FAN kick (%ims) s:%i\n", _kickTime,  _kickSpeed);
  } else if (!_fanKickTimer) {  // wenn nicht in Kick-Phase
    analogWrite(_pin, map(_speed, 0, 100, 0, _analogResolution));
    DEBUG__PRINTF("FAN speed s: %i --> %li\n", _speed, map(_speed, 0, 100, 0, _analogResolution));
  }
  _speedOld = _speed;
}

void fan::loop() {
  if (_fanKickTimer && (millis() > _fanKickTimer)) {  // Wenn KickTime abgelaufen ist,
    _fanKickTimer = 0;                                // wird auf die gewünschte Geschwindigkeit umgeschaltet
    analogWrite(_pin, map(_speed, 0, 100, 0, _analogResolution));
    DEBUG__PRINTF("FAN speed l: %i --> %li\n", _speed, map(_speed, 0, 100, 0, _analogResolution));
  }
}

inline bool fan::kickRun() { return _fanKickTimer; }  // Lüfter in Kick-Phase ?
