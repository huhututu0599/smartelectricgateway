#include "rwconf.h"

/** brief brief description
 *
 */
rwConf::rwConf()
{
  if (SPIFFS.begin())
  { // 启动闪存文件系统
    Serial.println("SPIFFS Started.");
  }
  else
  {
    Serial.println("SPIFFS Failed to Start.");
  }
}

// 从配置文件中读取MQTT配置信息
void rwConf::ReadMqttConf()
{
  // 建立DynamicJsonDocument对象
  // const size_t capacity = JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(9) + 80;
  const size_t capacity4 = 1024;
  DynamicJsonDocument doc4(capacity4);

  // 从闪存文件系统中读取即将解析的json文件
  File file4 = SPIFFS.open("/mq_conf.json", "r");

  // 反序列化数据
  deserializeJson(doc4, file4);

  //   char *mqtt_address = doc4["mqtt"]["mqtt_address"];
  MQTT_Address = doc4["mqtt"]["mqtt_address"];

  const char *mq_username = doc4["mqtt"]["mqtt_username"];
  MQTT_username = (String)mq_username;

  const char *mq_password = doc4["mqtt"]["mqtt_password"];
  MQTT_password = (String)mq_password;

  MQTT_Secret_Check_enable = doc4["mqtt"]["MQTT_Secret_Check_enable"];

  MQTT_Port = doc4["mqtt"]["mqtt_port"];
  MQTT_Pub_Frequency = doc4["mqtt"]["mqtt_pub_frequency"];

  Serial.println(MQTT_Address);
  Serial.println(MQTT_username);
  Serial.println(MQTT_password);

  Serial.println(MQTT_Port);
  Serial.println(MQTT_Pub_Frequency);

  file4.close();

  // return x;
}

/// @brief 读取配置状态
void rwConf::ReadConfStat()
{

  Serial.println("-----程序进入读取状态信息信息文件逻辑----");

  // 建立DynamicJsonDocument对象
  // const size_t capacity = JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(9) + 80;
  const size_t capacity2 = 100;
  DynamicJsonDocument doc2(capacity2);

  // 从闪存文件系统中读取即将解析的json文件
  File file2 = SPIFFS.open("/state_conf.json", "r");

  // 反序列化数据
  deserializeJson(doc2, file2);

  // 配置文件json几个json指针定义
  Conf_State = doc2["confstat"]["state"];

  file2.close();
  Serial.println("↓↓↓↓↓↓↓↓↓↓↓设备状态信息↓↓↓↓↓↓↓↓↓↓↓");
  Serial.println(Conf_State);
  Serial.println("↑↑↑↑↑↑↑↑↑↑↑设备状态信息↑↑↑↑↑↑↑↑↑↑");
}

void rwConf::ReadIPInfoConf()
{

  Serial.println("-----程序进入读取IP信息文件逻辑----");

  // 建立DynamicJsonDocument对象
  // const size_t capacity = JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(9) + 80;
  const size_t capacity1 = 1024;
  DynamicJsonDocument doc1(capacity1);

  // 从闪存文件系统中读取即将解析的json文件
  File file1 = SPIFFS.open("/wifi_conf.json", "r");

  // 反序列化数据
  deserializeJson(doc1, file1);

  const char *wf_ssid = doc1["wifi_ssid"];
  Wifi_ssid = (String)wf_ssid;

  const char *wf_password = doc1["wifi_password"];
  Wifi_password = (String)wf_password;

  Serial.println(Wifi_ssid);
  Serial.println(Wifi_password);

  Dhcp_info = doc1["dhcpinfo"];

  const char *ipinfo = doc1["ipinfo"];
  Ip_info = (String)ipinfo;

  const char *sbmaskinfo = doc1["subnetmaskinfo"];
  Subnetmask_info = (String)sbmaskinfo;

  const char *gtinfo = doc1["gatewayinfo"];
  Gateway_info = (String)gtinfo;

  const char *dns1info = doc1["dns1info"];
  Dns1_info = (String)dns1info;

  const char *dns2info = doc1["dns2info"];
  Dns2_info = (String)dns2info;

  file1.close();
}

