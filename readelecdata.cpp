#include "readelecdata.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <SoftwareSerial.h>
#include "dltcrccheck.h"

#define RE 4                 // Connect RE terminal with 32 of ESP
#define DE 5                 // Connect DE terminal with 33 of ESP
SoftwareSerial modx(16, 17); // RX=16->RO , TX =17
using namespace std;

void readelecdata::SetInit()
{
    // SoftwareSerial mod(16, 17); // RX=16->RO , TX =17
    Serial.println("初始化");
    Serial.println("setinit->elec");
    modx.begin(2400, SWSERIAL_8E1);
    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
    Serial.println("485电平已准备就绪");
}

/// @brief 解析modbus收到的数据
/// @param input 传入的数组
/// @param output 输出的值
/// @param size 输入值的大小
void readelecdata::reverseBytes(unsigned char *input, unsigned char *output, int size)
{
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10);
    Serial.println("Start Write");
    Serial.println();
    modx.write(input, size);
    Serial.println("end write");

    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    delay(1000);

    Serial.println("mod.available is:");
    Serial.println(modx.available());

    if (modx.available())
    { // 如果有数据返回，则进行处理
        byte response[modx.available()];
        modx.readBytes(response, sizeof(response)); // 读取返回的数据

        Serial.println("Received response from meter:");
        for (int j = 0; j < sizeof(response); j++)
        {
            Serial.print(response[j], HEX);
            Serial.print(" ");
            output[j] = response[j];
        }
    }
    delay(1000);
    // return mod.available();
}

/// @brief  读取总功耗
/// @param input 传入电表号
void readelecdata::ReadTotalPower(const std::string &input)
{
    //
    // unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x33, 0x33, 0x33, 0xF8, 0x16};

    // 莲花路店2号表
    //                         FE FE FE 68  03 29 18  11 12 22 68 11 04 33 33 33 33 3A 16
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x03, 0x29, 0x18, 0x11, 0x12, 0x22, 0x68, 0x11, 0x04, 0x33, 0x33, 0x33, 0x33, 0x3A, 0x16};

    unsigned char *bytePointerTotalPower = data;
    unsigned char *outputdataTotalPower;
    outputdataTotalPower = new unsigned char[sizeof(data) + 2];
    reverseBytes(bytePointerTotalPower, outputdataTotalPower, sizeof(data));

    for (int i = 0; i < sizeof(data) + 2; i++)
    {
        if (outputdataTotalPower[i] == 0x91)
        {
            stringstream ss1;
            stringstream ss2;
            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1 << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 9] - 0x33
                << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 8] - 0x33
                << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 7] - 0x33;
            ss2 << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 6] - 0x33;

            string elecPower = ss1.str() + "." + ss2.str();
            ElecTotalPower = elecPower.c_str();
        }
        Serial.print(outputdataTotalPower[i], HEX);
        Serial.print(" ");
    }
    Serial.println(" ");
}

String readelecdata::GetElecTotalPower()
{
    return ElecTotalPower;
}
String readelecdata::GetElecTotalVoltage()
{
    return ElecTotalVoltage;
}
String readelecdata::GetElecTotalCurrent()
{
    return ElecTotalCurrent;
}
String readelecdata::GetElecActivepower()
{
    return ElecActivepower;
}
String readelecdata::GetElecApparentpower()
{
    return ElecApparentpower;
}
String readelecdata::GetNeutralwireCurrent()
{
    return ElecNeutralwireCurrent;
}
String readelecdata::GetElecGridFrequency()
{
    return ElecGridFrequency;
}
String readelecdata::GetElecMeterInternalTemperature()
{
    return ElecMeterInternalTemperature;
}
String readelecdata::GetElecClockBatteryVoltage()
{
    return ElecClockBatteryVoltage;
}
String readelecdata::GetElecInternalBatteryOperatingTime()
{
    return ElecInternalBatteryOperatingTime;
}