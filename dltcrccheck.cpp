#include "dltcrccheck.h"

int dltcrccheck::calculateChecksum(const std::string &input)
{
    int sum = 0;

    // 遍历字符串中的每个字符
    for (char ch : input)
    {
        // 计算字符的ASCII值，并将其加到总和上
        sum += static_cast<unsigned char>(ch);
    }

    // 对总和取模以防止溢出
    sum %= 256;

    return sum;
}

String dltcrccheck::makeCheck(const std::string &data)
{
    if (data.empty())
    {
        return "";
    }
    String x1;
    int total = 0;
    int len = data.length();
    int num = 0;

    while (num < len)
    {
        std::string s = data.substr(num, 2);
        total += std::stoi(s, nullptr, 16);
        num += 2;
    }

    // Use 256 to find the remainder, maximum is 255 (hex FF)
    int mod = total % 256;

    // Convert the remainder to hexadecimal
    std::ostringstream hexStream;
    hexStream << std::hex << mod;

    // Get the hexadecimal string
    std::string hexx = hexStream.str();

    // If the length is less than 2, pad with 0 (assuming two-digit checksum)
    if (hexx.length() < 2)
    {
        hexx = "0" + hexx;
    }
    x1 =hexx.c_str();
    // Convert to uppercase and append "16" as in your Java code
    // return hexx + "16";
    return x1;
}



std::string dltcrccheck::packStringToHexArray(const std::string& input) {
    std::ostringstream hexStream;

    for (char c : input) {
        if (isalpha(c)) {
            // If the string contains letters, return 0xFF
            return "0xFF";
        }
        hexStream << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(c);
    }

    return hexStream.str();
}