#include "readdata.h"

using namespace std;

#define RE 4 // Connect RE terminal with 32 of ESP
#define DE 5 // Connect DE terminal with 33 of ESP

SoftwareSerial mod(16, 17); // RX=16->RO , TX =17
// const byte ModFstReadBuffer[] = {0x7B, 0x03, 0x00, 0x00, 0x00, 0x02, 0xCF, 0x91};

// 电压指令
// FEFEFE 68 02 02 00 03 20 20 68 11 04 33 34 34 35 FC 16
// const byte ModFstReadBuffer[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0xFC, 0x16};

void readdata::OneFstSetUp()
{
    // SoftwareSerial mod(16, 17); // RX=16->RO , TX =17
    Serial.println("setup->fst");
    mod.begin(2400, SWSERIAL_8E1);
    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
    Serial.println("485FST电平已准备就绪");
}

// 解析电能数据、校验位
//   int cscalc = 0;
//  for (int i = 0; i < sizeof(response); i++)
//          {
//              Serial.print(response[i], HEX);
//              Serial.print(" ");
//              cscalc += response[i] % 256;
//          }
//          int lastTwo = cscalc & 0xFF;
//          Serial.print("校验位为:");
//          Serial.println(lastTwo, HEX);

/// @brief 获取组合有功总电能
/// @return map返回4个key 、Onebit、TwoBit、ThreeBit、FourBit
/// 1、Onebit -33 = 十万和万位、TwoBit-33 = 千和百位。ThreeBit -33 = 十和个位。FourBit-33 = 小数位。
std::map<std::string, std::string> readdata::ReadDLTdata()
{

    std::map<std::string, std::string> dicz;

    Serial.println("state=2常规工作模式-------------菲尔斯特探头工作模式");
    // delay(1000);

    // 总电能
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10);
    byte data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x33, 0x33, 0x33, 0xF8, 0x16};

    // byte data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0xFC, 0x16};

    mod.write(data, sizeof(data)); // 发送数据到电表
                                   // 延迟1秒，等待电表响应

    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    delay(1000);
    Serial.println("----------1----------↓");

    if (mod.available())
    { // 如果有数据返回，则进行处理
        byte response[mod.available()];
        mod.readBytes(response, sizeof(response)); // 读取返回的数据

        Serial.println("Received response from meter:");
        for (int j = 0; j < sizeof(response); j++)
        {
            Serial.print(response[j], HEX);
            Serial.print("  ");
        }

        for (int i = 0; i < sizeof(response); i++)
        {
            if (response[i] == 0x91)
            {
                // Onebit、TwoBit、ThreeBit、FourBit
                Serial.println("↓-----------------------↓");
                Serial.println((int)response[i + 6], HEX);
                Serial.println((int)response[i + 7], HEX);
                Serial.println((int)response[i + 8], HEX);
                Serial.println((int)response[i + 9], HEX);
                Serial.println("↑-----------------------↑");
                Serial.println("↓222-----------------------222↓");
                Serial.println((int)response[i + 6] - 0x33, HEX);
                Serial.println((int)response[i + 7] - 0x33, HEX);
                Serial.println((int)response[i + 8] - 0x33, HEX);
                Serial.println((int)response[i + 9] - 0x33, HEX);
                Serial.println("↑222-----------------------222↑");

                stringstream ss1;
                stringstream ss2;
                // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

                ss1 << hex << setw(2) << setfill('0') << (int)response[i + 9] - 0x33
                    << hex << setw(2) << setfill('0') << (int)response[i + 8] - 0x33
                    << hex << setw(2) << setfill('0') << (int)response[i + 7] - 0x33;
                ss2 << hex << setw(2) << setfill('0') << (int)response[i + 6] - 0x33;

                string elecPower = ss1.str() + "." + ss2.str();
                dicz.insert(pair<std::string, std::string>("AccumulatePower", elecPower));
                // dicz.insert(pair<std::string, int>("FourBit", (int)response[i + 6] - 0x33));
                // dicz.insert(pair<std::string, int>("ThreeBit", (int)response[i + 7] - 0x33));
                // dicz.insert(pair<std::string, int>("TwoBit", (int)response[i + 8] - 0x33));
                // dicz.insert(pair<std::string, int>("Onebit", (int)response[i + 9] - 0x33));
            }
        }
    }
    Serial.println();

    Serial.println("↑-----------1----------↑");

    return dicz;
}

