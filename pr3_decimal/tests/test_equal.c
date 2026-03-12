#include "tests.h"

//----------------------------------s21_is_equal-------------------------------------
START_TEST(test_is_equal_1) {
  // 5 != 10
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_equal_2) {
  // 5 == 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_3) {
  // -5 != 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_equal_4) {
  // -5 == -5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_5) {
  // 0 == 0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_6) {
  // -0 == +0 (true) - нули с разными знаками
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  set_sign(&val1, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_7) {
  // 5.5 == 5.5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 55;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_8) {
  // 5.5 == 5.6
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 56;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_equal_9) {
  // 5.0 == 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 50;
  val2.bits[0] = 5;
  set_scale(&val1, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_10) {
  // 50 != 5.0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 50;
  val2.bits[0] = 50;
  set_scale(&val2, 1);

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_equal_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 0xFFFFFFFE;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_equal_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_equal_13) {
  // 1.0000000000000000000000000000 == 1
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0x10000000;
  val1.bits[1] = 0x3E250261;
  val1.bits[2] = 0x204FCE5E;
  set_scale(&val1, 28);

  val2.bits[0] = 0x00000001;
  val2.bits[1] = 0x00000000;
  val2.bits[2] = 0x00000000;

  int result = s21_is_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}

Suite *s21_test_is_equal(void) {
  Suite *s = suite_create("S21_IS_EQUAL");
  TCase *tc = tcase_create("s21_is_equal");

  tcase_add_test(tc, test_is_equal_1);
  tcase_add_test(tc, test_is_equal_2);
  tcase_add_test(tc, test_is_equal_3);
  tcase_add_test(tc, test_is_equal_4);
  tcase_add_test(tc, test_is_equal_5);
  tcase_add_test(tc, test_is_equal_6);
  tcase_add_test(tc, test_is_equal_7);
  tcase_add_test(tc, test_is_equal_8);
  tcase_add_test(tc, test_is_equal_9);
  tcase_add_test(tc, test_is_equal_10);
  tcase_add_test(tc, test_is_equal_11);
  tcase_add_test(tc, test_is_equal_12);
  tcase_add_test(tc, test_is_equal_13);

  suite_add_tcase(s, tc);
  return s;
}

//----------------------------------s21_is_not_equal-------------------------------------

START_TEST(test_is_not_equal_1) {
  // 5 != 10
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_not_equal_2) {
  // 5 != 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_3) {
  // -5 != 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_not_equal_4) {
  // -5 != -5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_5) {
  // 0 != 0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_6) {
  // -0 != +0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  set_sign(&val1, 1);

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_7) {
  // 5.5 != 5.6
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 56;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_not_equal_8) {
  // 5.5 != 5.5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 55;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_9) {
  // 5.1 != 5.10
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 51;
  val2.bits[0] = 510;
  set_scale(&val1, 1);
  set_scale(&val2, 2);

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_not_equal_10) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 0xFFFFFFFE;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_not_equal_11) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[1] = 0x00000001;

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[1] = 0x00000000;

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_not_equal_12) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 0xFFFFFFFE;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_not_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *s21_test_is_not_equal(void) {
  Suite *s = suite_create("S21_IS_NOT_EQUAL");
  TCase *tc = tcase_create("s21_is_not_equal");

  tcase_add_test(tc, test_is_not_equal_1);
  tcase_add_test(tc, test_is_not_equal_2);
  tcase_add_test(tc, test_is_not_equal_3);
  tcase_add_test(tc, test_is_not_equal_4);
  tcase_add_test(tc, test_is_not_equal_5);
  tcase_add_test(tc, test_is_not_equal_6);
  tcase_add_test(tc, test_is_not_equal_7);
  tcase_add_test(tc, test_is_not_equal_8);
  tcase_add_test(tc, test_is_not_equal_9);
  tcase_add_test(tc, test_is_not_equal_10);
  tcase_add_test(tc, test_is_not_equal_11);
  tcase_add_test(tc, test_is_not_equal_12);

  suite_add_tcase(s, tc);
  return s;
}
