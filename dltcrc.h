#ifndef DLT_CRC_H
#define DLT_CRC_H

#include <Arduino.h>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

class dltcrc
{
public:
    String makeCheck(String data);
};

#endif