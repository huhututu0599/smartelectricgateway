#include "configall.h"

WebServer server(80);
WiFiServer Tcpserver; // 声明Tcp服务器对象

const size_t capacityRecConf = JSON_OBJECT_SIZE(2) + 1024;
DynamicJsonDocument docRecConf(capacityRecConf);

const size_t capacityPOSTRecConf = JSON_OBJECT_SIZE(2) + 1024;
DynamicJsonDocument docPOSTRecConf(capacityPOSTRecConf);

const size_t capacityRecConf_Lic = JSON_OBJECT_SIZE(2) + 1024;
DynamicJsonDocument docPOSTRecConfLic(capacityRecConf_Lic);

rwConf rwc;

configall::configall()
{
  Serial.println("进入配置功能了~~~~~");
}

void ReceivePostLicData()
{
  if (server.hasArg("plain"))
  {
    String body = server.arg("plain");
    Serial.println(body);
    server.send(200, "text/html", "seccess");

    // 重点3：反序列化数据
    deserializeJson(docPOSTRecConfLic, body);

    // 重点4：获取解析后的数据信息
    String LocalLic = docPOSTRecConfLic["local_serial"].as<String>();
    String sensor_1 = docPOSTRecConfLic["sensor_1"].as<String>();
    String sensor_2 = docPOSTRecConfLic["sensor_2"].as<String>();

    server.send(200, "text/html", "configer success");

    rwc.SaveLic(LocalLic, sensor_1, sensor_2);

    rwc.SaveSatatConf(2);
  }
}

void ReceivePostData()
{

  // String wifi_ssid = server.arg("wifi_ssid");

  // String x1 = server.arg;

  if (server.hasArg("plain"))
  {
    String body = server.arg("plain");
    Serial.println(body);
    server.send(200, "text/html", "seccess");

    // 重点3：反序列化数据
    deserializeJson(docPOSTRecConf, body);

    // 重点4：获取解析后的数据信息
    String wifi_ssid = docPOSTRecConf["wifi_ssid"].as<String>();
    String wifi_password = docPOSTRecConf["wifi_password"].as<String>();
    bool DHCP_Enable = docPOSTRecConf["DHCP_Enable"].as<bool>();
    String ip_address = docPOSTRecConf["ip_address"].as<String>();

    String subnetmask = docPOSTRecConf["subnetmask"].as<String>();
    String gateway = docPOSTRecConf["gateway"].as<String>();
    String DNS1 = docPOSTRecConf["DNS1"].as<String>();
    String DNS2 = docPOSTRecConf["DNS2"].as<String>();
    String mqtt_address = docPOSTRecConf["mqtt_address"].as<String>();
    String mqtt_username = docPOSTRecConf["mqtt_username"].as<String>();
    String mqtt_password = docPOSTRecConf["mqtt_password"].as<String>();
    bool MQTT_Secret_Check_enable = docPOSTRecConf["MQTT_Secret_Check_enable"].as<bool>();

    int mqtt_port = docPOSTRecConf["mqtt_port"].as<int>();
    int mqtt_frequency = docPOSTRecConf["mqtt_frequency"].as<int>();
    String workmod = docPOSTRecConf["workmod"].as<String>();
    int mxnum = docPOSTRecConf["mxnum"].as<int>();
    int mx_frenq = docPOSTRecConf["mx_frenq"].as<int>();
    int shtnum = docPOSTRecConf["shtnum"].as<int>();
    int sht_frenq = docPOSTRecConf["sht_frenq"].as<int>();
    int fstnum = docPOSTRecConf["fstnum"].as<int>();
    int fst_frenq = docPOSTRecConf["fst_frenq"].as<int>();

    String LocalLic = docPOSTRecConf["local_serial"].as<String>();
    String sensor_1 = docPOSTRecConf["sensor_1"].as<String>();
    String sensor_2 = docPOSTRecConf["sensor_2"].as<String>();

    Serial.println(mqtt_address);
    Serial.println(mqtt_port);
    Serial.println(mqtt_frequency);
    Serial.println(workmod);
    Serial.println(mxnum);
    Serial.println(mx_frenq);
    Serial.println(shtnum);
    Serial.println(sht_frenq);
    Serial.println(fstnum);
    Serial.println(fst_frenq);

    server.send(200, "text/html", "configer success");
    // rwc.SaveIPConf(wifi_ssid1, wifi_password, dhcp, firstip, secondip, thirdip, forthip, firstsubnetmask, secondsubnetmask, thirdsubnetmask, forthsubnetmask, firstgateway, secondgateway, thirdgateway, forthgateway, firstdns1, seconddns1, thirddns1, forthdns1, firstdns2, seconddns2, thirddns2, forthdns2);
    rwc.SaveIPConf(wifi_ssid, wifi_password, DHCP_Enable, ip_address, subnetmask, gateway, DNS1, DNS2);
    rwc.SaveMqConf(mqtt_address, mqtt_port, mqtt_frequency, mqtt_username, mqtt_password,MQTT_Secret_Check_enable);
    rwc.SaveWorkConf(workmod, mxnum, mx_frenq, shtnum, sht_frenq, fstnum, fst_frenq);

    if (LocalLic != " ")
    {
      rwc.SaveLic(LocalLic, sensor_1, sensor_2);
    }

    rwc.SaveSatatConf(2);

    // digitalWrite(14, LOW);
    // WiFi.enableAP(false);
    // setup();

    // return;
    //  server.send(303);
  }
}

void configall::StartConfigMethod()
{
  WiFi.enableAP(true);
  WiFi.softAP("SmartT/H_AP", "12345678");

  server.on("/RecPost", ReceivePostData);
  server.on("/PostRecLic", ReceivePostLicData);
  server.begin();
  Serial.println("HTTP server started");
  delay(100);

  Tcpserver.begin(2333); // TCP服务器启动，端口号2333
}

