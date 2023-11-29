#ifndef MQTT_MSG_H
#define MQTT_MSG_H

#include "conncetwifi.h"
#include <WiFi.h>
#include <WebServer.h>
#include <PubSubClient.h>

// WiFiClient  wifiClient;

class MqttMethod
{

public:
    void connectMQTTServer();
    void pubMQTTmsg(String timeA, float mqtemperature, float mqfahrenheit, float mqhumidity, String devicename);
    void pubElecMQTTmsg(String timeA, String Elec);
    void MqttLoopMethod();
    void publishMessageAll(String msg);
    bool GetMqttConnectState();
    

private:
    bool MqttConnectState;

};

#endif