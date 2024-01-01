#include "readdata.h"
#include "spfile.h"
#include <stdio.h>

#include <cstring>

// #include "conncetwifi.h"
// #include "mqttmsg.h"
// #include "conftime.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <ArduinoJson.h>

#include <Ticker.h>
#include "dltcrccheck.h"
#include <vector>
using namespace std;

// Ticker ticker;
// readdata rs;
// MqttMethod mqmsg;
//
// confTime cft;
// int count1; // Ticker计数用变量
//
// void tickerCount()
//{
//     count1++;
// }
// spfile sp;
dltcrccheck dc;
void setup()
{
    Serial.begin(115200);
    // ticker.attach(1, tickerCount);
    //  connectWiFi();
    //  mqmsg.connectMQTTServer();

    // rs.OneFstSetUp();

    // if (!SD.begin())
    // {
    //     Serial.println("Card Mount Failed");
    //     return;
    // }
    // uint8_t cardType = SD.cardType();

    // if (cardType == CARD_NONE)
    // {
    //     Serial.println("No SD card attached");
    //     return;
    // }

    // Serial.print("SD Card Type: ");
    // if (cardType == CARD_MMC)
    // {
    //     Serial.println("MMC");
    // }
    // else if (cardType == CARD_SD)
    // {
    //     Serial.println("SDSC");
    // }
    // else if (cardType == CARD_SDHC)
    // {
    //     Serial.println("SDHC");
    // }
    // else
    // {
    //     Serial.println("UNKNOWN");
    // }

    // sp.writeFile(SD, "/hello.txt", "Hello ");
    // sp.appendFile(SD, "/hello.txt", "World!\n");

    Serial.println("123");
    // Serial.println(dc.calculateChecksum("6802020003202068110433343435"),HEX);
    // Serial.println(dc.makeCheck("6802020003202068110433343435"));
    // Serial.println(dc.makeCheck("66666666"));

    Serial.println("↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓");
    int x1;
    x1 = dc.calculateChecksum("6802020003202068110433343435");
    Serial.println(x1);
    Serial.println("↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑");
    // dc.splitStringToHex("6802020003202068110433343435");
    // std::vector<uint8_t> hexArray = dc.splitStringToHex("6802020003202068110433343435");

    vector<uint8_t> hexc = dc.stringToByteArray("6802020003202068110433343435");
    for (size_t i = 0; i < hexc.size(); i++)
    {
        Serial.println(static_cast<int>(hexc[i]), HEX);
    }

    //    for (uint8_t value : hexArray) {
    //        Serial.println(static_cast<int>(value));
    //
    //        //std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(value) << " ";
    //
    //    }
    // std::cout << std::endl;

}

void loop()
{

    // Serial.println(cft.ReadConftime());
    // delay(2000);
    // sp.appendFile(SD, "/hello.txt", "\n");
    // sp.appendFile(SD, "/hello.txt", cft.ReadConftime().c_str());
    // delay(1000);

    // delay(7000);

    //     rs.ReadTotalVoltage();
    //     Serial.println("电压是：");
    //     Serial.println(rs.GetTotalVoltage());
    //     Serial.println("----------------");

    //     rs.ReadTotalPower();
    //     Serial.println("总功耗是：");
    //     Serial.println(rs.GetTotalPower());

    //     rs.ReadTotalCurrent();
    //     Serial.println("电流是：");
    //     Serial.println(rs.GetTotalCurrent());

    //     rs.ReadActivepower();
    //     Serial.println("有功功率是：");
    //     Serial.println(rs.GetActivepower());

    //     rs.ReadApparentpower();
    //     Serial.println("视在功率是：");
    //     Serial.println(rs.GetApparentpower());

    //     rs.ReadGridFrequency();
    //     Serial.println("电网频率是：");
    //     Serial.println(rs.GetGridFrequency());

    //     // rs.ReadMeterInternalTemperature();
    //     // Serial.println("表内温度是：");
    //     // Serial.println(rs.GetMeterInternalTemperature());

    //     // rs.ReadClockBatteryVoltage();
    //     // Serial.println("内部电池电压：");
    //     // Serial.println(rs.GetClockBatteryVoltage());

    //     StaticJsonDocument<1024> doc51;
    //     doc51["localtime"] = cft.ReadConftime();
    //     doc51["Phase"] = "Single";

    //     doc51["Total"]["TotalPower"] = rs.GetTotalPower();
    //     doc51["Total"]["TotalVoltage"] = rs.GetTotalVoltage();
    //     doc51["Total"]["TotalCurrent"] = rs.GetTotalCurrent();
    //     doc51["Total"]["Activepower"] = rs.GetActivepower();
    //     doc51["Total"]["Apparentpower"] = rs.GetApparentpower();

    //     doc51["GridFrequency"] = rs.GetGridFrequency();
    //     doc51["MeterInternalTemperature"] = rs.GetMeterInternalTemperature();
    //     doc51["ClockBatteryVoltage"] = rs.GetClockBatteryVoltage();
    //     String jsonString;

    //     serializeJson(doc51, jsonString);
    // //String jsonString = "{\"localtime\":\"1970-01-01 08:00:25\",\"Phase\":\"Single\",\"Total\":{\"TotalPower\":\"000005.55\",\"TotalVoltage\":\"229.5\",\"TotalCurrent\":\"000.000\",\"Activepower\":\"00.0000\",\"Apparentpower\":\"00.0000\"},\"GridFrequency\":\"50.00\",\"MeterInternalTemperature\":\"020.9\",\"ClockBatteryVoltage\":\"03.56\"}";
    //     Serial.println(jsonString);

    //     // String jsonString = "666";

    //     if (mqmsg.GetMqttConnectState())
    //     {
    //         if (count1 >= 20)
    //         {
    //             mqmsg.publishMessageAll(jsonString);
    //             count1 = 0;
    //         }
    //         mqmsg.MqttLoopMethod();
    //     }
    //     else
    //     {
    //         mqmsg.connectMQTTServer();
    //     }
}
