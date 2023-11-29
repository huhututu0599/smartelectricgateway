#include "ipconvert.h"

void IpToIne(unsigned char *int_out, char *ip_in)
{
  char ip_idx = 0;
  char int_idx = 0;
  int i = 0;
  char wk_data[4] = {'\0', '\0', '\0', '\0'};
  char wk_len = strlen(ip_in);
  for (ip_idx = 0; ip_idx < wk_len; ip_idx++)
  {
    wk_data[i++] = ip_in[ip_idx];
    if ((ip_in[ip_idx] == '.') || (ip_in[ip_idx + 1] == '\0'))
    {
      i = 0;
      sscanf(wk_data, "%d", &int_out[int_idx++]);
      memset(wk_data, '\0', 4);
      continue;
    }
  }
}