/// @brief 读取工作模式配置文件
void rwConf::ReadWorkConf()
{
  Serial.println("-----程序进入读取work配置文件逻辑----");
  // 建立DynamicJsonDocument对象
  // const size_t capacity = JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(9) + 80;
  const size_t capacity3 = 1024;
  DynamicJsonDocument doc3(capacity3);

  // 从闪存文件系统中读取即将解析的json文件
  File file3 = SPIFFS.open("/work_conf.json", "r");

  Serial.println(file3);
  // 反序列化数据
  deserializeJson(doc3, file3);

  const char *sedmod = doc3["workmod"]["sendmod"];
  Sendmod = (String)sedmod;
  Serial.println(Sendmod);
  mxnum = doc3["mx"]["num"];
  mxfrequency = doc3["mx"]["Afrequency"];

  shtnum = doc3["sht"]["num"];
  shtfrequency = doc3["sht"]["Afrequency"];

  fstnum = doc3["fst"]["num"];
  fstfrequency = doc3["fst"]["Afrequency"];

  file3.close();
}

/// @brief 读取本机存储的lic
void rwConf::ReadLic()
{

  const size_t capacityLic = 1024;
  DynamicJsonDocument docLic(capacityLic);

  // 从闪存文件系统中读取即将解析的json文件
  File fileLic = SPIFFS.open("/lic.json", "r");

  // 反序列化数据
  deserializeJson(docLic, fileLic);

  const char *llic = docLic["local_lic"];
  LocalLic = (String)llic;

  const char *oneSensorLic = docLic["Sensor_lic"]["One"];
  OneShtLic = (String)oneSensorLic;

  const char *TwoSensorLic = docLic["Sensor_lic"]["Two"];
  TwoShtLic = (String)TwoSensorLic;

  fileLic.close();
}

/// @brief 读取本机电表需要读取的数据的状态
void rwConf::ReadElceConf()
{

  const size_t capacityLic = 1024;
  DynamicJsonDocument docElec(capacityLic);

  // 从闪存文件系统中读取即将解析的json文件
  File fileElec = SPIFFS.open("/elec_conf.json", "r");

  // 反序列化数据
  deserializeJson(docElec, fileElec);

  const char *Elce_Phase = docElec["Phase"];
  Elce_Phase = (String)Elce_Phase;

  const char *oneSensorLic = docElec["Sensor_lic"]["One"];
  OneShtLic = (String)oneSensorLic;

  const char *TwoSensorLic = docElec["Sensor_lic"]["Two"];
  TwoShtLic = (String)TwoSensorLic;

  fileElec.close();
}


void rwConf::SaveWorkConf(String sendmod, int mxnum, int mxAfrequency, int shtnum, int shtAfrequency, int fstnum, int fstAfrequency)
{
  StaticJsonDocument<1024> doc31;

  doc31["workmod"]["sendmod"] = sendmod;

  doc31["mx"]["num"] = mxnum;
  doc31["mx"]["Afrequency"] = mxAfrequency;

  doc31["sht"]["num"] = shtnum;
  doc31["sht"]["Afrequency"] = shtAfrequency;

  doc31["fst"]["num"] = fstnum;
  doc31["fst"]["Afrequency"] = fstAfrequency;

  File configworkFile = SPIFFS.open("/work_conf.json", "w");
  serializeJson(doc31, configworkFile);
  configworkFile.close();
}

