#include "tests.h"

START_TEST(test_from_decimal_to_float_1) {
  s21_decimal val = {0};
  float result = 0.0f;

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_2) {
  // 123.45
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 12345;
  set_scale(&val, 2);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 123.45f);
}
END_TEST

START_TEST(test_from_decimal_to_float_3) {
  // -678.9
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 6789;
  set_scale(&val, 1);
  set_sign(&val, 1);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, -678.9f);
}
END_TEST

START_TEST(test_from_decimal_to_float_4) {
  // 9999999
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 9999999;
  set_scale(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 9999999.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_5) {
  // 1e-10
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 1;
  set_scale(&val, 10);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 1e-10f);
}
END_TEST

START_TEST(test_from_decimal_to_float_6) {
  // 1e-29 -> ошибка конвертации = 1
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 1;
  set_scale(&val, 29);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 1);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_7) {
  // 1.23456789 -> 1.234568
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 123456789;
  set_scale(&val, 8);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 1.234568f);
}
END_TEST

START_TEST(test_from_decimal_to_float_8) {
  // 2.5
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 25;
  set_scale(&val, 1);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 2.5f);
}
END_TEST

START_TEST(test_from_decimal_to_float_9) {
  // 123412340000000 -> 123412300000000 -> 1.234123e+14
  s21_decimal val = {0};
  val.bits[0] = 0x2CAFC500;
  val.bits[1] = 0x0000703E;
  set_scale(&val, 0);

  float result = 0.0f;
  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 1.234123e+14f);
}
END_TEST

START_TEST(test_from_decimal_to_float_10) {
  // 123.4567 -> 123.4567
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 1234567;
  set_scale(&val, 4);

  int ret = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(ret, 0);
  ck_assert_float_eq(result, 123.4567f);
}
END_TEST

START_TEST(test_from_decimal_to_float_11) {
  // 1.2345674 -> 1.234567
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 12345674;
  set_scale(&val, 7);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 1.234567f);
}
END_TEST

START_TEST(test_from_decimal_to_float_12) {
  // 1.2345665 -> 1.234566
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 12345665;
  set_scale(&val, 7);

  int ret = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(ret, 0);
  ck_assert_float_eq(result, 1.234566f);
}
END_TEST

START_TEST(test_from_decimal_to_float_13) {
  // 1234567.89 -> 1234568.0
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 123456789;
  set_scale(&val, 2);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, 1234568.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_14) {
  // 0.0000000007922816 -> 7922816 -> 7.922816e-10
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922816e-10f;
  val.bits[0] = 0x0078E480;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 16);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_15) {
  // 0.000000000792281622 -> 792281600 -> 7.922816E-10
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922816e-10;
  val.bits[0] = 0x2F394216;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 18);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_16) {
  // 7922816.9 -> 7922817.0 -> 7922817
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7922817.0f;
  val.bits[0] = 0x04B8ED09;
  val.bits[1] = 0x00000000;
  set_scale(&val, 1);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_17) {
  // 792281611 -> 792281600 -> 7.922816E+08
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922816e+08;
  val.bits[0] = 0x2F39420B;
  val.bits[1] = 0x00000000;
  set_scale(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_18) {
  // 7922816.11 -> 7922816.00 -> 7922816
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7922816.00f;
  val.bits[0] = 0x2F39420B;
  val.bits[1] = 0x00000000;
  set_scale(&val, 2);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_19) {
  // 79228162.5142 -> 79228160 -> 7.922816E+07
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 79228160.0f;
  val.bits[0] = 0x77AA3236;
  val.bits[1] = 0x000000B8;
  set_scale(&val, 4);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_20) {
  // 79228162514264337593543950335 ->
  // 79228160000000000000000000000 -> 7.922816E+28
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922816e+28f;
  val.bits[0] = 0xFFFFFFFF;
  val.bits[1] = 0xFFFFFFFF;
  val.bits[2] = 0xFFFFFFFF;
  set_scale(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_21) {
  // 0.7922816251426433759354395033 ->
  // 0.7922816000000000000000000000 -> 0.7922816
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 0.7922816f;
  val.bits[0] = 0x99999999;
  val.bits[1] = 0x99999999;
  val.bits[2] = 0x19999999;
  set_scale(&val, 28);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_22) {
  // 792281625142643375935439.50335 ->
  // 792281600000000000000000.00000 -> 7.922816E+23
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922816e+23f;
  val.bits[0] = 0xFFFFFFFF;
  val.bits[1] = 0xFFFFFFFF;
  val.bits[2] = 0xFFFFFFFF;
  set_scale(&val, 5);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_23) {
  //-10000003.5 -> -10000000 -> -1E+07
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = -10000000.0f;
  val.bits[0] = 0x05F5E123;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 1);
  set_sign(&val, 1);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_24) {
  // 1000002.5 -> 1000002.0 -> 1000002
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 1000002.0f;
  val.bits[0] = 0x00989699;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 1);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_25) {
  // 1000003.5 -> 1000004.0 -> 1000004
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 1000004.0f;
  val.bits[0] = 0x009896A3;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 1);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_26) {
  // 7922812.5142 -> 7922813.0 -> 7922813
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7922813.0f;
  val.bits[0] = 0x725D3FD6;
  val.bits[1] = 0x00000012;
  val.bits[2] = 0x00000000;
  set_scale(&val, 4);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_27) {
  // 0.79228165 -> 0.7922816 -> 0.7922816
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 0.7922816f;
  val.bits[0] = 0x04B8ED05;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 8);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_28) {
  // 0.79228135 -> 0.7922814 -> 0.7922814
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 0.7922814f;
  val.bits[0] = 0x04B8ECE7;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 8);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_29) {
  //-0.0000000000000000079228135111 -> -7922814 -> -7.922814E-18
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = -7.922814e-18f;
  val.bits[0] = 0x725D66C7;
  val.bits[1] = 0x00000012;
  val.bits[2] = 0x00000000;
  set_scale(&val, 28);
  set_sign(&val, 1);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_30) {
  // 0.0000000000000000079228145 -> 7922814 -> 7.922814E-18
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922814e-18f;
  val.bits[0] = 0x04B8ECF1;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 25);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_31) {
  // 0.0000000000000000079228115 -> 7922812 -> 7.922812E-18
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.922812e-18f;
  val.bits[0] = 0x04B8ECD3;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 25);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_32) {
  // 0.0000000000000000079228199 -> 792282 -> 7.92282E-18
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 7.92282e-18f;
  val.bits[0] = 0x04B8ED27;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 25);
  set_sign(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_33) {
  //-0.000 -> 0
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = 0.0f;
  val.bits[0] = 0x00000000;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_scale(&val, 3);
  set_sign(&val, 1);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_34) {
  //-0 -> -0.000000e+00
  s21_decimal val = {0};
  float result = 0.0f;

  float expected_float = -0.0f;
  val.bits[0] = 0x00000000;
  val.bits[1] = 0x00000000;
  val.bits[2] = 0x00000000;
  set_sign(&val, 1);
  set_scale(&val, 0);

  int code = s21_from_decimal_to_float(val, &result);

  ck_assert_int_eq(code, 0);
  ck_assert_float_eq(result, expected_float);
}
END_TEST

