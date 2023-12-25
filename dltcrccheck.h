#ifndef DLT_CRC_CHECK_H
#define DLT_CRC_CHECK_H

#include <Arduino.h>

#include <iostream>
#include <sstream>
#include <string.h>

// using namespace std;

class dltcrccheck
{
public:
    int calculateChecksum(const std::string& input);
    String makeCheck(const std::string& data);
};

#endif
