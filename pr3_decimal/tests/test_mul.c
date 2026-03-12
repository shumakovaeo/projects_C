#include "tests.h"

START_TEST(test_s21_mul_1) {
  // 5 * 10 = 50
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 50);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_2) {
  // -5 * 10.0000 = -50.0000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  set_sign(&val1, 1);
  val2.bits[0] = 100000;
  set_scale(&val2, 4);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 0x0007A120);
  ck_assert_int_eq(res.bits[1], 0x00000000);
  ck_assert_int_eq(res.bits[2], 0x00000000);
  ck_assert_int_eq(get_scale(res), 4);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_s21_mul_3) {
  // -5 * -10 = 50
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;
  set_sign(&val1, 1);  // -5
  set_sign(&val2, 1);  // -10

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 50);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_4) {
  // 0 * 123456 = 0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val2.bits[0] = 123456;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_5) {
  // 1.0000 * MAX = MAX
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x00002710;
  set_scale(&val2, 4);

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFF);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_6) {
  // 2^32 * 2 = 2^33
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[1] = 1;
  val2.bits[0] = 2;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 2);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_7) {
  // 2^64 * 2^32 = 2^96
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[2] = 0x00000001;

  val2.bits[0] = 0x00000000;
  val2.bits[1] = 0x00000001;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x89ABCDEF;
  val1.bits[1] = 0x1234567;
  val1.bits[2] = 0;

  val2.bits[0] = 10;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x60B60B56);
  ck_assert(res.bits[1] == 0x0B60B60B);
  ck_assert(res.bits[2] == 0x0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_9) {
  // Умножение с масштабами: 1.5 * 2.5 = 3.75
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 15;
  val2.bits[0] = 25;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 375);
  ck_assert_int_eq(get_scale(res), 2);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_10) {
  // 1.23 * 45.6 = 56.088
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 123;
  val2.bits[0] = 456;
  set_scale(&val1, 2);
  set_scale(&val2, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 56088);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_11) {
  // 0.0000000000000000000000000000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 1;
  set_scale(&val1, 18);

  val2.bits[0] = 1;
  set_scale(&val2, 18);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 2);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 28);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_12) {
  // 39614081257132168796771975167 * 2 = 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0x7FFFFFFF;

  val2.bits[0] = 2;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
}
END_TEST

START_TEST(test_s21_mul_13) {
  // -1000000000 * 3 = -3000000000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 1000000000;
  val2.bits[0] = 3;
  set_sign(&val1, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 3000000000U);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_s21_mul_14) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val2.bits[0] = 2;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0x1);
  ck_assert_int_eq(get_scale(res), 0);
}
END_TEST

