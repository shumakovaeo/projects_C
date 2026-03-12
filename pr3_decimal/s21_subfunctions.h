#ifndef S21_SUBFUNCTIONS_H
#define S21_SUBFUNCTIONS_H

#include "s21_common.h"
#include "s21_decimal.h"

#define MAXNUM 4294967295

// add
void add_diff_sign(s21_decimal value_1, s21_decimal value_2, s21_decimal *res);
int sub_normal(s21_decimal value_1, s21_decimal value_2, s21_decimal *res,
               s21_decimal *ostat_dec);
void sub_mantis(s21_decimal value_1, s21_decimal value_2, s21_decimal *res);
void add_mantis(s21_decimal value_1, s21_decimal value_2, s21_decimal *res,
                int *mem);
void over_mantis(s21_decimal *value, int scale);
int scale_equal_add(s21_decimal *value_1, s21_decimal *value_2,
                    int *diff_scale);
int scale_equal_sub(s21_decimal *value_1, s21_decimal *value_2,
                    s21_decimal *ostat_dec);
int is_less_or_equal_mantis(s21_decimal val1, s21_decimal val2);

// mul
int mul_by_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void add_product_to_big_decimal(s21_big_decimal *tmp,
                                unsigned long long product, int pos);
int big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result,
                           int result_scale);
int convert_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result,
                                   int *scale);

// div
int div_by_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void add_frac_part_to_decimal(s21_decimal *quotient, s21_big_decimal remainder,
                              s21_decimal value_2, int *result_scale);
int mul_by_10_big_decimal(s21_big_decimal *value);
void div_big_decimal(s21_big_decimal *remainder, s21_decimal divisor,
                     s21_decimal *quotient);
void left_shift_big_decimal(s21_big_decimal *num);
int get_bit_big_decimal(s21_big_decimal num, int position);
void set_bit_big_decimal(s21_big_decimal *num, int position, int value);
void set_bit(s21_decimal *num, int position, int value);
int is_greater_or_equal_big_decimal(s21_big_decimal value_1,
                                    s21_decimal value_2);
void sub_big_decimal(s21_big_decimal value_1, s21_decimal value,
                     s21_big_decimal *result);

// equal
int normalize_scales(s21_decimal *value_1, s21_decimal *value_2);
int compare_by_bits(s21_decimal value1, s21_decimal value2);

// decimal->float
int round_number_by_decimal(s21_decimal src, long double *result);

////round
int bankers_round(s21_decimal value, s21_decimal *result);
int general_rounding(s21_decimal value, s21_decimal *result, int type_rounding);
void general_rounding_by_bits(s21_decimal *result, int type_rounding);
void apply_floor_rounding(s21_decimal *result, int sign, int count_digits);
void apply_math_rounding(s21_decimal *result, int curr_digit);
void apply_bankers_rounding(s21_decimal *result, int curr_digit,
                            int count_digits);

#endif