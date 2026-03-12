#include "s21_common.h"

#include <stdlib.h>

void init_decimal(s21_decimal *value) {
  value->bits[0] = value->bits[1] = value->bits[2] = value->bits[3] = 0;
}

int is_zero_decimal(s21_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0);
}

int get_scale(s21_decimal decimal) {
  int scale = (decimal.bits[3] >> 16) & 0xFF;
  return scale;
}

void set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] = decimal->bits[3] & 0xFF00FFFF;
  decimal->bits[3] = decimal->bits[3] | (scale << 16);
}

int get_sign(s21_decimal decimal) {
  int sign = (decimal.bits[3] >> 31) & 0x1;
  return sign;
}

void set_sign(s21_decimal *decimal, int sign) {
  decimal->bits[3] = decimal->bits[3] & 0x7FFFFFFF;
  if (sign == 1) {
    decimal->bits[3] = decimal->bits[3] | 0x80000000;
  }
}

int is_decimal_valid(s21_decimal value) {
  int result = 1;

  int scale = get_scale(value);
  if (scale < 0 || scale > 28) {
    result = 0;
  }

  return result;
}

void decimal_to_big_decimal(s21_decimal value,
                            s21_big_decimal *value_big_decimal) {
  value_big_decimal->bits[0] = value.bits[0];
  value_big_decimal->bits[1] = value.bits[1];
  value_big_decimal->bits[2] = value.bits[2];
}

int is_big_decimal(s21_big_decimal value) {
  return value.bits[3] != 0 || value.bits[4] != 0 || value.bits[5] != 0;
}

int is_zero_big_decimal(s21_big_decimal value) {
  return (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
          value.bits[3] == 0 && value.bits[4] == 0 && value.bits[5] == 0);
}

int mul_by_10(s21_decimal *value) {
  int code_error = 0;

  s21_decimal result = {0};
  unsigned int carry = 0;

  for (int i = 0; i < 3; i++) {
    unsigned long long sum = (unsigned long long)value->bits[i] * 10 + carry;
    result.bits[i] = sum & 0xFFFFFFFFULL;
    carry = sum >> 32;
  }

  if (carry != 0) {
    code_error = 1;
  } else {
    value->bits[0] = result.bits[0];
    value->bits[1] = result.bits[1];
    value->bits[2] = result.bits[2];
  }

  return code_error;
}

int div10(s21_decimal val1, s21_decimal *s) {
  int mem = 0;
  long int temp = 0;
  for (int i = 2; i >= 0; i--) {
    temp = val1.bits[i] + mem * (MAXNUM + 1);
    mem = (int)(temp % 10);
    s->bits[i] = (int)((temp - mem) / 10);
  }
  return mem;
}

int mulk(s21_decimal val1, int k, s21_decimal *s) {
  int mem = 0;
  long int temp = 0;
  for (int i = 0; i <= 2; i++) {
    temp = (long int)val1.bits[i] * k + mem;
    s->bits[i] = (int)(temp % (MAXNUM + 1));
    mem = ((temp - s->bits[i]) / (MAXNUM + 1));
  }

  return mem;
}