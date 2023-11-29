#ifndef IP_CONVERT_H
#define IP_CONVERT_H
//进行宏定义时为了防止重复引用头文件而引起重定义错误
#include <Arduino.h>
#include <cstring>
void IpToIne(unsigned char *int_out, char *ip_in);

#endif