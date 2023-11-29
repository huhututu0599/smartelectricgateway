#ifndef READ_DATA_H
#define READ_DATA_H

#include <Arduino.h>
#include <iostream>
#include <string>
#include <map>
#include <cstring>


#include <sstream>
#include <iomanip>
#include <bitset>

#include <SoftwareSerial.h>

// using namespace std;

class readdata
{

public:
   void OneFstSetUp();
   std::map<std::string, std::string> ReadDLTdata();
   void reverseBytes(unsigned char *input, unsigned char *output, int size);

   void ReadTotalPower();
   void ReadTotalVoltage();
   void ReadTotalCurrent();
   void ReadActivepower();
   void ReadApparentpower();
   void ReadNeutralwireCurrent();
   void ReadGridFrequency();
   void ReadMeterInternalTemperature();
   void ReadClockBatteryVoltage();
   void ReadInternalBatteryOperatingTime();

   String GetTotalPower();
   String GetTotalVoltage();
   String GetTotalCurrent();
   String GetActivepower();
   String GetApparentpower();
   String GetNeutralwireCurrent();
   String GetGridFrequency();
   String GetMeterInternalTemperature();
   String GetClockBatteryVoltage();
   String GetInternalBatteryOperatingTime();

   // String AccumulatePower;
private:
   String TotalPower, TotalVoltage, TotalCurrent, Activepower, Apparentpower, NeutralwireCurrent, GridFrequency, MeterInternalTemperature, ClockBatteryVoltage, InternalBatteryOperatingTime;
};

#endif
