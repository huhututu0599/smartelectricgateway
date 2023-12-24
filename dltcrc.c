#include "dltcrc.h"



String dltcrc::makeCheck(String data)
{
    if (data.empty())
    {
        return "";
    }

    int total = 0;
    int len = data.length();
    int num = 0;

    while (num < len)
    {
        String s = data.substr(num, 2);
        total += stoi(s, nullptr, 16);
        num += 2;
    }

    // Calculate mod 256
    int mod = total % 256;

    // Convert mod to hexadecimal
   oStringstream hexStream;
    hexStream << hex << mod;
    String hex = hexStream.str();

    len = hex.length();

    // If not enough length for the checksum, add leading zero
    if (len < 2)
    {
        hex = "0" + hex;
    }

    return hex + "16";
}