void readdata::reverseBytes(unsigned char *input, unsigned char *output, int size)
{
    // byte x1[] = {};
    // Serial.println("input data to x1 is:");
    // for (int i = 0; i < size; i++)
    // {
    //     x1[i] = input[i];
    //     Serial.print(x1[i], HEX);
    //     Serial.print(" ");
    // }
    // Serial.println("x1 value");
    // for (int i = 0; i < size; i++)
    // {
    //     Serial.print(x1[i],HEX);
    //     Serial.print(" ");
    // }

    Serial.println(" ");

    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
    delay(10);
    Serial.println("Start Write");
    Serial.println(size);
    mod.write(input, size);
    Serial.println("end write");

    digitalWrite(DE, LOW);
    digitalWrite(RE, LOW);
    delay(1000);
    // unsigned char data2[] = {0x77, 0x88};
    // unsigned char *outputdata1 = data2;

    // int szof = mod.available();
    Serial.println("mod.available is:");
    Serial.println(mod.available());

    if (mod.available())
    { // 如果有数据返回，则进行处理
        byte response[mod.available()];
        mod.readBytes(response, sizeof(response)); // 读取返回的数据

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

// String TotalPower,TotalVoltage,TotalCurrent,Activepower,Apparentpower,NeutralwireCurrent,GridFrequency,MeterInternalTemperature,ClockBatteryVoltage,InternalBatteryOperatingTime;

// FE FE FE 68 02 02 00 03 20 20 68 11 04 33 33 34 33 F9 16
// 电量

// 电压
// FEFEFE 68 02 02 00 03 20 20 68 11 04 33 34 34 35 FC 16

/// @brief 读取总功耗
void readdata::ReadTotalPower()
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
            // // Onebit、TwoBit、ThreeBit、FourBit
            // Serial.println("↓-----------------------↓");
            // Serial.println((int)outputdata[i + 6], HEX);
            // Serial.println((int)outputdata[i + 7], HEX);
            // Serial.println((int)outputdata[i + 8], HEX);
            // Serial.println((int)outputdata[i + 9], HEX);
            // Serial.println("↑-----------------------↑");
            // Serial.println("↓222-----------------------222↓");
            // Serial.println((int)outputdata[i + 6] - 0x33, HEX);
            // Serial.println((int)outputdata[i + 7] - 0x33, HEX);
            // Serial.println((int)outputdata[i + 8] - 0x33, HEX);
            // Serial.println((int)outputdata[i + 9] - 0x33, HEX);
            // Serial.println("↑222-----------------------222↑");

            stringstream ss1;
            stringstream ss2;
            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1 << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 9] - 0x33
                << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 8] - 0x33
                << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 7] - 0x33;
            ss2 << hex << setw(2) << setfill('0') << (int)outputdataTotalPower[i + 6] - 0x33;

            string elecPower = ss1.str() + "." + ss2.str();
            TotalPower = elecPower.c_str();
        }
        Serial.print(outputdataTotalPower[i], HEX);
        Serial.print(" ");
    }
    Serial.println(" ");

   // delete[] outputdataTotalPower;
}

