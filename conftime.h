#ifndef CONF_TIME_H
#define CONF_TIME_H
#include <Arduino.h>
#include <time.h>

/// @brief 配置时间
class confTime
{
public:
    confTime();
    String ReadConftime();

private:
    String confTim;
};

#endif