#include "tests.h"

START_TEST(test_is_less_1) {
  // 5 < 10 (положительные числа)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_2) {
  // 5 < 5 (равные числа)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_3) {
  // -10 < -5 (отрицательные числа)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 5;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_4) {
  // -5 < 5 (разные знаки)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_5) {
  // 0 < 5 (ноль меньше положительного)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val2.bits[0] = 5;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_6) {
  // 5 < 0 (положительное больше нуля)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_7) {
  // 5.5 < 5.6 (числа с дробной частью)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 56;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_8) {
  // Большие числа: 2^32-1 < 2^32
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 4294967295u;
  val2.bits[0] = 4294967295u;
  val2.bits[1] = 1;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_9) {
  // Максимальные значения равны
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_10) {
  // -5 < 0 (отрицательное меньше нуля)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_11) {
  // 0 < -5 (ноль больше отрицательного)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val2.bits[0] = 5;
  set_sign(&val2, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_12) {
  // 5.0 < 5 (масштабы разные, значения равны)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 50;
  val2.bits[0] = 5;
  set_scale(&val1, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_13) {
  // 0.01 < MAX
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 1;
  set_scale(&val1, 2);

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_14) {
  //-79228162514.264337593543950335 <
  //-792281.62514264337593543950335
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 18);
  set_sign(&val1, 1);

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_scale(&val2, 23);
  set_sign(&val2, 1);

  int result = s21_is_less(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *s21_test_is_less(void) {
  Suite *s = suite_create("S21_IS_LESS");
  TCase *tc = tcase_create("s21_is_less");

  tcase_add_test(tc, test_is_less_1);
  tcase_add_test(tc, test_is_less_2);
  tcase_add_test(tc, test_is_less_3);
  tcase_add_test(tc, test_is_less_4);
  tcase_add_test(tc, test_is_less_5);
  tcase_add_test(tc, test_is_less_6);
  tcase_add_test(tc, test_is_less_7);
  tcase_add_test(tc, test_is_less_8);
  tcase_add_test(tc, test_is_less_9);
  tcase_add_test(tc, test_is_less_10);
  tcase_add_test(tc, test_is_less_11);
  tcase_add_test(tc, test_is_less_12);
  tcase_add_test(tc, test_is_less_13);
  tcase_add_test(tc, test_is_less_14);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(test_is_less_or_equal_1) {
  // 5 <= 10 (положительные числа, меньше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_2) {
  // 5 <= 5 (равные положительные числа)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_3) {
  // 10 <= 5 (положительные числа, больше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 5;

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_4) {
  // -10 <= -5 (отрицательные числа, меньше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 5;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_5) {
  // -5 <= -5 (равные отрицательные числа)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_6) {
  // -5 <= -10 (отрицательные числа, больше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_7) {
  // -5 <= 5 (разные знаки, отрицательное меньше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_8) {
  // 5 <= -5 (разные знаки, положительное больше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;
  set_sign(&val2, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_9) {
  // Максимальные значения равны
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_10) {
  // 5 <= 0 (положительное больше нуля)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_is_less_or_equal_11) {
  // 0 <= 0 (нули равны)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_12) {
  // -5 <= 0 (отрицательное меньше нуля)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 5;
  set_sign(&val1, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_13) {
  // 5.0 <= 5 (разные масштабы, значения равны)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 50;
  val2.bits[0] = 5;
  set_scale(&val1, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_14) {
  // 5.5 <= 5.6 (дробные числа, меньше)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 56;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_is_less_or_equal_15) {
  // 5.5 <= 5.5 (дробные числа, равны)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 55;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_is_less_or_equal(val1, val2);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *s21_test_is_less_or_equal(void) {
  Suite *s = suite_create("S21_IS_LESS_OR_EQUAL");
  TCase *tc = tcase_create("s21_is_less_or_equal");

  // Тесты для s21_is_less_or_equal
  tcase_add_test(tc, test_is_less_or_equal_1);
  tcase_add_test(tc, test_is_less_or_equal_2);
  tcase_add_test(tc, test_is_less_or_equal_3);
  tcase_add_test(tc, test_is_less_or_equal_4);
  tcase_add_test(tc, test_is_less_or_equal_5);
  tcase_add_test(tc, test_is_less_or_equal_6);
  tcase_add_test(tc, test_is_less_or_equal_7);
  tcase_add_test(tc, test_is_less_or_equal_8);
  tcase_add_test(tc, test_is_less_or_equal_9);
  tcase_add_test(tc, test_is_less_or_equal_10);
  tcase_add_test(tc, test_is_less_or_equal_11);
  tcase_add_test(tc, test_is_less_or_equal_12);
  tcase_add_test(tc, test_is_less_or_equal_13);
  tcase_add_test(tc, test_is_less_or_equal_14);
  tcase_add_test(tc, test_is_less_or_equal_15);

  suite_add_tcase(s, tc);
  return s;
}