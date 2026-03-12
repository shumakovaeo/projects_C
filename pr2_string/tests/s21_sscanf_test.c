
#include <check.h>
#include <stdio.h>

#include "string_test.h"

START_TEST(test_s21_sscanf_c) {
  char ch_std, ch_s21;
  sscanf("A", "%c", &ch_std);
  s21_sscanf("A", "%c", &ch_s21);
  ck_assert_int_eq(ch_std, ch_s21);
}
END_TEST

START_TEST(test_s21_sscanf_d) {
  int num_std, num_s21;
  sscanf("-123", "%d", &num_std);
  s21_sscanf("-123", "%d", &num_s21);
  ck_assert_int_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_i) {
  int num_std, num_s21;
  sscanf("077", "%i", &num_std);
  s21_sscanf("077", "%i", &num_s21);
  ck_assert_int_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_e) {
  float num_std, num_s21;
  sscanf("1.234560e-03", "%e", &num_std);
  s21_sscanf("1.234560e-03", "%e", &num_s21);
  ck_assert_double_eq_tol(num_std, num_s21, 1e-6);
}
END_TEST

START_TEST(test_s21_sscanf_E) {
  float num_std, num_s21;
  sscanf("1.234560E-03", "%E", &num_std);
  s21_sscanf("1.234560E-03", "%E", &num_s21);
  ck_assert_double_eq_tol(num_std, num_s21, 1e-6);
}
END_TEST

START_TEST(test_s21_sscanf_f) {
  float num_std, num_s21;
  sscanf("3.14", "%f", &num_std);
  s21_sscanf("3.14", "%f", &num_s21);
  ck_assert_double_eq_tol(num_std, num_s21, 0.01);
}
END_TEST

START_TEST(test_s21_sscanf_g) {
  float num_std, num_s21;
  sscanf("123", "%g", &num_std);
  s21_sscanf("123", "%g", &num_s21);
  ck_assert_double_eq_tol(num_std, num_s21, 0.01);
}
END_TEST

START_TEST(test_s21_sscanf_G) {
  float num_std, num_s21;
  sscanf("123", "%G", &num_std);
  s21_sscanf("123", "%G", &num_s21);
  ck_assert_double_eq_tol(num_std, num_s21, 0.01);
}
END_TEST

START_TEST(test_s21_sscanf_o) {
  unsigned int num_std, num_s21;
  sscanf("10", "%o", &num_std);
  s21_sscanf("10", "%o", &num_s21);
  ck_assert_uint_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_s) {
  char str_std[10], str_s21[10];
  sscanf("hello", "%s", str_std);
  s21_sscanf("hello", "%s", str_s21);
  ck_assert_str_eq(str_std, str_s21);
}
END_TEST

START_TEST(test_s21_sscanf_u) {
  unsigned int num_std, num_s21;
  sscanf("4294967295", "%u", &num_std);
  s21_sscanf("4294967295", "%u", &num_s21);
  ck_assert_uint_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_x) {
  unsigned int num_std, num_s21;
  sscanf("ff", "%x", &num_std);
  s21_sscanf("ff", "%x", &num_s21);
  ck_assert_uint_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_X) {
  unsigned int num_std, num_s21;
  sscanf("FF", "%X", &num_std);
  s21_sscanf("FF", "%X", &num_s21);
  ck_assert_uint_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_p) {
  void *ptr_std, *ptr_s21;
  char buf[30];
  sprintf(buf, "%p", (void *)0x12345678);
  sscanf(buf, "%p", &ptr_std);
  s21_sscanf(buf, "%p", &ptr_s21);
  ck_assert_ptr_eq(ptr_std, ptr_s21);
}
END_TEST

START_TEST(test_s21_sscanf_n) {
  int count_std, count_s21;
  sscanf("test", "test%n", &count_std);
  s21_sscanf("test", "test%n", &count_s21);
  ck_assert_int_eq(count_std, count_s21);
}
END_TEST

