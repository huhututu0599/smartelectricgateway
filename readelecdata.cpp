#include "readelecdata.h"

#define RE 4 // Connect RE terminal with 32 of ESP
#define DE 5 // Connect DE terminal with 33 of ESP
#include <SoftwareSerial.h>
SoftwareSerial modx(16, 17); // RX=16->RO , TX =17

void readelecdata::SetInit()
{
    // SoftwareSerial mod(16, 17); // RX=16->RO , TX =17
    Serial.println("setinit->elec");
    modx.begin(2400, SWSERIAL_8E1);
    pinMode(RE, OUTPUT);
    pinMode(DE, OUTPUT);
    Serial.println("485FST电平已准备就绪");
}