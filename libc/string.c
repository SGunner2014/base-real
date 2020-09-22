#include "string.h"
#include "stdint.h"

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

void str_rev(char *s)
{
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
  {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void int_to_ascii(int n, char *buff)
{
  int i, sign;

  if ((sign = n) < 0)
    n = -n;

  i = 0;

  do
  {
    buff[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0)
    buff[i++] = '-';
  buff[i] = '\0';

  str_rev(buff);
}

void hex_to_ascii(int n, char *buff)
{
  append(buff, '0');
  append(buff, 'x');
  char zeroes = 0;

  int32_t tmp;
  int i;
  for (i = 28; i > 0; i -= 4)
  {
    tmp = (n >> i) & 0xf;
    if (tmp == 0 && zeroes == 0)
      continue;
    zeroes = 1;
    if (tmp > 0xa)
      append(buff, tmp - 0xa + 'a');
    else
      append(buff, tmp + '0');
  }
}

void append(char *buff, char n)
{
  int len = strlen(buff);
  buff[len] = n;
  buff[len + 1] = '\0';
}

int strcmp(char *buff, char *cmp)
{
  int i;
  for (i = 0; buff[i] == cmp[i]; i++)
  {
    if (buff[i] == '\0')
      return 0;
  }

  return buff[i] - cmp[i];
}