/// @brief 读取电压
void readdata::ReadTotalVoltage()
{
    // 电压
    // FE FE FE 68 02 02 00 03 20 20 68 11 04 33 34 34 35 FC 16
    // unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0xFC, 0x16};

    // 莲花路店2号表
    //
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x03, 0x29, 0x18, 0x11, 0x12, 0x22, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0x3E, 0x16};

    unsigned char *bytePointerTotalVoltage = data;
    unsigned char *outputdataTotalVoltage;
    outputdataTotalVoltage = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerTotalVoltage, outputdataTotalVoltage, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataTotalVoltage[i] == 0x91)
        {
            stringstream ss2TotalVoltage;
            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            int hexnTotalVoltage = (int)outputdataTotalVoltage[i + 6] - 0x33; // 2位16进制数

            ss2TotalVoltage << hex << setw(2) << setfill('0') << outputdataTotalVoltage[i + 7] - 0x33;

            char str[5]; // 要赋值的string类型变量，长度应足够存储转换后的字符串
            char str1[5];
            // 使用位运算取出第一位，并将其转换为字符串格式
            sprintf(str, "%.1X", (hexnTotalVoltage >> 4) & 0x0F);

            // 输出结果
            // printf("The value of str is: %s\n", str);

            sprintf(str1, "%.1X", hexnTotalVoltage & 0x0F);

            string elecVoltage = ss2TotalVoltage.str() + str + "." + str1;
            TotalVoltage = elecVoltage.c_str();
        }
    }
    Serial.println(" ");

   // delete[] outputdataTotalVoltage;
}

/// @brief 读取电流
void readdata::ReadTotalCurrent()
{
    // 电流
    // 6802020003202068110433343535 FD16

    // unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x34, 0x35, 0x35, 0xFD, 0x16};

    // 莲花路店2号表
    //
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x03, 0x29, 0x18, 0x11, 0x12, 0x22, 0x68, 0x11, 0x04, 0x33, 0x34, 0x35, 0x35, 0x3F, 0x16};

    unsigned char *bytePointerTotalCurrent = data;
    unsigned char *outputdataTotalCurrent;
    outputdataTotalCurrent = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerTotalCurrent, outputdataTotalCurrent, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataTotalCurrent[i] == 0x91)
        {
            stringstream ss2TotalCurrent;
            stringstream ss3TotalCurrent;

            // ss2TotalVoltage << hex << setw(2) << setfill('0') << outputdataTotalVoltage[i + 7] - 0x33;

            ss2TotalCurrent << hex << setw(2) << setfill('0') << (int)outputdataTotalCurrent[i + 8] - 0x33;
            ss3TotalCurrent << hex << setw(2) << setfill('0') << (int)outputdataTotalCurrent[i + 6] - 0x33;

            int hexnTotalCurrent = (int)outputdataTotalCurrent[i + 7] - 0x33; // 2位16进制数

            char str[5]; // 要赋值的string类型变量，长度应足够存储转换后的字符串
            char str1[5];
            // 使用位运算取出第一位，并将其转换为字符串格式
            sprintf(str, "%.1X", (hexnTotalCurrent >> 4) & 0x0F);

            // 输出结果
            // printf("The value of str is: %s\n", str);

            sprintf(str1, "%.1X", hexnTotalCurrent & 0x0F);

            string elecCurrent = ss2TotalCurrent.str() + str + "." + str1 + ss3TotalCurrent.str();
            // string elecCurrent = ss2TotalCurrent.str() + "." + ss3TotalCurrent.str();
            TotalCurrent = elecCurrent.c_str();
        }
    }
    Serial.println(" ");

    // delete[] outputdataTotalCurrent;
}
/// @brief 读取有功功率
void readdata::ReadActivepower()
{
    // 有功功率
    // FE FE FE 68 02 02 00 03 20 20 68 11 04 33 33 36 35 FD 16
    //unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x33, 0x36, 0x35, 0xFD, 0x16};

    // 莲花路店2号表
    //
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x03, 0x29, 0x18, 0x11, 0x12, 0x22, 0x68, 0x11, 0x04, 0x33, 0x33, 0x36, 0x35, 0x3F, 0x16};
    unsigned char *bytePointerActivepower = data;
    unsigned char *outputdataActivepower;
    outputdataActivepower = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerActivepower, outputdataActivepower, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataActivepower[i] == 0x91)
        {
            stringstream ss1Activepower;
            stringstream ss2Activepower;
            stringstream ss3Activepower;
            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1Activepower << hex << setw(2) << setfill('0') << outputdataActivepower[i + 8] - 0x33;
            ss2Activepower << hex << setw(2) << setfill('0') << outputdataActivepower[i + 7] - 0x33;
            ss3Activepower << hex << setw(2) << setfill('0') << outputdataActivepower[i + 6] - 0x33;

            string elecActivepower = ss1Activepower.str() + "." + ss2Activepower.str() + ss3Activepower.str();
            Activepower = elecActivepower.c_str();
        }
    }
    Serial.println(" ");

    // delete[] outputdataActivepower;
}

