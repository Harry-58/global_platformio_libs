#ifndef __MY_MQTT_H__
#define __MY_MQTT_H__

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

class myMqtt : public PubSubClient {
 public:
  myMqtt(Client& client) : PubSubClient(client) {
    // Konstuktor
    _client    = &client;
    _baseTopic = "";
  }

  void setWill(const char topic[]) { this->setWill(topic, ""); }
  void setWill(const char topic[], const char payload[]) { this->setWill(topic, payload, false, 0); }
  void setWill(const char topic[], const char payload[], bool retained, int qos);
  void clearWill();

  //boolean connect(String id, String user, String pass);

  bool publish(                  String topic, String payload);
  bool publish(String baseTopic, String topic, String payload);

  bool publish(                  String topic, String payload, boolean retained);
  bool publish(String baseTopic, String topic, String payload, boolean retained);

  bool publish(                  String topic, const uint8_t * payload, uint16_t plength);
  bool publish(String baseTopic, String topic, const uint8_t * payload, uint16_t plength);

  bool publish(                  String topic, const uint8_t * payload, uint16_t plength,  boolean retained);
  bool publish(String baseTopic, String topic, const uint8_t * payload, uint16_t plength,  boolean retained);

  bool subscribe(                  String topic);
  bool subscribe(String baseTopic, String topic);

  bool subscribe(                  String topic, uint8_t qos);
  bool subscribe(String baseTopic, String topic, uint8_t qos);

  void setBaseTopic(const char* baseTopic) { this->_baseTopic = (char*)baseTopic; }

  String makeClientIDfromMac(const String clientID);
  const char* makeTopic(String topic);
  const char* makeTopic(String baseTopic, String topic);

 protected:
 private:
  Client* _client;
  String _baseTopic;
};

#endif