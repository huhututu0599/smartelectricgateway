#ifndef DLT_CRC_CHECK_H
#define DLT_CRC_CHECK_H

#include <Arduino.h>

#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <iomanip>

// using namespace std;

class dltcrccheck
{
public:
    int calculateChecksum(const std::string& input);
    String makeCheck(const std::string& data);
    std::string packStringToHexArray(const std::string& input);
    std::vector<uint8_t> splitStringToHex(const std::string& input);
};

#endif
