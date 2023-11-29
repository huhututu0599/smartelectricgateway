#include "conncetwifi.h" //声明头文件

void connectWiFi()
{
    rwConf red;

    red.ReadIPInfoConf();

    WiFi.setHostname("PGSH Sensor");
    // 设置工作模式为无线终端模式
    WiFi.mode(WIFI_STA);

    WiFi.begin(red.GETWiFiSSID().c_str(), red.GETWiFiPassword().c_str());
    
    if (!red.GETDhcpinfo())
    {
        Serial.println("进入固定ip配置逻辑");

        // ReadIPInfoConf();

        unsigned char int_ip[4];
        unsigned char int_subnetmask[4];
        unsigned char int_gateway[4];
        unsigned char int_dns1[4];
        unsigned char int_dns2[4];

        IpToIne(int_ip, (char *)red.GetIPInfo().c_str());
        IpToIne(int_subnetmask, (char *)red.GetSubnetmaskinfo().c_str());
        IpToIne(int_gateway, (char *)red.GetGateWay_info().c_str());
        IpToIne(int_dns1, (char *)red.GETDns1Info().c_str());
        IpToIne(int_dns2, (char *)red.GETDns2Info().c_str());

        IPAddress local_IP(int_ip[0], int_ip[1], int_ip[2], int_ip[3]);
        IPAddress subnet(int_subnetmask[0], int_subnetmask[1], int_subnetmask[2], int_subnetmask[3]);
        IPAddress gateway(int_gateway[0], int_gateway[1], int_gateway[2], int_gateway[3]);
        IPAddress primaryDNS(int_dns1[0], int_dns1[1], int_dns1[2], int_dns1[3]);   // optional
        IPAddress secondaryDNS(int_dns2[0], int_dns2[1], int_dns2[2], int_dns2[3]); // optional

        Serial.println("开始执行配置静态ip");
        if (WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS))
        {
            Serial.println("STA Success to configure");
        }
        else
        {
            Serial.println("STA Failed to configure");
        }
        Serial.println("配置完成");
        delay(1000); // 延迟1秒
    }

    int i1 = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
        // connectWifi();
        i1 += 1;
        if (i1 >= 30)
        {
            ESP.restart();
        }
    }
    i1 = 0;
    Serial.println("");
    Serial.println("WiFi Connected!");
    Serial.println(WiFi.localIP());
    Serial.println(WiFi.subnetMask());

    Serial.println(WiFi.gatewayIP());
    Serial.println(WiFi.dnsIP());

    Serial.println(WiFi.RSSI());
    Serial.println("");
}
