#ifndef CONNECT_WIFI_H
#define CONNECT_WIFI_H
//进行宏定义时为了防止重复引用头文件而引起重定义错误
#include <WiFi.h>
// #include <WebServer.h>
#include <PubSubClient.h>
#include "rwconf.h"
#include "ipconvert.h"

void connectWiFi();  

 
#endif