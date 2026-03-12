#ifndef S21_COMMON_H
#define S21_COMMON_H

#include "s21_decimal.h"

#define MAXNUM 4294967295

typedef struct {
  unsigned int bits[6];
} s21_big_decimal;

void init_decimal(s21_decimal *value);
int is_zero_decimal(s21_decimal value);
int get_scale(s21_decimal decimal);
void set_scale(s21_decimal *decimal, int scale);
int get_sign(s21_decimal decimal);
void set_sign(s21_decimal *decimal, int sign);
int is_decimal_valid(s21_decimal value);
void decimal_to_big_decimal(s21_decimal value,
                            s21_big_decimal *value_big_decimal);
int is_big_decimal(s21_big_decimal value);
int is_zero_big_decimal(s21_big_decimal value);
int mul_by_10(s21_decimal *value);
int div10(s21_decimal val1, s21_decimal *s);
int mulk(s21_decimal val1, int k, s21_decimal *s);

#endif