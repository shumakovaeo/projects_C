
#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "string_test.h"

START_TEST(test_s21_sprintf_c) {
  char buf_std[10], buf_s21[10];
  sprintf(buf_std, "%c", 'A');
  s21_sprintf(buf_s21, "%c", 'A');
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_d) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%d", -123);
  s21_sprintf(buf_s21, "%d", -123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_i) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%i", 077);
  s21_sprintf(buf_s21, "%i", 077);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_e) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%.6e", 1.23456e-3);
  s21_sprintf(buf_s21, "%.6e", 1.23456e-3);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_E) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%.6E", 1.23456e-3);
  s21_sprintf(buf_s21, "%.6E", 1.23456e-3);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%.2f", 3.14159);
  s21_sprintf(buf_s21, "%.2f", 3.14159);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_g) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%g", 123.0);
  s21_sprintf(buf_s21, "%g", 123.0);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_G) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%G", 123.0);
  s21_sprintf(buf_s21, "%G", 123.0);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_o) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%o", 8);
  s21_sprintf(buf_s21, "%o", 8);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_sprintf_precision_zero_value_zero) {
  char buf[100];
  s21_sprintf(buf, "%.0d", 0);
  ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_sprintf_precision_zero_negative_zero) {
  char buf[100];
  s21_sprintf(buf, "%.0d", -0);
  ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_sprintf_float_precision_zero_zero) {
  char buf[100];
  s21_sprintf(buf, "%.0f", 0.0);
  ck_assert_str_eq(buf, "0");
}
END_TEST

START_TEST(test_s21_sprintf_s) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%s", "hello");
  s21_sprintf(buf_s21, "%s", "hello");
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_u) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%u", 4294967295U);
  s21_sprintf(buf_s21, "%u", 4294967295U);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_x) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%x", 255);
  s21_sprintf(buf_s21, "%x", 255);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_X) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%X", 255);
  s21_sprintf(buf_s21, "%X", 255);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_p) {
  char buf_std[30], buf_s21[30];
  int a = 42;
  sprintf(buf_std, "%p", (void*)&a);
  s21_sprintf(buf_s21, "%p", (void*)&a);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_n) {
  char buf_std[20], buf_s21[20];
  int count_std, count_s21;
  sprintf(buf_std, "test%n", &count_std);
  s21_sprintf(buf_s21, "test%n", &count_s21);
  ck_assert_str_eq(buf_std, buf_s21);
  ck_assert_int_eq(count_std, count_s21);
}
END_TEST

