#include "mqttmsg.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);


int mqtt_count = 0;

char smqtt_address[] = "66666";
const char *mqtt_addressa = smqtt_address;

// char smqtt_username[] = "66666";
// const char *mqtt_usernamea = smqtt_username;

// char smqtt_password[] = "66666";
// const char *mqtt_passworda = smqtt_password;

rwConf rd;

void MqttMethod::connectMQTTServer()
{
  rd.ReadMqttConf();
  strcpy(smqtt_address, rd.GetMqttAddressV());
  // strcpy(smqtt_username, rd.GetMqttUsernameV());
  // strcpy(smqtt_password, rd.GetMqttPasswordV());

  mqttClient.setServer(mqtt_addressa, (int)rd.GETMQTTPort());
  mqttClient.setBufferSize(MQTT_MAX_PACKET_SIZE);
  // mqttClient.setServer(mqtt_address1,1883);
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）
  String clientId = "pgsh-" + WiFi.macAddress();

  if (!rd.GetMQTT_Secret_Check_enable())
  {

    // 连接MQTT服务器
    // if (mqttClient.connect(clientId.c_str(), rd.GetMqttUsernameV().c_str(), rd.GetMqttPasswordV().c_str()))
    if (mqttClient.connect(clientId.c_str(), rd.GetMqttUsernameV().c_str(), rd.GetMqttPasswordV().c_str()))
    {
      Serial.println("MQTT Server Connected.");
      Serial.println("Server Address: ");
      Serial.println(mqtt_addressa);
      Serial.println("ClientId:");
      Serial.println(clientId);
    }
    else
    {

      Serial.print("MQTT Server Connect Failed. Client State:");
      Serial.println(mqttClient.state());
      if (mqttClient.state() == -1 || mqttClient.state() == -2 || mqttClient.state() == -3 || mqttClient.state() == -4 || mqttClient.state() == 1 || mqttClient.state() == 2 || mqttClient.state() == 3 || mqttClient.state() == 4 || mqttClient.state() == 5)
      {
        Serial.println("conncet error");
        mqtt_count += 1;
        if (mqtt_count >= 5)
        {
          // ESP.restart();
          WiFi.disconnect();
          connectWiFi();
        }
      }
    }
  }
  if (rd.GetMQTT_Secret_Check_enable())
  {
    // 连接MQTT服务器
    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println("MQTT Server Connected.");
      Serial.println("Server Address: ");
      Serial.println(mqtt_addressa);
      Serial.println("ClientId:");
      Serial.println(clientId);
    }
    else
    {

      Serial.print("MQTT Server Connect Failed. Client State:");
      Serial.println(mqttClient.state());
      if (mqttClient.state() == -1 || mqttClient.state() == -2 || mqttClient.state() == -3 || mqttClient.state() == -4)
      {
        Serial.println("conncet error");
        mqtt_count += 1;
        if (mqtt_count >= 5)
        {
          // ESP.restart();
          WiFi.disconnect();
          connectWiFi();
        }
      }
    }
  }
}

void MqttMethod::pubMQTTmsg(String timeA, float mqtemperature, float mqfahrenheit, float mqhumidity, String devicename)
{
  // static int value; // 客户端发布信息用数字

  // 建立发布主题。主题名称以Taichi-Maker-为前缀，后面添加设备的MAC地址。
  // 这么做是为确保不同用户进行MQTT信息发布时，ESP8266客户端名称各不相同，
  String topicString = "SJIOT/WSD/" + WiFi.macAddress();
  char publishTopic[topicString.length() + 1];
  strcpy(publishTopic, topicString.c_str());

  // 建立发布信息。信息内容以Hello World为起始，后面添加发布次数。
  String messageString = "{\"localtime\": \"" + timeA + "\",\"temperature\": \"" + mqtemperature + "\",\"fahrenheit\": \"" + mqfahrenheit + "\",\"humidity\": \"" + mqhumidity + "\",\"devicename\": \"" + devicename + "\"}";

  char publishMsg[messageString.length() + 1];
  strcpy(publishMsg, messageString.c_str());

  // 实现ESP8266向主题发布信息
  if (mqttClient.publish(publishTopic, publishMsg))
  {
    Serial.println("Publish Topic:");
    Serial.println(publishTopic);
    Serial.println("Publish message:");
    Serial.println(publishMsg);
  }
  else
  {
    Serial.println("Message Publish Failed.");
  }
}