START_TEST(test_s21_mul_15) {
  // 7922816251426433759354395033.4 * 0.01 =
  // 79228162514264337593543950.334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 1);

  val2.bits[0] = 1;
  set_scale(&val2, 2);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_16) {
  // MAX * 2 -> ошибка = 1
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 2;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_mul_17) {
  // -MAX * 2 -> ошибка = 2
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_sign(&val1, 1);

  val2.bits[0] = 2;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_s21_mul_18) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 5);

  val2.bits[0] = 2;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x33333333);
  ck_assert(res.bits[1] == 0x33333333);
  ck_assert(res.bits[2] == 0x33333333);
  ck_assert_int_eq(get_scale(res), 4);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_19) {
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_sign(&val1, 1);

  val2.bits[0] = 1;
  set_sign(&val2, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFF);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_20) {
  // 0.00000000000121932631112635269 (scale = 29) ->
  // 0.0000000000012193263111263527
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 123456789;
  val2.bits[0] = 987654321;
  set_scale(&val1, 14);
  set_scale(&val2, 15);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x4C665527);
  ck_assert(res.bits[1] == 0x002B51B5);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 28);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_21) {
  // не влезает в мантиссу: остаток 0.5, последняя цифра четная
  // 528187751816791697503184486.3 * 15 =
  // 7922816277251875462547767294.5 -> 7922816277251875462547767294
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0x11111111;
  set_scale(&val1, 1);

  val2.bits[0] = 0x0000000F;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0x1999999A);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_22) {
  // не влезает в мантиссу: остаток 0.5, последняя цифра нечетная
  // 79228162514264337593543950335 (scale = 1) * 5 -> =
  // 39614081257132168796771975167.5 -> 39614081257132168796771975168

  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 1);

  val2.bits[0] = 5;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x80000000);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_23) {
  // не влезает в мантиссу: остаток > 0.5
  // 11091942751997007263096153046.76 -> 11091942751997007263096153047
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 2);

  val2.bits[0] = 14;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x3D70A3D7);
  ck_assert(res.bits[1] == 0x70A3D70A);
  ck_assert(res.bits[2] == 0x23D70A3D);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_24) {
  // не влезает в мантиссу: остаток < 0.5
  // 7922816251426433759354395033.4 * 1.3 =
  // 10299661126854363887160713543.42 ->
  // 10299661126854363887160713543
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 1);

  val2.bits[0] = 13;
  set_scale(&val2, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x147AE147);
  ck_assert(res.bits[1] == 0x7AE147AE);
  ck_assert(res.bits[2] == 0x2147AE14);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_25) {
  // число не влезает в мантису, требуется округление
  // 792281625142643375901079764.91 * 5 =
  // 3961408125713216879505398824.55 -> 3961408125713216879505398824.6
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x3333332B;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 2);

  val2.bits[0] = 5;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x99999996);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0x7FFFFFFF);
  ck_assert_int_eq(get_scale(res), 1);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_26) {
  // не влезает в мантиссу: ошибка = 1
  // 7922816251426433759354395033.4 * 11 =
  // 87150978765690771352898345367.4
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFE;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 1);

  val2.bits[0] = 11;

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 1);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_27) {
  // 792281625142643.575901079764 * 79228162514262.5375901079764
  // 62771017353865397371620622298.5838703954472541090295696
  // 62771017353865397371620622299
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xB7D748D4;
  val1.bits[1] = 0xF5C28F8A;
  val1.bits[2] = 0x028F5C28;
  set_scale(&val1, 12);

  val2.bits[0] = 0x334E58D4;
  val2.bits[1] = 0xF5C27EFD;
  val2.bits[2] = 0x028F5C28;
  set_scale(&val2, 13);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xB984FFDB);
  ck_assert(res.bits[1] == 0x3595389C);
  ck_assert(res.bits[2] == 0xCAD2F7F5);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_28) {
  // 396140812571321687967719732.45 * 99 =
  // 39217940444560847108804253512.55 ->
  // 39217940444560847108804253513
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFF87D;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0x7FFFFFFF;
  set_scale(&val1, 2);

  val2.bits[0] = 99;
  set_scale(&val2, 0);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xEB851749);
  ck_assert(res.bits[1] == 0x851EB851);
  ck_assert(res.bits[2] == 0x7EB851EB);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_29) {
  // 7922816251426430500.0000000001 * 1.000001116 =
  // 7922825093289367091.8964380001000001116 ->
  // 7922825093289367091.896438000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x39641001;
  val1.bits[1] = 0xFFFFE25B;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 10);

  val2.bits[0] = 0x3B9ACE5C;
  set_scale(&val2, 9);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xB520CCF0);
  ck_assert(res.bits[1] == 0xEB18FD44);
  ck_assert(res.bits[2] == 0x19999B78);
  ck_assert_int_eq(get_scale(res), 9);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_30) {
  // 7922816251426430500.0000000001 * 0.033 =
  // 261452936297072206.5000000000033 ->
  // 261452936297072206.50000000000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x39641001;
  val1.bits[1] = 0xFFFFE25B;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 10);

  val2.bits[0] = 33;
  set_scale(&val2, 3);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFBE62400);
  ck_assert(res.bits[1] == 0xAE147118);
  ck_assert(res.bits[2] == 0x547AE147);
  ck_assert_int_eq(get_scale(res), 11);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_31) {
  // 79228162514264305000000000001 * 0.5055 =
  // 40049836150960606177500000000.5055 ->
  // 40049836150960606177500000001
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x39641001;
  val1.bits[1] = 0xFFFFE25B;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 5055;
  set_scale(&val2, 4);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xC306EF01);
  ck_assert(res.bits[1] == 0x20C48CA9);
  ck_assert(res.bits[2] == 0x816872B0);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_32) {
  // 79228162514264305000000000001 * 0.5 =
  // 39614081257132152500000000000.5 ->
  // 39614081257132152500000000000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x39641001;
  val1.bits[1] = 0xFFFFE25B;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 5;
  set_scale(&val2, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x9CB20800);
  ck_assert(res.bits[1] == 0xFFFFF12D);
  ck_assert(res.bits[2] == 0x7FFFFFFF);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_33) {
  // 29228162514264305000000000001 * 1.5 =
  // 43842243771396457500000000001.5 ->
  // 43842243771396457500000000002
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xE9641001;
  val1.bits[1] = 0xC946D675;
  val1.bits[2] = 0x5E70F828;
  set_scale(&val1, 0);

  val2.bits[0] = 15;
  set_scale(&val2, 1);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xDE161802);
  ck_assert(res.bits[1] == 0x2DEA41B0);
  ck_assert(res.bits[2] == 0x8DA9743D);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_34) {
  // 0.9999999999999999999999999999 * 0.001 =
  // 0.0009999999999999999999999999999 ->
  // 0.0010000000000000000000000000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x0FFFFFFF;
  val1.bits[1] = 0x3E250261;
  val1.bits[2] = 0x204FCE5E;
  set_scale(&val1, 28);

  val2.bits[0] = 1;
  set_scale(&val2, 3);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x4A000000);
  ck_assert(res.bits[1] == 0x16140148);
  ck_assert(res.bits[2] == 0x00084595);
  ck_assert_int_eq(get_scale(res), 28);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_s21_mul_35) {
  // 7.9228162514264337593543950335 * 7.9228162514264337593543950335 =
  // 62.77101735386680763835789423
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 28);

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_scale(&val2, 28);

  int result = s21_mul(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x096EE456);
  ck_assert(res.bits[1] == 0x359A3B3E);
  ck_assert(res.bits[2] == 0xCAD2F7F5);
  ck_assert_int_eq(get_scale(res), 27);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

