#ifndef CONFIG_ALL_H
#define CONFIG_ALL_H
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include "ipconvert.h"
#include "rwconf.h"

/// @brief 配置。开始StartConfigMethod、开始TCP，StartTcpRec、开始HTTP,PostHandleMethod
class configall
{
public:
    configall();
    // void ReceivePostData();
    void StartConfigMethod();
    void StartTcpRec();
    void PostHandleMethod();

    

};

#endif