void MqttMethod::pubElecMQTTmsg(String timeA, String Elec)
{
  // static int value; // 客户端发布信息用数字

  // 建立发布主题。主题名称以Taichi-Maker-为前缀，后面添加设备的MAC地址。
  // 这么做是为确保不同用户进行MQTT信息发布时，ESP8266客户端名称各不相同，
  String topicString = "SJIOT/DB/" + WiFi.macAddress();
  char publishTopic[topicString.length() + 1];
  strcpy(publishTopic, topicString.c_str());

  // 建立发布信息。信息内容以Hello World为起始，后面添加发布次数。
  String messageString = "{\"localtime\": \"" + timeA + "\",\"AccumulatePower\": \"" + Elec + "\"}";

  char publishMsg[messageString.length() + 1];
  strcpy(publishMsg, messageString.c_str());

  // 实现ESP8266向主题发布信息
  if (mqttClient.publish(publishTopic, publishMsg))
  {
    Serial.println("Publish Topic:");
    Serial.println(publishTopic);
    Serial.println("Publish message:");
    Serial.println(publishMsg);
  }
  else
  {
    Serial.println("Message Publish Failed.");
  }
}

void MqttMethod::publishMessageAll(String messageString)
{
  Serial.println("方法内的msg");
  Serial.println(messageString);
  // static int value; // 客户端发布信息用数字

  // 建立发布主题。主题名称以Taichi-Maker-为前缀，后面添加设备的MAC地址。
  // 这么做是为确保不同用户进行MQTT信息发布时，ESP8266客户端名称各不相同，
  String topicString = "SJIOT/DB/" + WiFi.macAddress();
  char publishTopic[topicString.length() + 1];
  strcpy(publishTopic, topicString.c_str());


  // 建立发布信息。信息内容以Hello World为起始，后面添加发布次数。
  //String messageString = "{\"localtime\":\"1970-01-01 08:00:25\",\"Phase\":\"Single\",\"Total\":{\"TotalPower\":\"000005.55\",\"TotalVoltage\":\"229.5\",\"TotalCurrent\":\"000.000\",\"Activepower\":\"00.0000\",\"Apparentpower\":\"00.0000\"},\"GridFrequency\":\"50.00\",\"MeterInternalTemperature\":\"020.9\",\"ClockBatteryVoltage\":\"03.56\"}";

const char* myChar = messageString.c_str();
// String messageString = "{\"localtime\":\"1970-01-01 08:00:25\",\"Phase\":\"Single\",\"Total\":{\"TotalPower\":\"000005.55\",\"TotalVolt";
// Serial.println("一下是mychar");
//   Serial.println(myChar);
  // char publishMsg[messageString.length() + 1];
  // strcpy(publishMsg, messageString.c_str());

  // 实现ESP8266向主题发布信息
  if (mqttClient.publish(publishTopic, myChar))
  {
    Serial.println("Publish Topic:");
    Serial.println(publishTopic);
    Serial.println("Publish message:");
    Serial.println(myChar);
  }
  else
  {
    Serial.println("Message Publish Failed.");
  }
}

// void MqttMethod::publishMessageAllOneValue(String TimeA,)
// {

//   // static int value; // 客户端发布信息用数字

//   // 建立发布主题。主题名称以Taichi-Maker-为前缀，后面添加设备的MAC地址。
//   // 这么做是为确保不同用户进行MQTT信息发布时，ESP8266客户端名称各不相同，
//   String topicString = "SJIOT/DB/" + WiFi.macAddress();
//   char publishTopic[topicString.length() + 1];
//   strcpy(publishTopic, topicString.c_str());

//   // 建立发布信息。信息内容以Hello World为起始，后面添加发布次数。
//   String messageString = ;

//   char publishMsg[msg.length() + 1];
//   strcpy(publishMsg, msg.c_str());

//   // 实现ESP8266向主题发布信息
//   if (mqttClient.publish(publishTopic, publishMsg))
//   {
//     Serial.println("Publish Topic:");
//     Serial.println(publishTopic);
//     Serial.println("Publish message:");
//     Serial.println(publishMsg);
//   }
//   else
//   {
//     Serial.println("Message Publish Failed.");
//   }
// }

void MqttMethod::MqttLoopMethod()
{
  mqttClient.loop();
}

bool MqttMethod::GetMqttConnectState()
{
  return mqttClient.connected();
}