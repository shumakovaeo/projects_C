#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

long long parse_signed_number(const char** str, int width, int* ptr_flag);
unsigned long long parse_unsigned_number(const char** str, int base, int width,
                                         int* ptr_flag);
double parse_float_number(const char** str, int width, int* ptr_flag);
char* parse_word(const char** str, int width);
int specifiers_numb(const char** src, const char* format, va_list* args,
                    int width, int suppress, int assigned, int len);
int specifiers_char_str(const char** src, const char* format, va_list* args,
                        int width, int suppress, int assigned, int len);
int uslov(const char* src, const char* format);
int w_width(const char** format);
char l_len(const char** format);
int literal(const char** src, const char** format);
int s21_sscanf(const char* str, const char* format, ...);

#endif
