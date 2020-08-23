#include "string.h"

int backspace(char *buff)
{
  int len = strlen(buff);

  if (len > 0)
  {
    buff[len - 1] = '\0';
  }

  return len;
}

int strlen(const char *str)
{
  int i = 0;

  while (str[i] != '\0')
    i++;

  return i;
}

void str_append(char *buff, char chr)
{
  int len = strlen(buff);
  buff[len] = chr;
  buff[len + 1] = '\0';
}