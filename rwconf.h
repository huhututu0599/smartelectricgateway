#ifndef RW_CONF_H
#define RW_CONF_H
// 进行宏定义时为了防止重复引用头文件而引起重定义错误
#include <Arduino.h>

#include "SPIFFS.h"
#include "FS.h"
#include <string.h>
#include <ArduinoJson.h>
#include <iostream>

using namespace std;
class rwConf
{
public:
  rwConf();
  /// brief 读取mqtt配置信息
  void ReadMqttConf();
  void ReadConfStat();
  void ReadWorkConf();
  void ReadElecConf();
  void ReadIPInfoConf();
  void ReadLic();

  void SaveWorkConf(String sendmod, int mxnum, int mxAfrequency, int shtnum, int shtAfrequency, int fstnum, int fstAfrequency);
  void SaveIPConf(String wifi_ssid, String wifi_password, bool dhcp_info, String IpInfo, String Subnetmask_info, String Gateway_info, String Dns1_info, String Dns2_info);
  void SaveSatatConf(int conf_state);
  void SaveMqConf(String mqtt_address, int mqtt_port, int mqtt_pub_frequency, String mqtt_username, String mqtt_password, bool MQTT_Secret_Check_enable);
  void SaveLic(String localLic, String OneShtLic, String TwoShtLic);
  void SaveElecConf(String Enable_Phase, String Enable_electricity_meter_number, String Enable_TotalPower, String Enable_TotalVoltage, String Enable_TotalCurrent, String Enable_Activepower, String Enable_Apparentpower, String Enable_GridFrequency, String Enable_MeterInternalTemperature, String Enable_ClockBatteryVoltage);

  const char *GetMqttAddressV();
  String GetMqttUsernameV();
  String GetMqttPasswordV();
  bool GetMQTT_Secret_Check_enable();

  int GETMQTTPort();
  int GETMQTTPubFrequency();

  String GETWiFiSSID();
  String GETWiFiPassword();
  bool GETDhcpinfo();
  String GetIPInfo();
  String GetSubnetmaskinfo();
  String GetGateWay_info();
  String GETDns1Info();
  String GETDns2Info();

  String GETSendmod();

  int GETmxnum();
  int GetMxFrequency();
  int Getshtnum();
  int GetShtFrequency();
  int Getfstnum();
  int Getfstfrequency();
  int GetConfState();

  String GetLocalLic();
  String GetOneShtLic();
  String GetTwoShtLic();

  String GetPhase();
  String Get_electricity_meter_number();

  bool GetTotalPower();
  bool GetTotalVoltage();
  bool GetTotalCurrent();
  bool GetActivepower();
  bool GetApparentpower();
  bool GetGridFrequency();
  bool GetMeterInternalTemperature();
  bool GetClockBatteryVoltage();

private:
  /// @brief  mqtt地址局部变量
  const char *MQTT_Address;
  String MQTT_username;
  String MQTT_password;

  int MQTT_Port, MQTT_Pub_Frequency;

  ///@brief wifi信息局部变量
  bool Dhcp_info, MQTT_Secret_Check_enable;
  String Wifi_ssid, Wifi_password, Ip_info, Subnetmask_info, Gateway_info, Dns1_info, Dns2_info;

  ///@brief workmod信息局部变量
  String Sendmod;
  int mxnum, mxfrequency, shtnum, shtfrequency, fstnum, fstfrequency;

  /// @brief 配置信息变量
  int Conf_State;

  String LocalLic, OneShtLic, TwoShtLic;

  /// @brief 读取电量的部分配置信息
  String Phase, electricity_meter_number;
  bool TotalPower, TotalVoltage, TotalCurrent, Activepower, Apparentpower, GridFrequency, MeterInternalTemperature, ClockBatteryVoltage;
};

#endif
