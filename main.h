#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>
#include <unistd.h>

int printf_int(va_list args);
int _strlen(char *s);
int *_strcpy(char *dest, char *src);
int printf_char(va_list val);
int printf_string(va_list val);
int _printf(const char *format, ...);

#endif
