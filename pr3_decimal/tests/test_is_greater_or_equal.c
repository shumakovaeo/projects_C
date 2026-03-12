#include "tests.h"

//----------------------------------s21_is_greater-------------------------------------

START_TEST(test_s21_is_greater_1) {
  // 5 > 10 (false)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  // 10 > 5 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 5;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  // 5 > 5 (false)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  // -5 > 5 (false)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_5) {
  // 5 > -5 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val2, 1);

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_6) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 1;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0;
  val1.bits[1] = 1;  // 1 * 2^32

  // val2 = 2^32 - 1 = 4294967295
  val2.bits[0] = 0xFFFFFFFF;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);  // 2^32 > (2^32 - 1)
}
END_TEST

START_TEST(test_s21_is_greater_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // val1 = 2^64 = 18446744073709551616
  val1.bits[0] = 0;
  val1.bits[1] = 0;
  val1.bits[2] = 1;  // 1 * 2^64

  // val2 = 2^64 - 1
  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);  // 2^64 > (2^64 - 1)
}
END_TEST

START_TEST(test_s21_is_greater_9) {
  // Максимальное decimal > почти максимальное
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // максимальное decimal (все биты = 1)
  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  // максимальное - 1
  val2.bits[0] = 0xFFFFFFFE;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // 12345.6789
  val1.bits[0] = 123456789;
  set_scale(&val1, 4);

  // 1234567890000
  val2.bits[0] = 0x49A5FBA0;  // 1234567840
  val2.bits[1] = 0x11F;       // 287

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);  // 1.23456789 < 1234567890000
}
END_TEST

START_TEST(test_s21_is_greater_11) {
  // 5.0 > 5 (false)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 50;
  val2.bits[0] = 5;
  set_scale(&val1, 1);

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_12) {
  // Большое положительное > большое отрицательное
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // val1 = 10000000000000000000
  val1.bits[0] = 0x6FC23AC0;
  val1.bits[1] = 0x8AC72304;

  // val2 = -10000000000000000000
  val2.bits[0] = 0x6FC23AC0;
  val2.bits[1] = 0x8AC72304;
  set_sign(&val2, 1);

  int result = s21_is_greater(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *s21_test_is_greater(void) {
  Suite *s = suite_create("S21_IS_GREATER");
  TCase *tc = tcase_create("s21_is_greater");

  tcase_add_test(tc, test_s21_is_greater_1);
  tcase_add_test(tc, test_s21_is_greater_2);
  tcase_add_test(tc, test_s21_is_greater_3);
  tcase_add_test(tc, test_s21_is_greater_4);
  tcase_add_test(tc, test_s21_is_greater_5);
  tcase_add_test(tc, test_s21_is_greater_6);
  tcase_add_test(tc, test_s21_is_greater_7);
  tcase_add_test(tc, test_s21_is_greater_8);
  tcase_add_test(tc, test_s21_is_greater_9);
  tcase_add_test(tc, test_s21_is_greater_10);
  tcase_add_test(tc, test_s21_is_greater_11);
  tcase_add_test(tc, test_s21_is_greater_12);

  suite_add_tcase(s, tc);
  return s;
}

//----------------------------------s21_s21_is_greater_or_equal-------------------------------------

START_TEST(test_s21_is_greater_or_equal_1) {
  // 5 >= 10 (false)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  // 10 >= 5 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 5;

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  // 5 >= 5 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  // -5 >= 5 (false)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  // 5 >= -5 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val2, 1);

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_6) {
  // -5 >= -10 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_7) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0;
  val1.bits[1] = 1;

  val2.bits[0] = 0xFFFFFFFF;

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);  // 2^32 >= (2^32 - 1)
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // val1 = 2^64
  val1.bits[0] = 0;
  val1.bits[1] = 0;
  val1.bits[2] = 1;

  // val2 = 2^64 - 1
  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);  // 2^64 >= (2^64 - 1)
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_9) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  //-10000000000
  val1.bits[0] = 0x540BE400;
  val1.bits[1] = 0x2;
  set_sign(&val1, 1);

  //-20000000000
  val2.bits[0] = 0x817C8200;
  val2.bits[1] = 0x4;
  set_sign(&val2, 1);

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);  // -10 млрд >= -20 млрд
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // 12345.6789
  val1.bits[0] = 123456789;
  set_scale(&val1, 4);

  // 1234567890000
  val2.bits[0] = 0x49A5FBA0;
  val2.bits[1] = 0x11F;

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);  // 1.23456789 < 1234567890000
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_11) {
  // 5.0 >= 5 (true)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 50;
  val2.bits[0] = 5;
  set_scale(&val1, 1);

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  // 10000000000000000000
  val1.bits[0] = 0x6FC23AC0;
  val1.bits[1] = 0x8AC72304;

  // 10000000000000000000
  val2.bits[0] = 0x6FC23AC0;
  val2.bits[1] = 0x8AC72304;
  set_sign(&val2, 1);

  int result = s21_is_greater_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *s21_test_is_greater_or_equal(void) {
  Suite *s = suite_create("S21_IS_GREATER_OR_EQUAL");
  TCase *tc = tcase_create("s21_is_greater_or_equal");

  tcase_add_test(tc, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc, test_s21_is_greater_or_equal_5);
  tcase_add_test(tc, test_s21_is_greater_or_equal_6);
  tcase_add_test(tc, test_s21_is_greater_or_equal_7);
  tcase_add_test(tc, test_s21_is_greater_or_equal_8);
  tcase_add_test(tc, test_s21_is_greater_or_equal_9);
  tcase_add_test(tc, test_s21_is_greater_or_equal_10);
  tcase_add_test(tc, test_s21_is_greater_or_equal_11);
  tcase_add_test(tc, test_s21_is_greater_or_equal_12);

  suite_add_tcase(s, tc);
  return s;
}