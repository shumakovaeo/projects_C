#include "tests.h"

START_TEST(test_add_1) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 0;

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_2) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 20;

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 30);
}
END_TEST

START_TEST(test_add_3) {
  // 10 + (-20) = -10
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 20;
  set_sign(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_add_4) {
  //-10 + (-20) = -30
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 10;
  set_sign(&val1, 1);
  val2.bits[0] = 20;
  set_sign(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 30);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_add_5) {
  // 1.5 + 2.5 = 4.0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 15;
  set_scale(&val1, 1);

  val2.bits[0] = 25;
  set_scale(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 40);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_6) {
  // 1.55 (scale 2) + 2.5 (scale 1) = 4.05
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 155;
  set_scale(&val1, 2);

  val2.bits[0] = 25;
  set_scale(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 405);
  ck_assert_int_eq(get_scale(result), 2);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_7) {
  // MAX + 1 -> ощибка = 1
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 1;

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_add_8) {
  //-MAX + (-1) -> ошибка = 2
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_sign(&val1, 1);

  val2.bits[0] = 1;
  set_sign(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 2);
  ck_assert_int_eq(result.bits[0], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_9) {
  // банковское округление
  // 79228162514264337593543950335 (макс значение) + (-0.6)
  // 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 6;
  set_sign(&val2, 1);
  set_scale(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFE);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_10) {
  // 79228162514264337593543950334 + 1 = MAX
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 1;

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_11) {
  // MAX + 0 = MAX
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 0;
  set_scale(&val2, 0);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_12) {
  // 79228162514264337593543950334 + 0.5 =
  // 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 5;
  set_scale(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFE);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_13) {
  // 79228162514264337593543950334 + 0.6 =
  // 79228162514264337593543950335
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 6;
  set_scale(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_add_14) {
  // 79228162514264337593543950333 + 0.5 =
  // 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal result = {0};

  val1.bits[0] = 0xFFFFFFFD;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 5;
  set_scale(&val2, 1);

  int code = s21_add(val1, val2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFE);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

Suite *s21_test_add(void) {
  Suite *s = suite_create("S21_ADD");
  TCase *tc = tcase_create("s21_add");

  tcase_add_test(tc, test_add_1);
  tcase_add_test(tc, test_add_2);
  tcase_add_test(tc, test_add_3);
  tcase_add_test(tc, test_add_4);
  tcase_add_test(tc, test_add_5);
  tcase_add_test(tc, test_add_6);
  tcase_add_test(tc, test_add_7);
  tcase_add_test(tc, test_add_8);
  tcase_add_test(tc, test_add_9);
  tcase_add_test(tc, test_add_10);
  tcase_add_test(tc, test_add_11);
  tcase_add_test(tc, test_add_12);
  tcase_add_test(tc, test_add_13);
  tcase_add_test(tc, test_add_14);

  suite_add_tcase(s, tc);
  return s;
}