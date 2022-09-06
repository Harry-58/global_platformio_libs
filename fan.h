#pragma once
#include <Arduino.h>

#define DEBUG_EIN  //"Schalter" zum aktivieren von DEBUG-Ausgaben
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

  //+=================================================================================
 private:
  uint16_t _speed    = 0;
  uint16_t _speedOld = 0;
  int16_t _kickTime  = 100;   // ms
  int16_t _kickSpeed = 1024;  // pwm
  int16_t _minSpeed  = 300;   // pwm  Mindestgeschwindigkeit damit Lüfter anläuft

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
}


void fan::speed(uint16_t speed, bool kick) {
  _speed = speed;
  if (kick) {
    analogWrite(_pin, _kickSpeed);
    _fanKickTimer = millis() + _kickTime;
    DEBUG_PRINTF("FAN kick (%ims)\n", _kickTime);
  } else {
    analogWrite(_pin, speed);
    DEBUG_PRINTF("FAN speed s: %i\n", _speed);
  }
}

void fan::speed(uint16_t speed) {
  _speed = speed;
  if (speed == 0) {
    _speedOld     = _speed;
    _fanKickTimer = 0;
    analogWrite(_pin, speed);
    DEBUG_PRINTF("FAN ausschalten\n");
    return;
  }
  if ((_speedOld == 0) && (speed < _minSpeed)) {  // kick notwendig ? weil Lüfter noch nicht läuft
                                                  // und Speed kleiner als Anlaufgeschwindigkeit ist
    analogWrite(_pin, _kickSpeed);
    _fanKickTimer = millis() + _kickTime;
    DEBUG_PRINTF("FAN kick (%ims)\n", _kickTime);
  } else if (!_fanKickTimer) {  // wenn nicht in Kick-Phase
    analogWrite(_pin, speed);
    DEBUG_PRINTF("FAN speed s: %i\n", _speed);
  }
  _speedOld = _speed;
}

void fan::loop() {
  if (_fanKickTimer && (millis() > _fanKickTimer)) {  // Wenn KickTime abgelaufen ist,
    _fanKickTimer = 0;                                // wird auf die gewünschte Geschwindigkeit umgeschaltet
    analogWrite(_pin, _speed);
    DEBUG_PRINTF("FAN speed l: %i\n", _speed);
  }
}

inline bool fan::kickRun() { return _fanKickTimer; } // Lüfter in Kick-Phase ?