void configall::StartTcpRec()
{

  WiFiClient client = Tcpserver.available(); // 尝试建立客户对象
  if (client)                                // 如果当前客户可用
  {
    Serial.println("[存在客户端连接]");
    String readBuff;           // 读取信息暂存
    while (client.connected()) // 如果客户端处于连接状态
    {
      if (client.available()) // 如果有可读数据
      {
        char c = client.read(); // 读取一个字节
                                // 也可以用readLine()等其他方法
        readBuff += c;
        // if(c == '\r') //接收到回车符
        // {
        //     client.print("已收到: " + readBuff); //向客户端发送
        //     Serial.println("已收到: " + readBuff); //从串口打印
        //     readBuff = "";
        //     break; //跳出循环
        // }

        // 先注释掉
        if (!client.available()) // 如果有可读数据
        {
          break;
        }
      }
    }
    if (readBuff.length() != 0)
    {
      Serial.println("已收到: " + readBuff); // 从串口打印
    }

    // 重点3：反序列化数据
    deserializeJson(docRecConf, readBuff);

    // 重点4：获取解析后的数据信息
    String conf_state_real = docRecConf["conf_state"].as<String>();

    String LocalLic = docRecConf["local_serial"].as<String>();
    String sensor_1 = docRecConf["sensor_1"].as<String>();
    String sensor_2 = docRecConf["sensor_2"].as<String>();
    String wifi_ssid = docRecConf["wifi_ssid"].as<String>();
    String wifi_password = docRecConf["wifi_password"].as<String>();
    bool DHCP_Enable = docRecConf["DHCP_Enable"].as<bool>();
    String ip_address = docRecConf["ip_address"].as<String>();

    String subnetmask = docRecConf["subnetmask"].as<String>();
    String gateway = docRecConf["gateway"].as<String>();
    String DNS1 = docRecConf["DNS1"].as<String>();
    String DNS2 = docRecConf["DNS2"].as<String>();
    String mqtt_address = docRecConf["mqtt_address"].as<String>();
    String mqtt_username = docRecConf["mqtt_username"].as<String>();
    String mqtt_password = docRecConf["mqtt_password"].as<String>();
    bool MQTT_Secret_Check_enable = docRecConf["MQTT_Secret_Check_enable"].as<bool>();

    int mqtt_port = docRecConf["mqtt_port"].as<int>();
    int mqtt_frequency = docRecConf["mqtt_frequency"].as<int>();
    String workmod = docRecConf["workmod"].as<String>();
    int mxnum = docRecConf["mxnum"].as<int>();
    int mx_frenq = docRecConf["mx_frenq"].as<int>();
    int shtnum = docRecConf["shtnum"].as<int>();
    int sht_frenq = docRecConf["sht_frenq"].as<int>();
    int fstnum = docRecConf["fstnum"].as<int>();
    int fst_frenq = docRecConf["fst_frenq"].as<int>();

    Serial.println("接收到的数据解析完成后结果---------------------------------------↓");
    Serial.println(wifi_ssid);
    Serial.println(wifi_password);
    Serial.println(DHCP_Enable);
    Serial.println(ip_address);
    Serial.println(subnetmask);
    Serial.println(gateway);
    Serial.println(DNS1);
    Serial.println(DNS2);
    Serial.println(mqtt_address);
    Serial.println(mqtt_port);
    Serial.println(mqtt_frequency);
    Serial.println(MQTT_Secret_Check_enable);

    Serial.println(workmod);
    Serial.println(mxnum);
    Serial.println(mx_frenq);
    Serial.println(shtnum);
    Serial.println(sht_frenq);
    Serial.println(fstnum);
    Serial.println(fst_frenq);

    Serial.println("-----------------------------------------------------------↑");

    if (conf_state_real == "serial")
    {

      Serial.println("写入Lic信息");
      Serial.println(LocalLic);
      Serial.println(sensor_1);
      Serial.println(sensor_2);

      rwc.SaveLic(LocalLic, sensor_1, sensor_2);
      readBuff = "";
      rwc.SaveSatatConf(2);
    }

    if (conf_state_real == "sht")
    {

      Serial.println("写入ip信息");
      rwc.SaveIPConf(wifi_ssid, wifi_password, DHCP_Enable, ip_address, subnetmask, gateway, DNS1, DNS2);

      Serial.println("写入MQ信息");

      rwc.SaveMqConf(mqtt_address, mqtt_port, mqtt_frequency, mqtt_username, mqtt_password, MQTT_Secret_Check_enable);

      Serial.println("写入探头信息信息");
      Serial.println(sht_frenq);
      rwc.SaveWorkConf(workmod, 0, 0, shtnum, sht_frenq, 0, 0);

      readBuff = "";

      rwc.SaveSatatConf(2);
    }

    if (conf_state_real == "fst")
    {

      Serial.println("写入ip信息");
      rwc.SaveIPConf(wifi_ssid, wifi_password, DHCP_Enable, ip_address, subnetmask, gateway, DNS1, DNS2);

      Serial.println("写入MQ信息");

      rwc.SaveMqConf(mqtt_address, mqtt_port, mqtt_frequency, mqtt_username, mqtt_password, MQTT_Secret_Check_enable);

      Serial.println("写入探头信息信息");
      rwc.SaveWorkConf(workmod, 0, 0, 0, 0, fstnum, fst_frenq);

      readBuff = "";

      rwc.SaveSatatConf(2);
    }

    // digitalWrite(14, LOW);

    // Serial.println("123");
    Serial.println("Receive Success");
    // client.stop();
  }
}

void configall::PostHandleMethod()
{
  // Serial.println("state=1配置模式");
  server.handleClient();
}