void rwConf::SaveIPConf(String wifi_ssid, String wifi_password, bool dhcp_info, String IpInfo, String Subnetmask_info, String Gateway_info, String Dns1_info, String Dns2_info)
{

  StaticJsonDocument<1024> doc11;

  doc11["wifi_ssid"] = wifi_ssid;
  doc11["wifi_password"] = wifi_password;

  doc11["dhcpinfo"] = dhcp_info;

  doc11["ipinfo"] = IpInfo;

  // 配置文件json几个json指针定义
  doc11["subnetmaskinfo"] = Subnetmask_info;

  // 配置文件json几个json指针定义
  doc11["gatewayinfo"] = Gateway_info;

  // 配置文件json几个json指针定义
  doc11["dns1info"] = Dns1_info;

  // 配置文件json几个json指针定义
  doc11["dns2info"] = Dns2_info;

  File configIPFile = SPIFFS.open("/wifi_conf.json", "w");
  serializeJson(doc11, configIPFile);
  configIPFile.close();
}

void rwConf::SaveSatatConf(int conf_state)
{
  StaticJsonDocument<1024> doc21;
  doc21["confstat"]["state"] = conf_state;
  File configstatFile = SPIFFS.open("/state_conf.json", "w");
  serializeJson(doc21, configstatFile);
  configstatFile.close();
}

void rwConf::SaveMqConf(String mqtt_address, int mqtt_port, int mqtt_pub_frequency, String mqtt_username, String mqtt_password, bool MQTT_Secret_Check_enable)
{
  StaticJsonDocument<1024> doc41;
  doc41["mqtt"]["mqtt_address"] = mqtt_address;
  doc41["mqtt"]["mqtt_username"] = mqtt_username;
  doc41["mqtt"]["mqtt_password"] = mqtt_password;

  doc41["mqtt"]["mqtt_port"] = mqtt_port;
  doc41["mqtt"]["mqtt_pub_frequency"] = mqtt_pub_frequency;
  doc41["mqtt"]["MQTT_Secret_Check_enable"] = MQTT_Secret_Check_enable;

  File configMqFile = SPIFFS.open("/mq_conf.json", "w");
  serializeJson(doc41, configMqFile);
  configMqFile.close();
}

/// @brief 将lic保存到内存
/// @param localLic   主机Lic
/// @param OneShtLic  探头1Lic
/// @param TwoShtLic  探头2Lic
void rwConf::SaveLic(String localLic, String OneShtLic, String TwoShtLic)
{
  StaticJsonDocument<1024> doc51;
  doc51["local_lic"] = localLic;
  doc51["Sensor_lic"]["One"] = OneShtLic;
  doc51["Sensor_lic"]["Two"] = TwoShtLic;

  File configLicFile = SPIFFS.open("/lic.json", "w");
  serializeJson(doc51, configLicFile);
  configLicFile.close();
}

/// @brief 将Elc保存到内存
/// @param Enable_electricity_meter_number;
/// @param Enable_TotalPower;
/// @param Enable_TotalVoltage;
/// @param Enable_TotalCurrent;
/// @param Enable_Activepower;
/// @param Enable_Apparentpower;
/// @param Enable_GridFrequency;
/// @param Enable_MeterInternalTemperature;
/// @param Enable_ClockBatteryVoltage;
void rwConf::SaveElecConf(String Enable_Phase, String Enable_electricity_meter_number, String Enable_TotalPower, String Enable_TotalVoltage, String Enable_TotalCurrent, String Enable_Activepower, String Enable_Apparentpower, String Enable_GridFrequency, String Enable_MeterInternalTemperature, String Enable_ClockBatteryVoltage)
{
  StaticJsonDocument<1024> doc61;
  doc61["electricity_meter_number"] = Enable_electricity_meter_number;
  doc61["Enable_TotalPower"] = Enable_TotalPower;
  doc61["Enable_TotalVoltage"] = Enable_TotalVoltage;
  doc61["Enable_TotalCurrent"] = Enable_TotalCurrent;
  doc61["Enable_Activepower"] = Enable_Activepower;
  doc61["Enable_Apparentpower"] = Enable_Apparentpower;
  doc61["Enable_GridFrequency"] = Enable_GridFrequency;
  doc61["Enable_MeterInternalTemperature"] = Enable_MeterInternalTemperature;
  doc61["Enable_ClockBatteryVoltage"] = Enable_ClockBatteryVoltage;

  File configEleFile = SPIFFS.open("/elec_conf.json", "w");
  serializeJson(doc61, configEleFile);
  configEleFile.close();
}

