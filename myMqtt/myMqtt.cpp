#include "myMqtt.h"

#include "Arduino.h"

#define DEBUG_EIN  //"Schalter" zum aktivieren von DEBUG-Ausgaben
#include <myDebug.h>


// clientID mit 3 letzten Stellen der MAC ergänzen
String myMqtt::makeClientIDfromMac(const String clientID) {
  String result;
  uint8_t mac[6];
  result.reserve(clientID.length() + 5);
  WiFi.macAddress(mac);
  result = clientID + "_";
  for (int i = 3; i < 6; ++i) {
    result += String(mac[i] & 0x7F, 16);
  }
  return result;
}

const char* myMqtt::makeTopic(String topic) {
  //
  return makeTopic(_baseTopic, topic);
}

const char* myMqtt::makeTopic(String baseTopic, String topic) {
  //
  return (baseTopic + "/" + topic).c_str();
}

bool myMqtt::publish(String topic, String payload) {
  //
  return this->publish(_baseTopic, topic, (const uint8_t*)payload.c_str(), payload.length(), false);
}
bool myMqtt::publish(String baseTopic, String topic, String payload) {
  //
  return this->publish(baseTopic, topic, (const uint8_t*)payload.c_str(), payload.length(), false);
}


bool myMqtt::publish(String topic, String payload, boolean retained) {
  //
  return this->publish(_baseTopic, topic, (const uint8_t*)payload.c_str(), payload.length(), retained);
}
bool myMqtt::publish(String baseTopic, String topic, String payload, boolean retained) {
  //
  return this->publish(baseTopic, topic, (const uint8_t*)payload.c_str(), payload.length(), retained);
}


bool myMqtt::publish(String topic, const uint8_t* payload, uint16_t plength) {
  //
  return this->publish(_baseTopic, topic, payload, plength, false);
}
bool myMqtt::publish(String baseTopic, String topic, const uint8_t* payload, uint16_t plength) {
  //
  return this->publish(baseTopic, topic, payload, plength, false);
}

bool myMqtt::publish(String topic, const uint8_t* payload, uint16_t plength, boolean retained) {
  //
  return this->publish(_baseTopic, topic, payload, plength, retained);
}
bool myMqtt::publish(String baseTopic, String topic, const uint8_t* payload, uint16_t plength, boolean retained) {
  DEBUG_PRINTF(("publish: " + baseTopic + "/" + topic + " ->%s<-").c_str(), payload);
  if (!PubSubClient::publish((baseTopic + "/" + topic).c_str(), payload, plength, retained)) {
    DEBUG_PRINTLN(" ... Error");
    return false;
  }
  DEBUG_PRINTLN(" ... OK");
  return true;
}



bool myMqtt::subscribe(String topic) {
  //
  return this->subscribe(_baseTopic, topic, 0);
}
bool myMqtt::subscribe(String baseTopic, String topic) {
  //
  return this->subscribe(baseTopic, topic, 0);
}


bool myMqtt::subscribe(String topic, uint8_t qos) {
  //
  return this->subscribe(_baseTopic, topic, qos);
}
bool myMqtt::subscribe(String baseTopic, String topic, uint8_t qos) {
  DEBUG_PRINTF(("subscribe: " + baseTopic + "/" + topic).c_str());
  if (!PubSubClient::subscribe((baseTopic + "/" + topic).c_str()), qos) {
    DEBUG_PRINTLN(" ... Error");
    return false;
  }
  DEBUG_PRINTLN(" ... OK");
  return true;
}