START_TEST(test_from_decimal_to_float_35) {
  s21_decimal val = {0};
  float result = 0.0f;

  val.bits[0] = 10;
  set_scale(&val, -1);

  int code = s21_from_decimal_to_float(val, &result);
  ck_assert_int_eq(code, 1);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_36) {
  s21_decimal val = {0};

  val.bits[0] = 10;
  set_scale(&val, 1);

  int code = s21_from_decimal_to_float(val, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

Suite *s21_test_from_decimal_to_float(void) {
  Suite *s = suite_create("S21_FROM_DECIMAL_TO_FLOAT");
  TCase *tc = tcase_create("s21_from_decimal_to_float");

  tcase_add_test(tc, test_from_decimal_to_float_1);
  tcase_add_test(tc, test_from_decimal_to_float_2);
  tcase_add_test(tc, test_from_decimal_to_float_3);
  tcase_add_test(tc, test_from_decimal_to_float_4);
  tcase_add_test(tc, test_from_decimal_to_float_5);
  tcase_add_test(tc, test_from_decimal_to_float_7);
  tcase_add_test(tc, test_from_decimal_to_float_8);
  tcase_add_test(tc, test_from_decimal_to_float_9);
  tcase_add_test(tc, test_from_decimal_to_float_10);
  tcase_add_test(tc, test_from_decimal_to_float_11);
  tcase_add_test(tc, test_from_decimal_to_float_12);
  tcase_add_test(tc, test_from_decimal_to_float_13);
  tcase_add_test(tc, test_from_decimal_to_float_14);
  tcase_add_test(tc, test_from_decimal_to_float_15);
  tcase_add_test(tc, test_from_decimal_to_float_16);
  tcase_add_test(tc, test_from_decimal_to_float_17);
  tcase_add_test(tc, test_from_decimal_to_float_18);
  tcase_add_test(tc, test_from_decimal_to_float_19);
  tcase_add_test(tc, test_from_decimal_to_float_20);
  tcase_add_test(tc, test_from_decimal_to_float_21);
  tcase_add_test(tc, test_from_decimal_to_float_22);
  tcase_add_test(tc, test_from_decimal_to_float_23);
  tcase_add_test(tc, test_from_decimal_to_float_24);
  tcase_add_test(tc, test_from_decimal_to_float_25);
  tcase_add_test(tc, test_from_decimal_to_float_26);
  tcase_add_test(tc, test_from_decimal_to_float_27);
  tcase_add_test(tc, test_from_decimal_to_float_28);
  tcase_add_test(tc, test_from_decimal_to_float_29);
  tcase_add_test(tc, test_from_decimal_to_float_30);
  tcase_add_test(tc, test_from_decimal_to_float_31);
  tcase_add_test(tc, test_from_decimal_to_float_32);
  tcase_add_test(tc, test_from_decimal_to_float_33);
  tcase_add_test(tc, test_from_decimal_to_float_34);

  // коды ошибок
  // 1 — ошибка конвертации
  tcase_add_test(tc, test_from_decimal_to_float_6);
  tcase_add_test(tc, test_from_decimal_to_float_35);
  tcase_add_test(tc, test_from_decimal_to_float_36);

  suite_add_tcase(s, tc);
  return s;
}