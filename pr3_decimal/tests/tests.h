#ifndef SRC_TESTS
#define SRC_TESTS

#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"
#include "../s21_subfunctions.h"

Suite *s21_test_add(void);
Suite *s21_test_sub(void);
Suite *s21_test_mul(void);
Suite *s21_test_div(void);

Suite *s21_test_is_less(void);
Suite *s21_test_is_less_or_equal(void);
Suite *s21_test_is_greater(void);
Suite *s21_test_is_greater_or_equal(void);
Suite *s21_test_is_equal(void);
Suite *s21_test_is_not_equal(void);

Suite *s21_test_from_decimal_to_int(void);
Suite *s21_test_from_int_to_decimal(void);
Suite *s21_test_from_float_to_decimal(void);
Suite *s21_test_from_decimal_to_float(void);

Suite *s21_test_floor(void);
Suite *s21_test_round(void);
Suite *s21_test_truncate(void);
Suite *s21_test_negate(void);

#endif
