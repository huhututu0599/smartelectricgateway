#include "conftime.h"

// const char *ntpServer = "pool.ntp.org";
// const long gmtOffset_sec = 8 * 3600;
// const int daylightOffset_sec = 0;

 confTime::confTime(){
  //configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  configTime( 8 * 3600,0,"time.windows.com");
}

String confTime::ReadConftime(){

    struct tm timeinfo;

      getLocalTime(&timeinfo);

      String myFormat = "%Y-%m-%d %H:%M:%S"; //自定义格式
      char myStr[255] = "\0";
      Serial.println(&timeinfo);
      strftime(myStr, sizeof(myStr), myFormat.c_str(), &timeinfo);
      confTim = myStr;
    return confTim;
}