/// @brief 读取视在功率
void readdata::ReadApparentpower()
{
    // 视在功率
    // FE FE FE 68 02 02 00 03 20 20 68 11 04 33 33 38 35 FF 16
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x33, 0x38, 0x35, 0xFF, 0x16};


    unsigned char *bytePointerApparentpower = data;
    unsigned char *outputdataApparentpower;
    outputdataApparentpower = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerApparentpower, outputdataApparentpower, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataApparentpower[i] == 0x91)
        {
            stringstream ss1Apparentpower;
            stringstream ss2Apparentpower;
            stringstream ss3Apparentpower;
            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1Apparentpower << hex << setw(2) << setfill('0') << outputdataApparentpower[i + 8] - 0x33;
            ss2Apparentpower << hex << setw(2) << setfill('0') << outputdataApparentpower[i + 7] - 0x33;
            ss3Apparentpower << hex << setw(2) << setfill('0') << outputdataApparentpower[i + 6] - 0x33;

            string elecApparentpower = ss1Apparentpower.str() + "." + ss2Apparentpower.str() + ss3Apparentpower.str();
            Apparentpower = elecApparentpower.c_str();
        }
    }
    Serial.println(" ");

    // delete[] outputdataApparentpower;
}
/// @brief 读取零线电流
void readdata::ReadNeutralwireCurrent()
{
    // 电压
    // FEFEFE 68 02 02 00 03 20 20 68 11 04 33 34 34 35 FC 16
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0xFC, 0x16};
    unsigned char *bytePointer = data;
    unsigned char *outputdata;
    outputdata = new unsigned char[sizeof(data)];
    reverseBytes(bytePointer, outputdata, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        Serial.print(outputdata[i], HEX);
        Serial.print(" ");
    }
    Serial.println(" ");

   // delete[] outputdata;
}
/// @brief 读取电网频率
void readdata::ReadGridFrequency()
{
    // 电网频率
    // FE FE FE 68 02 02 00 03 20 20 68 11 04 35 33 b3 35 7C 16

    //unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x35, 0x33, 0xB3, 0x35, 0x7C, 0x16};


    // 莲花路店2号表
    //
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x03, 0x29, 0x18, 0x11, 0x12, 0x22, 0x68, 0x11, 0x04, 0x35, 0x33, 0xB3, 0x35, 0xBE, 0x16};
    unsigned char *bytePointerGridFrequency = data;
    unsigned char *outputdataGridFrequency;
    outputdataGridFrequency = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerGridFrequency, outputdataGridFrequency, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataGridFrequency[i] == 0x91)
        {
            stringstream ss1GridFrequency;
            stringstream ss2GridFrequency;

            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1GridFrequency << hex << setw(2) << setfill('0') << outputdataGridFrequency[i + 7] - 0x33;
            ss2GridFrequency << hex << setw(2) << setfill('0') << outputdataGridFrequency[i + 6] - 0x33;

            string elecGridFrequency = ss1GridFrequency.str() + "." + ss2GridFrequency.str();
            GridFrequency = elecGridFrequency.c_str();
        }
    }
    Serial.println(" ");

    //delete[] outputdataGridFrequency;
}