START_TEST(test_s21_sprintf_percent) {
  char buf_std[10], buf_s21[10];
  sprintf(buf_std, "%%");
  s21_sprintf(buf_s21, "%%");
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_flag_minus) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%-10d", 123);
  s21_sprintf(buf_s21, "%-10d", 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_flag_plus) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%+d", 123);
  s21_sprintf(buf_s21, "%+d", 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_flag_space) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "% d", 123);
  s21_sprintf(buf_s21, "% d", 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_flag_hash) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%#o", 8);
  s21_sprintf(buf_s21, "%#o", 8);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_flag_zero) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%010d", 123);
  s21_sprintf(buf_s21, "%010d", 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_width_number) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%5d", 123);
  s21_sprintf(buf_s21, "%5d", 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_width_star) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%*d", 5, 123);
  s21_sprintf(buf_s21, "%*d", 5, 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_precision_number) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%.3d", 123);
  s21_sprintf(buf_s21, "%.3d", 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_precision_star) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%.*d", 3, 123);
  s21_sprintf(buf_s21, "%.*d", 3, 123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_precision_star_double) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%.*lf", 3, 123.9876);
  s21_sprintf(buf_s21, "%.*lf", 3, 123.9876);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_length_h) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%hd", (short)123);
  s21_sprintf(buf_s21, "%hd", (short)123);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_length_l) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%ld", 123L);
  s21_sprintf(buf_s21, "%ld", 123L);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_s21_sprintf_length_L) {
  char buf_std[20], buf_s21[20];
  sprintf(buf_std, "%Le", 1.23e1L);
  s21_sprintf(buf_s21, "%Le", 1.23e1L);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

START_TEST(test_sprintf_zero_flag) {
  char buf[100];
  s21_sprintf(buf, "%010d", 42);
  ck_assert_str_eq(buf, "0000000042");
}
END_TEST

START_TEST(test_sprintf_width_star) {
  char buf[100];
  s21_sprintf(buf, "%*d", 10, 42);
  ck_assert_str_eq(buf, "        42");
}
END_TEST

START_TEST(test_sprintf_precision_star) {
  char buf[100];
  s21_sprintf(buf, "%.*f", 2, 3.14159);
  ck_assert_str_eq(buf, "3.14");
}
END_TEST

START_TEST(test_sprintf_length_hh) {
  char buf[100];
  s21_sprintf(buf, "%hhd", (char)42);
  ck_assert_str_eq(buf, "42");
}
END_TEST

START_TEST(test_sprintf_length_ll) {
  char buf[100];
  s21_sprintf(buf, "%lld", (long long)42);
  ck_assert_str_eq(buf, "42");
}
END_TEST

START_TEST(test_sprintf_length_L) {
  char buf[100];
  s21_sprintf(buf, "%Lf", (long double)3.14);
  ck_assert_str_eq(buf, "3.140000");
}
END_TEST

START_TEST(test_sprintf_llong_min) {
  char buf[100];
  s21_sprintf(buf, "%lld", LLONG_MIN);
  ck_assert_str_eq(buf, "-9223372036854775808");
}
END_TEST

START_TEST(test_sprintf_hex_upper_hash) {
  char buf[100];
  s21_sprintf(buf, "%#X", 255);
  ck_assert_str_eq(buf, "0XFF");
}
END_TEST

START_TEST(test_sprintf_octal_hash) {
  char buf[100];
  s21_sprintf(buf, "%#o", 8);
  ck_assert_str_eq(buf, "010");
}
END_TEST

START_TEST(test_sprintf_float_nan) {
  char buf[100];
  s21_sprintf(buf, "%f", NAN);
  ck_assert_str_eq(buf, "nan");
}
END_TEST

START_TEST(test_sprintf_float_inf) {
  char buf[100];
  s21_sprintf(buf, "%f", INFINITY);
  ck_assert_str_eq(buf, "inf");
}
END_TEST

START_TEST(test_sprintf_float_neg_inf) {
  char buf[100];
  s21_sprintf(buf, "%f", -INFINITY);
  ck_assert_str_eq(buf, "-inf");
}
END_TEST

START_TEST(test_sprintf_float_precision_zero) {
  char buf[100];
  s21_sprintf(buf, "%.0f", 3.14);
  ck_assert_str_eq(buf, "3");
}
END_TEST

START_TEST(test_sprintf_hex_hash) {
  char buf[100];
  s21_sprintf(buf, "%#x", 255);
  ck_assert_str_eq(buf, "0xff");
}
END_TEST

START_TEST(test_sprintf_pointer) {
  char buf[100];
  int x = 42;
  s21_sprintf(buf, "%p", &x);

  ck_assert(buf[0] == '0' && buf[1] == 'x');
}
END_TEST

START_TEST(test_sprintf_n) {
  char buf[100];
  int count = 0;
  s21_sprintf(buf, "hello%nworld", &count);
  ck_assert_int_eq(count, 5);
}
END_TEST

START_TEST(test_sprintf_invalid_spec) {
  char buf[100];
  s21_sprintf(buf, "%z", 42);
  ck_assert_str_eq(buf, "%z");
}
END_TEST

START_TEST(test_sprintf_precision_zero_int) {
  char buf[100];
  s21_sprintf(buf, "%.0d", 0);
  ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_sprintf_precision_zero_uint) {
  char buf[100];
  s21_sprintf(buf, "%.0u", 0);
  ck_assert_str_eq(buf, "");
}
END_TEST

START_TEST(test_sprintf_minus_flag) {
  char buf[100];
  s21_sprintf(buf, "%-10d", 42);
  ck_assert_str_eq(buf, "42        ");
}
END_TEST

START_TEST(test_sprintf_plus_flag) {
  char buf[100];
  s21_sprintf(buf, "%+d", 42);
  ck_assert_str_eq(buf, "+42");
}
END_TEST

START_TEST(test_sprintf_space_flag) {
  char buf[100];
  s21_sprintf(buf, "% d", 42);
  ck_assert_str_eq(buf, " 42");
}
END_TEST

START_TEST(test_sprintf_hash_flag_float) {
  char buf[100];
  s21_sprintf(buf, "%#.g", 3.14);
  ck_assert_str_eq(buf, "3.14000");
}
END_TEST

START_TEST(test_sprintf_exp_nan) {
  char buf[100];
  s21_sprintf(buf, "%e", NAN);
  ck_assert_str_eq(buf, "nan");
}
END_TEST

START_TEST(test_sprintf_exp_inf) {
  char buf[100];
  s21_sprintf(buf, "%e", INFINITY);
  ck_assert_str_eq(buf, "inf");
}
END_TEST

START_TEST(test_sprintf_general_nan) {
  char buf[100];
  s21_sprintf(buf, "%g", NAN);
  ck_assert_str_eq(buf, "nan");
}
END_TEST

START_TEST(test_sprintf_general_inf) {
  char buf[100];
  s21_sprintf(buf, "%g", INFINITY);
  ck_assert_str_eq(buf, "inf");
}
END_TEST

START_TEST(test_sprintf_zero_exp) {
  char buf[100];
  s21_sprintf(buf, "%e", 0.0);
  ck_assert_str_eq(buf, "0.000000e+00");
}
END_TEST

START_TEST(test_sprintf_general_zero) {
  char buf[100];
  s21_sprintf(buf, "%g", 0.0);
  ck_assert_str_eq(buf, "0");
}
END_TEST

START_TEST(test_sprintf_general_zero_precision) {
  char buf[100];
  s21_sprintf(buf, "%.2g", 0.0);
  ck_assert_str_eq(buf, "0");
}
END_TEST

START_TEST(test_sprintf_general_small_exp) {
  char buf[100];
  s21_sprintf(buf, "%g", 0.00001);
  ck_assert_str_eq(buf, "1e-05");
}
END_TEST

START_TEST(test_sprintf_general_small_exp_precision) {
  char buf[100];
  s21_sprintf(buf, "%.1g", 0.00001);
  ck_assert_str_eq(buf, "1e-05");
}
END_TEST

START_TEST(test_sprintf_general_large_exp) {
  char buf[100];
  s21_sprintf(buf, "%.1g", 123456.0);
  ck_assert_str_eq(buf, "1e+05");
}
END_TEST

START_TEST(test_sprintf_general_large_exp_precision) {
  char buf[100];
  s21_sprintf(buf, "%.0g", 100.0);
  ck_assert_str_eq(buf, "1e+02");
}
END_TEST

START_TEST(test_sprintf_char_width_no_minus) {
  char buf[100];
  s21_sprintf(buf, "%5c", 'A');
  ck_assert_str_eq(buf, "    A");
}
END_TEST

START_TEST(test_sprintf_char_width_minus) {
  char buf[100];
  s21_sprintf(buf, "%-5c", 'A');
  ck_assert_str_eq(buf, "A    ");
}
END_TEST

START_TEST(test_sprintf_char_width_no_minus_small) {
  char buf[100];
  s21_sprintf(buf, "%3c", 'B');
  ck_assert_str_eq(buf, "  B");
}
END_TEST

START_TEST(test_sprintf_char_width_minus_small) {
  char buf[100];
  s21_sprintf(buf, "%-3c", 'B');
  ck_assert_str_eq(buf, "B  ");
}
END_TEST

START_TEST(test_sprintf_general_long_double) {
  char buf[100];
  long double ld = 1.23456789012345L;
  s21_sprintf(buf, "%Lg", ld);

  char std_buf[100];
  sprintf(std_buf, "%Lg", ld);
  ck_assert_str_eq(buf, std_buf);
}
END_TEST

START_TEST(test_sprintf_general_hash) {
  char buf[100];
  s21_sprintf(buf, "%#.0g", 123.0);
  ck_assert_str_eq(buf, "1e+02.");
}
END_TEST

START_TEST(test_sprintf_general_hash_no_dot) {
  char buf[100];
  s21_sprintf(buf, "%#g", 100.0);
  ck_assert_str_eq(buf, "100.");
}
END_TEST

START_TEST(test_sprintf_general_plus) {
  char buf[100];
  s21_sprintf(buf, "%+g", 123.45);
  ck_assert_str_eq(buf, "+123.45");
}
END_TEST

START_TEST(test_sprintf_general_space) {
  char buf[100];
  s21_sprintf(buf, "% g", 123.45);
  ck_assert_str_eq(buf, " 123.45");
}
END_TEST

START_TEST(test_sprintf_general_width_no_minus) {
  char buf[100];
  s21_sprintf(buf, "%10g", 1.23);
  ck_assert_str_eq(buf, "      1.23");
}
END_TEST

START_TEST(test_sprintf_general_width_minus) {
  char buf[100];
  s21_sprintf(buf, "%-10g", 1.23);
  ck_assert_str_eq(buf, "1.23      ");
}
END_TEST

START_TEST(test_sprintf_general_plus_width) {
  char buf[100];
  s21_sprintf(buf, "%+10g", 1.23);
  ck_assert_str_eq(buf, "     +1.23");
}
END_TEST

START_TEST(test_sprintf_hex_precision_greater) {
  char buf[100];
  s21_sprintf(buf, "%.3x", 1);
  ck_assert_str_eq(buf, "001");
}
END_TEST

START_TEST(test_sprintf_hex_minus) {
  char buf[100];
  s21_sprintf(buf, "%-10x", 255);
  ck_assert_str_eq(buf, "ff        ");
}
END_TEST

START_TEST(test_sprintf_hex_zero_precision_zero) {
  char buf[100];
  s21_sprintf(buf, "%010x", 255);
  ck_assert_str_eq(buf, "00000000ff");
}
END_TEST

START_TEST(test_sprintf_hex_zero_precision_zero_hash) {
  char buf[100];
  s21_sprintf(buf, "%#010x", 255);
  ck_assert_str_eq(buf, "0x000000ff");
}
END_TEST

START_TEST(test_sprintf_hex_zero_precision_zero_no_hash) {
  char buf[100];
  s21_sprintf(buf, "%010x", 0);
  ck_assert_str_eq(buf, "0000000000");
}
END_TEST

START_TEST(test_sprintf_hex_width_no_minus) {
  char buf[100];
  s21_sprintf(buf, "%10x", 255);
  ck_assert_str_eq(buf, "        ff");
}
END_TEST

START_TEST(test_sprintf_hex_minus_hash) {
  char buf[100];
  s21_sprintf(buf, "%-#10x", 255);
  ck_assert_str_eq(buf, "0xff      ");
}
END_TEST

START_TEST(test_sprintf_hex_zeros_needed) {
  char buf[100];
  s21_sprintf(buf, "%.5x", 15);
  ck_assert_str_eq(buf, "0000f");
}
END_TEST

START_TEST(test_sprintf_hex_width_minus_padding) {
  char buf[100];
  s21_sprintf(buf, "%-8x", 1);
  ck_assert_str_eq(buf, "1       ");
}
END_TEST

START_TEST(test_sprintf_hex_uppercase_precision) {
  char buf[100];
  s21_sprintf(buf, "%.4X", 10);
  ck_assert_str_eq(buf, "000A");
}
END_TEST

START_TEST(test_sprintf_unsigned_ll) {
  char buf[100];
  s21_sprintf(buf, "%llu", 123456789012345ULL);
  ck_assert_str_eq(buf, "123456789012345");
}
END_TEST

START_TEST(test_sprintf_unsigned_l) {
  char buf[100];
  s21_sprintf(buf, "%lu", 4294967295UL);
  ck_assert_str_eq(buf, "4294967295");
}
END_TEST

START_TEST(test_sprintf_unsigned_hh) {
  char buf[100];
  s21_sprintf(buf, "%hhu", 255);
  ck_assert_str_eq(buf, "255");
}
END_TEST

START_TEST(test_sprintf_unsigned_h) {
  char buf[100];
  s21_sprintf(buf, "%hu", 65535);
  ck_assert_str_eq(buf, "65535");
}
END_TEST

START_TEST(test_sprintf_unsigned_precision_greater) {
  char buf[100];
  s21_sprintf(buf, "%.5u", 1);
  ck_assert_str_eq(buf, "00001");
}
END_TEST

START_TEST(test_sprintf_unsigned_precision_zero_nonzero) {
  char buf[100];
  s21_sprintf(buf, "%.0u", 5);
  ck_assert_str_eq(buf, "5");
}
END_TEST

START_TEST(test_sprintf_unsigned_zero_flag) {
  char buf[100];
  s21_sprintf(buf, "%010u", 123);
  ck_assert_str_eq(buf, "0000000123");
}
END_TEST

START_TEST(test_sprintf_unsigned_minus) {
  char buf[100];
  s21_sprintf(buf, "%-10u", 123);
  ck_assert_str_eq(buf, "123       ");
}
END_TEST

START_TEST(test_sprintf_unsigned_minus_precision) {
  char buf[100];
  s21_sprintf(buf, "%-.5u", 1);
  ck_assert_str_eq(buf, "00001     ");
}
END_TEST

START_TEST(test_sprintf_unsigned_width_no_minus) {
  char buf[100];
  s21_sprintf(buf, "%10u", 123);
  ck_assert_str_eq(buf, "       123");
}
END_TEST

START_TEST(char_left_pad) {
  char buf[100];
  s21_sprintf(buf, "%5c", 'A');
  ck_assert_str_eq(buf, "    A");
}
END_TEST

START_TEST(char_right_pad) {
  char buf[100];
  s21_sprintf(buf, "%-5c", 'A');
  ck_assert_str_eq(buf, "A    ");
}
END_TEST

START_TEST(char_no_pad) {
  char buf[100];
  s21_sprintf(buf, "%c", 'A');
  ck_assert_str_eq(buf, "A");
}
END_TEST

START_TEST(string_null) {
  char buf[100];
  s21_sprintf(buf, "%s", NULL);
  ck_assert_str_eq(buf, "(null)");
}
END_TEST

START_TEST(string_precision_trunc) {
  char buf[100];
  s21_sprintf(buf, "%.3s", "hello");
  ck_assert_str_eq(buf, "hel");
}
END_TEST

START_TEST(string_left_pad) {
  char buf[100];
  s21_sprintf(buf, "%10s", "hi");
  ck_assert_str_eq(buf, "        hi");
}
END_TEST

START_TEST(string_right_pad) {
  char buf[100];
  s21_sprintf(buf, "%-10s", "hi");
  ck_assert_str_eq(buf, "hi        ");
}
END_TEST

START_TEST(string_prec_width_right_pad) {
  char buf[100];
  s21_sprintf(buf, "%-10.3s", "hello");
  ck_assert_str_eq(buf, "hel       ");
}
END_TEST

Suite* suite_s21_sprintf(void) {
  Suite* s = suite_create("s21_sprintf");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_sprintf_zero_flag);

  tcase_add_test(tc, test_sprintf_precision_zero_value_zero);
  tcase_add_test(tc, test_sprintf_precision_zero_negative_zero);
  tcase_add_test(tc, test_sprintf_float_precision_zero_zero);
  tcase_add_test(tc, test_sprintf_char_width_no_minus);
  tcase_add_test(tc, test_sprintf_char_width_minus);
  tcase_add_test(tc, char_left_pad);
  tcase_add_test(tc, char_right_pad);
  tcase_add_test(tc, char_no_pad);
  tcase_add_test(tc, string_null);
  tcase_add_test(tc, string_precision_trunc);
  tcase_add_test(tc, string_left_pad);
  tcase_add_test(tc, string_right_pad);
  tcase_add_test(tc, string_prec_width_right_pad);
  tcase_add_test(tc, test_sprintf_general_long_double);
  tcase_add_test(tc, test_sprintf_general_hash);
  tcase_add_test(tc, test_sprintf_general_hash_no_dot);
  tcase_add_test(tc, test_sprintf_unsigned_ll);
  tcase_add_test(tc, test_sprintf_unsigned_l);
  tcase_add_test(tc, test_sprintf_unsigned_hh);
  tcase_add_test(tc, test_sprintf_unsigned_h);
  tcase_add_test(tc, test_sprintf_unsigned_precision_greater);
  tcase_add_test(tc, test_sprintf_unsigned_precision_zero_nonzero);
  tcase_add_test(tc, test_sprintf_unsigned_zero_flag);
  tcase_add_test(tc, test_sprintf_unsigned_minus);
  tcase_add_test(tc, test_sprintf_unsigned_minus_precision);
  tcase_add_test(tc, test_sprintf_unsigned_width_no_minus);
  tcase_add_test(tc, test_sprintf_hex_precision_greater);
  tcase_add_test(tc, test_sprintf_hex_minus);
  tcase_add_test(tc, test_sprintf_hex_zero_precision_zero);
  tcase_add_test(tc, test_sprintf_hex_zero_precision_zero_hash);
  tcase_add_test(tc, test_sprintf_hex_zero_precision_zero_no_hash);
  tcase_add_test(tc, test_sprintf_hex_width_no_minus);
  tcase_add_test(tc, test_sprintf_hex_minus_hash);
  tcase_add_test(tc, test_sprintf_hex_zeros_needed);
  tcase_add_test(tc, test_sprintf_hex_width_minus_padding);
  tcase_add_test(tc, test_sprintf_hex_uppercase_precision);
  tcase_add_test(tc, test_sprintf_general_plus);
  tcase_add_test(tc, test_sprintf_general_space);
  tcase_add_test(tc, test_sprintf_general_width_no_minus);
  tcase_add_test(tc, test_sprintf_general_width_minus);
  tcase_add_test(tc, test_sprintf_general_plus_width);

  tcase_add_test(tc, test_sprintf_char_width_no_minus_small);
  tcase_add_test(tc, test_sprintf_char_width_minus_small);
  tcase_add_test(tc, test_sprintf_general_zero);
  tcase_add_test(tc, test_sprintf_general_zero_precision);
  tcase_add_test(tc, test_sprintf_general_small_exp);
  tcase_add_test(tc, test_sprintf_general_small_exp_precision);
  tcase_add_test(tc, test_sprintf_general_large_exp);
  tcase_add_test(tc, test_sprintf_general_large_exp_precision);
  tcase_add_test(tc, test_sprintf_width_star);
  tcase_add_test(tc, test_sprintf_precision_star);
  tcase_add_test(tc, test_sprintf_length_hh);
  tcase_add_test(tc, test_sprintf_length_ll);
  tcase_add_test(tc, test_sprintf_length_L);
  tcase_add_test(tc, test_sprintf_llong_min);
  tcase_add_test(tc, test_sprintf_hex_upper_hash);
  tcase_add_test(tc, test_sprintf_octal_hash);
  tcase_add_test(tc, test_sprintf_float_nan);
  tcase_add_test(tc, test_sprintf_float_inf);
  tcase_add_test(tc, test_sprintf_float_neg_inf);
  tcase_add_test(tc, test_sprintf_float_precision_zero);
  tcase_add_test(tc, test_sprintf_hex_hash);
  tcase_add_test(tc, test_sprintf_pointer);
  tcase_add_test(tc, test_sprintf_n);
  tcase_add_test(tc, test_sprintf_invalid_spec);
  tcase_add_test(tc, test_sprintf_precision_zero_int);
  tcase_add_test(tc, test_sprintf_precision_zero_uint);
  tcase_add_test(tc, test_sprintf_minus_flag);
  tcase_add_test(tc, test_sprintf_plus_flag);
  tcase_add_test(tc, test_sprintf_space_flag);
  tcase_add_test(tc, test_sprintf_hash_flag_float);
  tcase_add_test(tc, test_sprintf_exp_nan);
  tcase_add_test(tc, test_sprintf_exp_inf);
  tcase_add_test(tc, test_sprintf_general_nan);
  tcase_add_test(tc, test_sprintf_general_inf);
  tcase_add_test(tc, test_sprintf_zero_exp);

  tcase_add_test(tc, test_s21_sprintf_c);
  tcase_add_test(tc, test_s21_sprintf_d);
  tcase_add_test(tc, test_s21_sprintf_i);
  tcase_add_test(tc, test_s21_sprintf_e);
  tcase_add_test(tc, test_s21_sprintf_E);
  tcase_add_test(tc, test_s21_sprintf_f);
  tcase_add_test(tc, test_s21_sprintf_g);
  tcase_add_test(tc, test_s21_sprintf_G);
  tcase_add_test(tc, test_s21_sprintf_o);
  tcase_add_test(tc, test_s21_sprintf_s);
  tcase_add_test(tc, test_s21_sprintf_u);
  tcase_add_test(tc, test_s21_sprintf_x);
  tcase_add_test(tc, test_s21_sprintf_X);
  tcase_add_test(tc, test_s21_sprintf_p);
  tcase_add_test(tc, test_s21_sprintf_n);
  tcase_add_test(tc, test_s21_sprintf_percent);
  tcase_add_test(tc, test_s21_sprintf_flag_minus);
  tcase_add_test(tc, test_s21_sprintf_flag_plus);
  tcase_add_test(tc, test_s21_sprintf_flag_space);
  tcase_add_test(tc, test_s21_sprintf_flag_hash);
  tcase_add_test(tc, test_s21_sprintf_flag_zero);
  tcase_add_test(tc, test_s21_sprintf_width_number);
  tcase_add_test(tc, test_s21_sprintf_width_star);
  tcase_add_test(tc, test_s21_sprintf_precision_number);
  tcase_add_test(tc, test_s21_sprintf_precision_star);
  tcase_add_test(tc, test_s21_sprintf_precision_star_double);
  tcase_add_test(tc, test_s21_sprintf_length_h);
  tcase_add_test(tc, test_s21_sprintf_length_l);
  tcase_add_test(tc, test_s21_sprintf_length_L);
  suite_add_tcase(s, tc);
  return s;
}
