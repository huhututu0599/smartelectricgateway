#ifndef DLT_CRC_CHECK_H
#define DLT_CRC_CHECK_H

#include <Arduino.h>

#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <iomanip>




class dltcrccheck
{
public:
    /// @brief 计算dlt645crc值
    /// @param input 输入的值，string类型
    /// @return 返回int类型数据，计算完成的crc
    int calculateChecksum(const std::string& input);

    String makeCheck(const std::string& data);
    std::string packStringToHexArray(const std::string& input);
    std::vector<uint8_t> splitStringToHex(const std::string& input);
    
    /// @brief 把字符串按照2位拆分为数组，例如6601 拆分为0x66，0x01
    /// @param hexString 传入方法的字符串
    /// @return 返回vector数据类型。
    std::vector<uint8_t> stringToByteArray(const std::string& hexString);
};

#endif