/// @brief 读取表内温度
void readdata::ReadMeterInternalTemperature()
{
    // 表内温度
    // FE FE FE 68 02 02 00 03 20 20 68 11 04 3A 33 b3 35 81 16

    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x3A, 0x33, 0xB3, 0x35, 0x81, 0x16};
    unsigned char *bytePointerMeterInternalTemperature = data;
    unsigned char *outputdataMeterInternalTemperature;
    outputdataMeterInternalTemperature = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerMeterInternalTemperature, outputdataMeterInternalTemperature, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataMeterInternalTemperature[i] == 0x91)
        {
            stringstream ss1MeterInternalTemperature;

            int hexn = (int)outputdataMeterInternalTemperature[i + 6] - 0x33; // 2位16进制数
            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1MeterInternalTemperature << hex << setw(2) << setfill('0') << outputdataMeterInternalTemperature[i + 7] - 0x33;

            char str[5]; // 要赋值的string类型变量，长度应足够存储转换后的字符串
            char str1[5];
            // 使用位运算取出第一位，并将其转换为字符串格式
            sprintf(str, "%.1X", (hexn >> 4) & 0x0F);

            // 输出结果
            // printf("The value of str is: %s\n", str);

            sprintf(str1, "%.1X", hexn & 0x0F);

            string elecMeterInternalTemperature = ss1MeterInternalTemperature.str() + str + "." + str1;
            MeterInternalTemperature = elecMeterInternalTemperature.c_str();
        }
    }
    Serial.println(" ");

    //delete[] outputdataMeterInternalTemperature;
}

/// @brief 读取内部电池电压
void readdata::ReadClockBatteryVoltage()
{
    // 内部电池电压
    // FE FE FE 68 02 02 00 03 20 20 68 11 04 3B 33 b3 35 82 16
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x3B, 0x33, 0xB3, 0x35, 0x82, 0x16};
    unsigned char *bytePointerClockBatteryVoltage = data;
    unsigned char *outputdataClockBatteryVoltage;
    outputdataClockBatteryVoltage = new unsigned char[sizeof(data)];
    reverseBytes(bytePointerClockBatteryVoltage, outputdataClockBatteryVoltage, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
        if (outputdataClockBatteryVoltage[i] == 0x91)
        {
            stringstream ss1ClockBatteryVoltage;
            stringstream ss2ClockBatteryVoltage;

            // ss << mp3["Onebit"] << mp3["TwoBit"] << mp3["ThreeBit"] << mp3["FourBit"];

            ss1ClockBatteryVoltage << hex << setw(2) << setfill('0') << outputdataClockBatteryVoltage[i + 7] - 0x33;
            ss2ClockBatteryVoltage << hex << setw(2) << setfill('0') << outputdataClockBatteryVoltage[i + 6] - 0x33;

            string elecClockBatteryVoltage = ss1ClockBatteryVoltage.str() + "." + ss2ClockBatteryVoltage.str();
            ClockBatteryVoltage = elecClockBatteryVoltage.c_str();
        }
    }
    Serial.println(" ");

   // delete[] outputdataClockBatteryVoltage;
}

/// @brief 内部电池工作时间
void readdata::ReadInternalBatteryOperatingTime()
{
    // 电压
    // FEFEFE 68 02 02 00 03 20 20 68 11 04 33 34 34 35 FC 16
    unsigned char data[] = {0xFE, 0xFE, 0xFE, 0x68, 0x02, 0x02, 0x00, 0x03, 0x20, 0x20, 0x68, 0x11, 0x04, 0x33, 0x34, 0x34, 0x35, 0xFC, 0x16};
    unsigned char *bytePointer = data;
    unsigned char *outputdata;
    outputdata = new unsigned char[sizeof(data)];
    reverseBytes(bytePointer, outputdata, sizeof(data));
    for (int i = 0; i < sizeof(data); i++)
    {
    }
    Serial.println(" ");

    //delete[] outputdata;
}

String readdata::GetTotalPower()
{
    return TotalPower;
}
String readdata::GetTotalVoltage()
{
    return TotalVoltage;
}
String readdata::GetTotalCurrent()
{
    return TotalCurrent;
}
String readdata::GetActivepower()
{
    return Activepower;
}
String readdata::GetApparentpower()
{
    return Apparentpower;
}
String readdata::GetNeutralwireCurrent()
{
    return NeutralwireCurrent;
}
String readdata::GetGridFrequency()
{
    return GridFrequency;
}
String readdata::GetMeterInternalTemperature()
{
    return MeterInternalTemperature;
}
String readdata::GetClockBatteryVoltage()
{
    return ClockBatteryVoltage;
}
String readdata::GetInternalBatteryOperatingTime()
{
    return InternalBatteryOperatingTime;
}