Suite *s21_test_mul(void) {
  Suite *s = suite_create("S21_MUL");
  TCase *tc = tcase_create("s21_mul");

  // Базовые тесты
  tcase_add_test(tc, test_s21_mul_1);
  tcase_add_test(tc, test_s21_mul_2);
  tcase_add_test(tc, test_s21_mul_3);
  tcase_add_test(tc, test_s21_mul_4);
  tcase_add_test(tc, test_s21_mul_5);
  tcase_add_test(tc, test_s21_mul_6);
  tcase_add_test(tc, test_s21_mul_7);
  tcase_add_test(tc, test_s21_mul_8);
  tcase_add_test(tc, test_s21_mul_12);
  tcase_add_test(tc, test_s21_mul_14);
  tcase_add_test(tc, test_s21_mul_9);
  tcase_add_test(tc, test_s21_mul_10);
  tcase_add_test(tc, test_s21_mul_13);
  tcase_add_test(tc, test_s21_mul_15);
  tcase_add_test(tc, test_s21_mul_18);
  tcase_add_test(tc, test_s21_mul_19);
  tcase_add_test(tc, test_s21_mul_20);
  // результат не вмещается в мантису, требуется округление
  tcase_add_test(tc, test_s21_mul_21);
  tcase_add_test(tc, test_s21_mul_22);
  tcase_add_test(tc, test_s21_mul_23);
  tcase_add_test(tc, test_s21_mul_24);
  tcase_add_test(tc, test_s21_mul_25);
  tcase_add_test(tc, test_s21_mul_27);
  tcase_add_test(tc, test_s21_mul_28);
  tcase_add_test(tc, test_s21_mul_29);
  tcase_add_test(tc, test_s21_mul_30);
  tcase_add_test(tc, test_s21_mul_31);
  tcase_add_test(tc, test_s21_mul_32);
  tcase_add_test(tc, test_s21_mul_33);
  tcase_add_test(tc, test_s21_mul_34);
  tcase_add_test(tc, test_s21_mul_35);
  // коды ошибок
  // 1 — число слишком велико или равно бесконечности
  tcase_add_test(tc, test_s21_mul_7);
  tcase_add_test(tc, test_s21_mul_16);
  tcase_add_test(tc, test_s21_mul_26);
  // 2 — число слишком мало или равно отрицательной бесконечности
  tcase_add_test(tc, test_s21_mul_11);
  tcase_add_test(tc, test_s21_mul_17);

  suite_add_tcase(s, tc);
  return s;
}