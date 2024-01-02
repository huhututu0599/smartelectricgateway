#ifndef READ_ELEC_DATA_H
#define READ_ELEC_DATA_H

#define FIRSTCOMMAND "FE FE FE 68"
#define ENDCOMAND "16"

class readelecdata
{
public:
    void SetInit();
    void reverseBytes(unsigned char *input, unsigned char *output, int size);
    void ReadTotalPower(const std::string &input);

    String GetElecTotalPower();
    String GetElecTotalVoltage();
    String GetElecTotalCurrent();
    String GetElecActivepower();
    String GetElecApparentpower();
    String GetNeutralwireCurrent();
    String GetElecGridFrequency();
    String GetElecMeterInternalTemperature();
    String GetElecClockBatteryVoltage();
    String GetElecInternalBatteryOperatingTime();

private:
    String ElecTotalPower, ElecTotalVoltage, ElecTotalCurrent, ElecActivepower, ElecApparentpower, ElecNeutralwireCurrent, ElecGridFrequency, ElecMeterInternalTemperature, ElecClockBatteryVoltage, ElecInternalBatteryOperatingTime;
};

#endif