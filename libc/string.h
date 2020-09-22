#ifndef STRING_H
#define STRING_H

int backspace(char *buff);
int strlen(const char *str);
void str_append(char *buff, char chr);
void int_to_ascii(int number, char *buff);
void hex_to_ascii(int number, char *buff);
void append(char *buff, char n);
void str_rev(char *buff);
int strcmp(char *buff, char *cmp);

#endif