/// @brief 将mqtt地址通过方法返回
/// @return mqtt地址
const char *rwConf::GetMqttAddressV()
{
  return MQTT_Address;
}

/// @brief 将mqtt账号通过方法返回
/// @return mqtt账号
String rwConf::GetMqttUsernameV()
{
  return MQTT_username;
}

/// @brief 将mqtt密码通过方法返回
/// @return mqtt密码
String rwConf::GetMqttPasswordV()
{
  return MQTT_password;
}

/// @brief 将是否启用mqtt账号密码通过方法返回
/// @return 是否启用
bool rwConf::GetMQTT_Secret_Check_enable()
{
  return MQTT_Secret_Check_enable;
}

/// @brief 将mqtt端口通过方法返回
/// @return mqtt端口
int rwConf::GETMQTTPort()
{
  return MQTT_Port;
}

/// @brief 将mqtt发送频率通过方法返回
/// @return mqtt发送频率
int rwConf::GETMQTTPubFrequency()
{
  return MQTT_Pub_Frequency;
}

/// @brief 将wifi ssid通过方法返回
/// @return wifi ssid
String rwConf::GETWiFiSSID()
{
  return Wifi_ssid;
}

/// @brief 将wifi密码通过方法返回
/// @return wifi 密码
String rwConf::GETWiFiPassword()
{
  return Wifi_password;
}

/// @brief 将dhcp信息通过方法返回
/// @return dhcp信息
bool rwConf::GETDhcpinfo()
{
  return Dhcp_info;
}

/// @brief 将ip信息通过方法返回
/// @return  ip信息
String rwConf::GetIPInfo()
{
  return Ip_info;
}

/// @brief 将子网掩码通过方法返回
/// @return 子网掩码
String rwConf::GetSubnetmaskinfo()
{
  return Subnetmask_info;
}

/// @brief 将gateway信息通过方法返回
/// @return  gateway
String rwConf::GetGateWay_info()
{
  return Gateway_info;
}

/// @brief 将dns1信息通过方法返回
/// @return dns1信息
String rwConf::GETDns1Info()
{
  return Dns1_info;
}

/// @brief 将dns2信息通过方法返回
/// @return  dns2信息
String rwConf::GETDns2Info()
{
  return Dns2_info;
}

/// @brief 将发送模式通过方法返回
/// @return 发送模式、mqtt、tcp、http
String rwConf::GETSendmod()
{
  return Sendmod;
}

/// @brief 将mx数量通过方法返回
/// @return mx数量
int rwConf::GETmxnum()
{
  return mxnum;
}

/// @brief 将mx频率通过方法返回
/// @return mx频率
int rwConf::GetMxFrequency()
{
  return mxfrequency;
}

/// @brief 将sht数量通过方法返回
/// @return sht数量
int rwConf::Getshtnum()
{
  return shtnum;
}

/// @brief 将sht频率通过方法返回
/// @return sht频率
int rwConf::GetShtFrequency()
{
  return shtfrequency;
}

/// @brief 将fst数量通过方法返回
/// @return fst数量
int rwConf::Getfstnum()
{
  return fstnum;
}

/// @brief 将fst频率通过方法返回
/// @return fst频率
int rwConf::Getfstfrequency()
{
  return fstfrequency;
}

/// @brief 将配置状态通过方法返回
/// @return 配置1、配置状态。2、工作状态
int rwConf::GetConfState()
{
  return Conf_State;
}

String rwConf::GetLocalLic()
{
  return LocalLic;
}

String rwConf::GetOneShtLic()
{
  return OneShtLic;
}

String rwConf::GetTwoShtLic()
{
  return TwoShtLic;
}