START_TEST(test_s21_sscanf_percent) {
  int res_std = sscanf("%", "%%");
  int res_s21 = s21_sscanf("%", "%%");
  ck_assert_int_eq(res_std, res_s21);
}
END_TEST

START_TEST(test_s21_sscanf_width_number_d) {
  int num_std, num_s21;
  sscanf("12345", "%3d", &num_std);
  s21_sscanf("12345", "%3d", &num_s21);
  ck_assert_int_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_width_number_s) {
  char str_std[10], str_s21[10];
  sscanf("hello world", "%5s", str_std);
  s21_sscanf("hello world", "%5s", str_s21);
  ck_assert_str_eq(str_std, str_s21);
}
END_TEST

START_TEST(test_s21_sscanf_width_star) {
  int num_std, num_s21;
  sscanf("123 456", "%*d %d", &num_std);
  s21_sscanf("123 456", "%*d %d", &num_s21);
  ck_assert_int_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_length_h_d) {
  short num_std, num_s21;
  sscanf("123", "%hd", &num_std);
  s21_sscanf("123", "%hd", &num_s21);
  ck_assert_int_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_length_h_u) {
  unsigned short num_std, num_s21;
  sscanf("65535", "%hu", &num_std);
  s21_sscanf("65535", "%hu", &num_s21);
  ck_assert_uint_eq(num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_length_l_d) {
  long num_std, num_s21;
  sscanf("123456789", "%ld", &num_std);
  s21_sscanf("123456789", "%ld", &num_s21);
  ck_assert_msg(num_std == num_s21, "Expected %ld, got %ld", num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_length_l_u) {
  unsigned long num_std, num_s21;
  sscanf("4294967295", "%lu", &num_std);
  s21_sscanf("4294967295", "%lu", &num_s21);
  ck_assert_msg(num_std == num_s21, "Expected %lu, got %lu", num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_length_L_e) {
  long double num_std, num_s21;
  sscanf("1.23e1", "%Le", &num_std);
  s21_sscanf("1.23e1", "%Le", &num_s21);
  ck_assert_msg(fabsl(num_std - num_s21) < 1e-6L, "Expected %Lf, got %Lf",
                num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_length_L_f) {
  long double num_std, num_s21;
  sscanf("3.1415926535", "%Lf", &num_std);
  s21_sscanf("3.1415926535", "%Lf", &num_s21);
  ck_assert_msg(fabsl(num_std - num_s21) < 1e-10L, "Expected %Lf, got %Lf",
                num_std, num_s21);
}
END_TEST

START_TEST(test_s21_sscanf_combined_d_u) {
  int a_std;
  unsigned int b_std;
  int a_s21;
  unsigned int b_s21;
  sscanf("123 456", "%d %u", &a_std, &b_std);
  s21_sscanf("123 456", "%d %u", &a_s21, &b_s21);
  ck_assert_int_eq(a_std, a_s21);
  ck_assert_uint_eq(b_std, b_s21);
}
END_TEST

START_TEST(test_s21_sscanf_combined_s_c) {
  char str_std[10], ch_std;
  char str_s21[10], ch_s21;
  sscanf("hello A", "%s %c", str_std, &ch_std);
  s21_sscanf("hello A", "%s %c", str_s21, &ch_s21);
  ck_assert_str_eq(str_std, str_s21);
  ck_assert_int_eq(ch_std, ch_s21);
}
END_TEST

START_TEST(test_s21_sscanf_combined_f_g) {
  float f_std, g_std;
  float f_s21, g_s21;
  sscanf("3.14 2.71", "%f %g", &f_std, &g_std);
  s21_sscanf("3.14 2.71", "%f %g", &f_s21, &g_s21);
  ck_assert_double_eq_tol(f_std, f_s21, 0.01);
  ck_assert_double_eq_tol(g_std, g_s21, 0.01);
}
END_TEST

START_TEST(test_s21_sscanf_combined_o_x_X) {
  unsigned int o_std, x_std, X_std;
  unsigned int o_s21, x_s21, X_s21;
  sscanf("10 ff FF", "%o %x %X", &o_std, &x_std, &X_std);
  s21_sscanf("10 ff FF", "%o %x %X", &o_s21, &x_s21, &X_s21);
  ck_assert_uint_eq(o_std, o_s21);
  ck_assert_uint_eq(x_std, x_s21);
  ck_assert_uint_eq(X_std, X_s21);
}
END_TEST

START_TEST(test_s21_sscanf_combined_width_precision) {
  char str_std[10], str_s21[10];
  sscanf("hello world", "%5s", str_std);
  s21_sscanf("hello world", "%5s", str_s21);
  ck_assert_str_eq(str_std, str_s21);
}
END_TEST

START_TEST(test_hex_signed) {
  const char *str = "0x1a -0X2b";
  int res;
  int val1, val2;
  res = s21_sscanf(str, "%i %i", &val1, &val2);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(val1, 26);
  ck_assert_int_eq(val2, -43);

  int orig_res;
  orig_res = sscanf(str, "%i %i", &val1, &val2);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_octal_signed) {
  const char *str = "0123 -0456";
  int res;
  int val1, val2;
  res = s21_sscanf(str, "%i %i", &val1, &val2);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(val1, 83);
  ck_assert_int_eq(val2, -302);

  int orig_res;
  orig_res = sscanf(str, "%i %i", &val1, &val2);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_float_sign) {
  const char *str = "+3.14 -2.718";
  int res;
  float f1, f2;
  res = s21_sscanf(str, "%f %f", &f1, &f2);
  ck_assert_int_eq(res, 2);
  ck_assert_float_eq_tol(f1, 3.14f, 1e-6);
  ck_assert_float_eq_tol(f2, -2.718f, 1e-6);

  int orig_res;
  orig_res = sscanf(str, "%f %f", &f1, &f2);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_float_exp_sign_neg) {
  const char *str = "1.23e-2 4.56E+3";
  int res;
  double d1, d2;
  res = s21_sscanf(str, "%lf %le", &d1, &d2);
  ck_assert_int_eq(res, 2);
  ck_assert_double_eq_tol(d1, 0.0123, 1e-6);
  ck_assert_double_eq_tol(d2, 4560.0, 1e-6);

  int orig_res;
  orig_res = sscanf(str, "%lf %le", &d1, &d2);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_p_specifier) {
  const char *str = "0xdeadbeef";
  int res;
  void *ptr;
  res = s21_sscanf(str, "%p", &ptr);
  ck_assert_int_eq(res, 1);

  ck_assert_ptr_ne(ptr, NULL);

  void *orig_ptr;
  int orig_res = sscanf(str, "%p", &orig_ptr);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_n_specifier) {
  const char *str = "hello world";
  int n, res;
  char st[50], st1[50];
  res = s21_sscanf(str, "%s%n", st, &n);
  int orig_n, orig_res;
  orig_res = sscanf(str, "%s%n", st1, &orig_n);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(n, orig_n);
}
END_TEST
#include <wchar.h>

START_TEST(test_c_with_l) {
  const char *str = "a";
  int res;
  wchar_t wc;
  res = s21_sscanf(str, "%lc", &wc);
  ck_assert_int_eq((int)wc, (int)L'a');

  wchar_t orig_wc;
  int orig_res = sscanf(str, "%lc", &orig_wc);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq((int)wc, (int)orig_wc);
}
END_TEST

START_TEST(test_width_multi) {
  const char *str = "12345";
  int res;
  char buf[3];
  res = s21_sscanf(str, "%2s", buf);
  ck_assert_int_eq(res, 1);
  ck_assert_str_eq(buf, "12");

  char orig_buf[3];
  int orig_res = sscanf(str, "%2s", orig_buf);
  ck_assert_int_eq(res, orig_res);
  ck_assert_str_eq(buf, orig_buf);
}
END_TEST

START_TEST(test_literal_mismatch) {
  const char *str = "abc";
  int res;
  int val, val1;
  res = s21_sscanf(str, "a%d", &val);
  int orig_res = sscanf(str, "a%d", &val1);
  ck_assert_int_eq(res, orig_res);

  res = s21_sscanf("xbc", "a%d", &val);
  orig_res = sscanf("xbc", "a%d", &val1);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_percent_literal) {
  const char *str = "100% error";
  int res;
  int val;
  char buf[10];
  res = s21_sscanf(str, "%d%% %s", &val, buf);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(val, 100);
  ck_assert_str_eq(buf, "error");

  int orig_res, orig_val;
  char orig_buf[10];
  orig_res = sscanf(str, "%d%% %s", &orig_val, orig_buf);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(val, orig_val);
  ck_assert_str_eq(buf, orig_buf);
}
END_TEST

START_TEST(test_float_l_L_mod) {
  const char *str = "3.14";
  int res;
  long double ld;
  res = s21_sscanf(str, "%Le", &ld);
  ck_assert_int_eq(res, 1);
  ck_assert_ldouble_eq_tol(ld, 3.14L, 1e-6);

  double d;
  res = s21_sscanf(str, "%le", &d);
  ck_assert_int_eq(res, 1);
  ck_assert_double_eq_tol(d, 3.14, 1e-6);

  long double orig_ld;
  int orig_res = sscanf(str, "%Le", &orig_ld);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_h_mod_signed_unsigned) {
  const char *str = "-128 255";
  int res, orig_res;
  short s_val;
  unsigned short us_val;
  res = s21_sscanf(str, "%hd %hu", &s_val, &us_val);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(s_val, -128);
  ck_assert_int_eq(us_val, 255);

  short orig_s;
  unsigned short orig_us;
  orig_res = sscanf(str, "%hd %hu", &orig_s, &orig_us);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(s_val, orig_s);
  ck_assert_int_eq(us_val, orig_us);
}
END_TEST

START_TEST(test_skip_spaces_c_n) {
  const char *str = " a";
  int res;
  char ch;
  res = s21_sscanf(str, "%c", &ch);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(ch, ' ');
  char s[10];
  int n;
  res = s21_sscanf("abc", "%s%n", s, &n);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(n, 3);

  char orig_ch;
  int orig_res = sscanf(str, "%c", &orig_ch);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(ch, orig_ch);
}
END_TEST

START_TEST(test_i_hex_letters) {
  const char *str = "0xa 0Xb";
  int res;
  int val1, val2;
  res = s21_sscanf(str, "%i %i", &val1, &val2);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(val1, 10);
  ck_assert_int_eq(val2, 11);

  int orig_res = sscanf(str, "%i %i", &val1, &val2);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_u_x_capital_letters) {
  const char *str = "0XA 0XB";
  int res;
  unsigned int val1, val2;
  res = s21_sscanf(str, "%x %X", &val1, &val2);
  ck_assert_int_eq(res, 2);
  ck_assert_int_eq(val1, 10);
  ck_assert_int_eq(val2, 11);
  unsigned int orig_val1, orig_val2;
  int orig_res = sscanf(str, "%x %X", &orig_val1, &orig_val2);
  ck_assert_int_eq(res, orig_res);
  res = s21_sscanf("123", "%u", &val1);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(val1, 123);
}
END_TEST

START_TEST(test_float_sign_no_digit) {
  const char *str = "+ ";
  int res;
  float f;
  res = s21_sscanf(str, "%f", &f);
  ck_assert_int_eq(res, 0);

  res = s21_sscanf("+3.14", "%f", &f);
  ck_assert_int_eq(res, 1);
  ck_assert_float_eq_tol(f, 3.14f, 1e-6);

  float orig_f;
  int orig_res = sscanf("+3.14", "%f", &orig_f);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

END_TEST

START_TEST(test_p_full) {
  const char *str = "0xdeadbeef";
  int res;
  void *ptr;
  res = s21_sscanf(str, "%p", &ptr);
  ck_assert_int_eq(res, 1);
  ck_assert_ptr_ne(ptr, NULL);
  void *orig_ptr;
  int orig_res = sscanf(str, "%p", &orig_ptr);
  ck_assert_int_eq(res, orig_res);
  res = s21_sscanf("0x1", "%*p", &ptr);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_n_full) {
  const char *str = "abc ";
  int res;
  int n;
  res = s21_sscanf(str, "%*s %n", &n);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(n, 4);
  char s[10];
  res = s21_sscanf("hi", "%s%n", s, &n);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(n, 2);

  int orig_n, orig_res;
  orig_res = sscanf("hi", "%s%n", s, &orig_n);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(n, orig_n);
}
END_TEST

START_TEST(test_percent_mismatch) {
  const char *str = "100x";
  int res;
  int val;
  res = s21_sscanf(str, "%d%%", &val);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(val, 100);

  res = s21_sscanf("100%", "%d%%", &val);

  int orig_val, orig_res = sscanf("100%", "%d%%", &orig_val);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(val, orig_val);
}
END_TEST

START_TEST(test_literals_and_mismatch) {
  const char *str = "a 123";
  int res;
  int val;
  res = s21_sscanf(str, "a %d", &val);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(val, 123);

  res = s21_sscanf("b 123", "a %d", &val);
  ck_assert_int_eq(res, 0);

  res = s21_sscanf(" 123", " %d", &val);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(val, 123);

  int orig_val, orig_res = sscanf(str, "a %d", &orig_val);
  ck_assert_int_eq(res, orig_res);
}
END_TEST

START_TEST(test_s_with_l) {
  const char *str = "hello";
  int res;
  wchar_t wbuf[10];
  res = s21_sscanf(str, "%ls", wbuf);
  wchar_t orig_wbuf[10];
  int orig_res = sscanf(str, "%ls", orig_wbuf);
  ck_assert_int_eq(res, orig_res);
  ck_assert_int_eq(wcscmp(wbuf, orig_wbuf), 0);
  res = s21_sscanf("hello", "%*ls", wbuf);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(test_c_without_l) {
  char c = 0;
  s21_sscanf("a", "%c", &c);
  ck_assert_int_eq(c, 'a');
}
END_TEST

START_TEST(test_d_suppress) {
  int num = 999;
  s21_sscanf("123", "%*d", &num);
  ck_assert_int_eq(num, 999);
}
END_TEST

START_TEST(test_sscanf_char_basic) {
  char result;
  char input[] = "A";
  int ret = s21_sscanf(input, "%c", &result);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(result, 'A');
}
END_TEST

START_TEST(test_sscanf_char_with_spaces) {
  char result;
  char input[] = " A";
  int ret = s21_sscanf(input, "%c", &result);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(result, ' ');
}
END_TEST
START_TEST(test_sscanf_int_with_leading_spaces) {
  int result;
  char input[] = "  123";
  int ret = s21_sscanf(input, "%d", &result);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_sscanf_hex_with_leading_spaces) {
  int result;
  char input[] = "   ABC";
  int ret = s21_sscanf(input, "%x", &result);
  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(result, 0xABC);
}
END_TEST

START_TEST(test_sscanf_n_specifier) {
  int result, count, result1, count1;
  char input[] = "124abc";
  int ret = s21_sscanf(input, "%d%n", &result, &count);
  int ret1 = sscanf(input, "%d%n", &result1, &count1);

  ck_assert_int_eq(ret, ret1);
  ck_assert_int_eq(result, result1);
  ck_assert_int_eq(count, count1);
}
END_TEST

START_TEST(test_sscanf_percent_literal_fail) {
  int result;
  char input[] = "abc";
  int ret = s21_sscanf(input, "%% %d", &result);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(test_sscanf_int_with_width_zero) {
  int result1, result;
  char input[] = "123456789";
  char fmt[] = "%0d";
  int ret = s21_sscanf(input, fmt, &result);
  int ret1 = s21_sscanf(input, fmt, &result1);
  ck_assert_int_eq(ret, ret1);
  ck_assert_int_eq(result, result1);
}
END_TEST

START_TEST(test_sscanf_octal_invalid_digit) {
  unsigned int result, result1;
  char input[] = "789";
  int ret = s21_sscanf(input, "%o", &result);
  int ret1 = sscanf(input, "%o", &result1);
  ck_assert_int_eq(ret, ret1);
  ck_assert_int_eq(result, result1);
}
END_TEST

START_TEST(test_sscanf_octal_invalid_digit2) {
  int result, result1;
  char input[] = "0789";
  int ret = s21_sscanf(input, "%i", &result);
  int ret1 = sscanf(input, "%i", &result1);
  ck_assert_int_eq(ret, ret1);
  ck_assert_uint_eq(result, result1);
}
END_TEST

START_TEST(suppress_int) {
  int b;
  const char *str = "123 456";
  int res = s21_sscanf(str, "%*d %d", &b);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(b, 456);
}
END_TEST

START_TEST(width_int) {
  int a;
  const char *str = "12345";
  int res = s21_sscanf(str, "%2d", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(a, 12);
}
END_TEST

START_TEST(len_mod_h) {
  short a;
  const char *str = "123";
  int res = s21_sscanf(str, "%hd", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(a, 123);
}
END_TEST

START_TEST(len_mod_l) {
  long a;
  const char *str = "123";
  int res = s21_sscanf(str, "%ld", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(a, 123);
}
END_TEST

START_TEST(len_mod_L) {
  long double a;
  const char *str = "1.23";
  int res = s21_sscanf(str, "%Lf", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_double_eq(a, 1.23);
}
END_TEST

START_TEST(format_i_hex) {
  int a;
  const char *str = "0x1a";
  int res = s21_sscanf(str, "%i", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(a, 26);
}
END_TEST

START_TEST(format_u_hex) {
  unsigned int a;
  const char *str = "1a";
  int res = s21_sscanf(str, "%x", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_uint_eq(a, 26);
}
END_TEST

START_TEST(format_c_suppress) {
  char a;
  const char *str = "ab";
  int res = s21_sscanf(str, "%*c %c", &a);
  ck_assert_int_eq(res, 1);
  ck_assert_int_eq(a, 'b');
}
END_TEST

START_TEST(format_s_suppress) {
  char buf[10];
  const char *str = "hello world";
  int res = s21_sscanf(str, "%*s %s", buf);
  ck_assert_int_eq(res, 1);
  ck_assert_str_eq(buf, "world");
}
END_TEST

START_TEST(format_p) {
  void *p, *p1;
  const char *str = "0x123";
  int res = s21_sscanf(str, "%p", &p);
  int res1 = sscanf(str, "%p", &p1);
  ck_assert_int_eq(res, res1);
}
END_TEST

START_TEST(format_n) {
  int pos, pos1, count, count1;
  const char *str = "123";
  int res = s21_sscanf(str, "%d%n", &pos, &count);
  int res1 = sscanf(str, "%d%n", &pos1, &count1);
  ck_assert_int_eq(res, res1);
  ck_assert_int_eq(pos, pos1);
}
END_TEST

START_TEST(format_percent) {
  const char *str = "%%";
  int res = s21_sscanf(str, "%%");
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(mismatch_break) {
  int a;
  const char *str = "abc";
  int res = s21_sscanf(str, "%d", &a);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(format_null) {
  char q, q1;
  char *s_n = NULL;
  int ret = s21_sscanf("a", s_n, &q);
  int ret1 = sscanf("a", s_n, &q1);
  ck_assert_int_eq(ret, ret1);
}
END_TEST

Suite *suite_s21_sscanf(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, format_null);
  tcase_add_test(tc, test_sscanf_octal_invalid_digit2);

  tcase_add_test(tc, test_sscanf_octal_invalid_digit);
  tcase_add_test(tc, test_sscanf_percent_literal_fail);
  tcase_add_test(tc, suppress_int);
  tcase_add_test(tc, width_int);
  tcase_add_test(tc, len_mod_h);
  tcase_add_test(tc, len_mod_l);
  tcase_add_test(tc, len_mod_L);
  tcase_add_test(tc, format_i_hex);
  tcase_add_test(tc, format_u_hex);
  tcase_add_test(tc, format_c_suppress);

  tcase_add_test(tc, format_s_suppress);

  tcase_add_test(tc, format_p);
  tcase_add_test(tc, format_n);
  tcase_add_test(tc, format_percent);
  tcase_add_test(tc, mismatch_break);
  tcase_add_test(tc, test_sscanf_int_with_width_zero);

  tcase_add_test(tc, test_sscanf_n_specifier);
  tcase_add_test(tc, test_sscanf_hex_with_leading_spaces);
  tcase_add_test(tc, test_sscanf_int_with_leading_spaces);
  tcase_add_test(tc, test_sscanf_char_with_spaces);
  tcase_add_test(tc, test_sscanf_char_basic);

  tcase_add_test(tc, test_s21_sscanf_c);
  tcase_add_test(tc, test_s21_sscanf_d);
  tcase_add_test(tc, test_s21_sscanf_i);
  tcase_add_test(tc, test_s21_sscanf_e);
  tcase_add_test(tc, test_s21_sscanf_E);
  tcase_add_test(tc, test_s21_sscanf_f);
  tcase_add_test(tc, test_s21_sscanf_g);
  tcase_add_test(tc, test_s21_sscanf_G);
  tcase_add_test(tc, test_s21_sscanf_o);
  tcase_add_test(tc, test_s21_sscanf_s);
  tcase_add_test(tc, test_s21_sscanf_u);
  tcase_add_test(tc, test_s21_sscanf_x);
  tcase_add_test(tc, test_s21_sscanf_X);
  tcase_add_test(tc, test_s21_sscanf_p);
  tcase_add_test(tc, test_s21_sscanf_n);
  tcase_add_test(tc, test_s21_sscanf_percent);
  tcase_add_test(tc, test_s21_sscanf_width_number_d);
  tcase_add_test(tc, test_s21_sscanf_width_number_s);
  tcase_add_test(tc, test_s21_sscanf_width_star);
  tcase_add_test(tc, test_s21_sscanf_length_h_d);
  tcase_add_test(tc, test_s21_sscanf_length_h_u);
  tcase_add_test(tc, test_s21_sscanf_length_l_d);
  tcase_add_test(tc, test_s21_sscanf_length_l_u);
  tcase_add_test(tc, test_s21_sscanf_length_L_e);
  tcase_add_test(tc, test_s21_sscanf_length_L_f);
  tcase_add_test(tc, test_s21_sscanf_combined_d_u);
  tcase_add_test(tc, test_s21_sscanf_combined_s_c);
  tcase_add_test(tc, test_s21_sscanf_combined_f_g);
  tcase_add_test(tc, test_s21_sscanf_combined_o_x_X);
  tcase_add_test(tc, test_s21_sscanf_combined_width_precision);

  tcase_add_test(tc, test_hex_signed);
  tcase_add_test(tc, test_octal_signed);

  tcase_add_test(tc, test_d_suppress);

  tcase_add_test(tc, test_c_without_l);

  tcase_add_test(tc, test_float_sign);
  tcase_add_test(tc, test_float_exp_sign_neg);
  tcase_add_test(tc, test_p_specifier);
  tcase_add_test(tc, test_n_specifier);
  tcase_add_test(tc, test_c_with_l);
  tcase_add_test(tc, test_s_with_l);
  tcase_add_test(tc, test_c_with_l);
  tcase_add_test(tc, test_width_multi);
  tcase_add_test(tc, test_literal_mismatch);
  tcase_add_test(tc, test_percent_literal);
  tcase_add_test(tc, test_float_l_L_mod);
  tcase_add_test(tc, test_h_mod_signed_unsigned);
  tcase_add_test(tc, test_skip_spaces_c_n);
  tcase_add_test(tc, test_i_hex_letters);
  tcase_add_test(tc, test_u_x_capital_letters);
  tcase_add_test(tc, test_float_sign_no_digit);

  tcase_add_test(tc, test_p_full);
  tcase_add_test(tc, test_n_full);
  tcase_add_test(tc, test_percent_mismatch);
  tcase_add_test(tc, test_literals_and_mismatch);

  suite_add_tcase(s, tc);
  return s;
}
