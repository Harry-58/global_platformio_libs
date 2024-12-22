/***********************************
blink led1(Pin, OnTime, OffTime, <HIGH>);  // Constructor für led1  LED leuchtet bei HIGH (default)  (ist gegen GND geschaltet)
blink led2(13, 350, 350, LOW);             // Constructor für led2  LED leuchtet bei LOW             (ist gegen VCC geschaltet)

led1.setOnOffTime(50, 500);      // LED-On/Off Zeiten ändern
led1.setOnTime(100);             // LED-On Zeit ändern
led1.setOffTime(300);            // LED-OFF Zeit ändern

led2.on();                       // LED einschalten
led2.off();                      // LED ausschalten

led2.toogle());                  // LED umschalten (Ein/Aus)

led2.stop();                     // Blinken stoppen
led2.start();                    // Blinken fortsetzen

led2.dimm(150);                  // LED dimmen auf Level 0..255

void loop()
{
  ...
  led1.Update();                 // muß zyklisch für jede LED aufgerufen werden,
  led2.Update();                 // damit jede LED mit den definierten ON/OFF-Zeiten blinkt
  ...
}
************************************/
// https://learn.adafruit.com/multi-tasking-the-arduino-part-1/ditch-the-delay?view=all
// https://steemit.com/arduino/@sot-plug/simple-non-blocking-arduino-led-blink-class

#pragma once

#include <arduino.h>
class Blink {
  // Class Member Variables
  // These are initialized at startup
  uint8_t _ledPin;    // the number of the LED pin
  uint32_t _OnTime;   // milliseconds of on-time
  uint32_t _OffTime;  // milliseconds of off-time

  // These maintain the current state
  bool _onState;             // Ob LED bei HIGH oder LOW leuchtet
  bool _ledState;            // _ledState used to set the LED
  uint32_t _previousMillis;  // will store last time LED was updated
  bool _doBlink;
  int16_t _dimmLevel;

  // Constructor - creates a blink
  // and initializes the member variables and state
 private:
  void resetDimm() {
    if (_dimmLevel > 0) {
      _dimmLevel = -1;
      pinMode(_ledPin, OUTPUT);
    }
  }

 public:
  Blink(uint8_t pin, uint32_t on, uint32_t off, bool onState = HIGH) {
    _ledPin = pin;
    pinMode(_ledPin, OUTPUT);

    _OnTime  = on;
    _OffTime = off;

    _onState        = onState;
    _ledState       = !_onState;  // zunächst ist LED aus
    _previousMillis = 0;

    _doBlink   = false;  // blinken ist ausgeschaltet
    _dimmLevel = -1;
  }

  void setOnOffTime(uint32_t on, uint32_t off) {
    _OnTime  = on;
    _OffTime = off;
  }

  void setOnTime(uint32_t on) { _OnTime = on; }

  void setOffTime(uint32_t off) { _OffTime = off; }

  void Update() {
    // check to see if it's time to change the state of the LED
    uint32_t currentMillis = millis();
    if (_doBlink) {
      //  resetDimm();
      if ((_ledState == _onState) && (currentMillis - _previousMillis >= _OnTime)) {
        _ledState       = !_onState;       // Turn it off
        _previousMillis = currentMillis;   // Remember the time
        digitalWrite(_ledPin, _ledState);  // Update the actual LED
      } else if ((_ledState == !_onState) && (currentMillis - _previousMillis >= _OffTime)) {
        _ledState       = _onState;        // turn it on
        _previousMillis = currentMillis;   // Remember the time
        digitalWrite(_ledPin, _ledState);  // Update the actual LED
      }
    }
  }

  void stop() {
    resetDimm();
    _doBlink = false;
    Blink::off();
  }
  void start() {
    resetDimm();
    _doBlink = true;
  }

  void blink(uint8_t count) {
    resetDimm();
    for (size_t i = 0; i < count; i++) {
      if (_ledState == _onState) {
        _ledState = !_onState;             // Turn it off
        digitalWrite(_ledPin, _ledState);  // Update the actual LED
        delay(_OffTime);
      } else if (_ledState == !_onState) {
        _ledState = _onState;              // turn it on
        digitalWrite(_ledPin, _ledState);  // Update the actual LED
        delay(_OnTime);
      }
    }
  }

  void off() {
    _doBlink  = false;
    _ledState = !_onState;             // Turn it off
    digitalWrite(_ledPin, _ledState);  // Update the actual LED
  }
  void on() {
    resetDimm();
    _doBlink  = false;
    _ledState = _onState;              // turn it on
    digitalWrite(_ledPin, _ledState);  // Update the actual LED
  }
  void toggle() {
    resetDimm();
    _doBlink  = false;
    _ledState = !_ledState;            // Status umschalten
    digitalWrite(_ledPin, _ledState);  // Update the actual LED
  }
  void dimm(uint16_t value) {
    _ledState  = _onState;  // turn it on
    _dimmLevel = value;
    _doBlink   = false;
    analogWrite(_ledPin, _dimmLevel);
  }
};
