#include "tests.h"

START_TEST(test_sub_1) {
  // 5 - 10 = -5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_2) {
  // 10 - 5 = 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 10;
  val2.bits[0] = 5;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_3) {
  // 5 - 5 = 0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 5;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_sub_4) {
  // -5 - 10 = -15
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;
  set_sign(&val1, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 15);
  ck_assert_int_eq(get_sign(res), 1);
  ck_assert_int_eq(res.bits[1], 0);
  ck_assert_int_eq(res.bits[2], 0);
}
END_TEST

START_TEST(test_sub_5) {
  // 5 - (-10) = 15
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;
  set_sign(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 15);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_6) {
  // -5 - (-10) = 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;
  val2.bits[0] = 10;
  set_sign(&val1, 1);
  set_sign(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_7) {
  // 0 - 5 = -5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val2.bits[0] = 5;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_8) {
  // 5 - 0 = 5
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 5;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 5);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_9) {
  // 0 - 0 = 0
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
}
END_TEST

START_TEST(test_sub_10) {
  // 5.5 - 2.3 = 3.2
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 55;
  val2.bits[0] = 23;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 32);
  ck_assert_int_eq(get_scale(res), 1);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_11) {
  // 2.3 - 5.5 = -3.2
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 23;
  val2.bits[0] = 55;
  set_scale(&val1, 1);
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert_int_eq(res.bits[0], 32);
  ck_assert_int_eq(get_scale(res), 1);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_12) {
  // 79228162514264337593543950335 - 1 =
  // 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 1;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);

  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);

  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_13) {
  // 79228162514264337593543950335 - (-1) =
  // 79228162514264337593543950336 > MAX
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 1;
  set_sign(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_14) {
  //-79228162514264337593543950335 - 1 =
  //-79228162514264337593543950336 -> 2(слишком мало)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_sign(&val1, 1);

  val2.bits[0] = 1;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_sub_15) {
  // остаток < 0.5 - не округляем
  // 79228162514264337593543950335 - 0.6 =
  // 79228162514264337593543950334.4 -> 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 6;
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_16) {
  // остаток > 0.5 - округляем вверх
  // 79228162514264337593543950335 - 0.4 =
  // 79228162514264337593543950334.6 -> 79228162514264337593543950335
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 4;
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFF);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_17) {
  // остаток = 0.5, последняя цифра четная - не округляем
  // 79228162514264337593543950335 - 0.5 =
  // 79228162514264337593543950334.5 -> 79228162514264337593543950334
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 5;
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFE);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_18) {
  // остаток = 0.5, последняя цифра нечетная - округляем вверх
  //  79228162514264337593543950332 - 0.5 ->
  //  79228162514264337593543950331.5 -> 79228162514264337593543950332
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFC;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 5;
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFFC);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_19) {
  // остаток > 0.5 - округляем вверх
  //  79228162514264337593543950335 - 79228162514264337593543950.111 =
  //  79148934351750073255950406384.889 ->
  //  79148934351750073255950406385
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 0xFFFFFF1F;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_scale(&val2, 3);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x624DD2F1);
  ck_assert(res.bits[1] == 0xB4395810);
  ck_assert(res.bits[2] == 0xFFBE76C8);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_20) {
  // остаток = 0.54 - округляем вверх
  //  79228162514264337593543950335 - 79228162514264337593543950.46 =
  //  79148934351750073255950406384.54 ->
  //  79148934351750073255950406385
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 0x999999A6;
  val2.bits[1] = 0x99999999;
  val2.bits[2] = 0x19999999;
  set_scale(&val2, 2);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x624DD2F1);
  ck_assert(res.bits[1] == 0xB4395810);
  ck_assert(res.bits[2] == 0xFFBE76C8);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_21) {
  // остаток = 0.5, последняя цифра четная - не округляем
  //  79228162514264337593543950335 - 79228162514264337593543950.50 =
  //  79148934351750073255950406384.50 ->
  //  79148934351750073255950406384
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 0);

  val2.bits[0] = 0x999999AA;
  val2.bits[1] = 0x99999999;
  val2.bits[2] = 0x19999999;
  set_scale(&val2, 2);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x624DD2F0);
  ck_assert(res.bits[1] == 0xB4395810);
  ck_assert(res.bits[2] == 0xFFBE76C8);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_22) {
  // 79228162514264337593543950.000 - 79228162514264337593543950 =
  // 0.000 ->
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFEB0;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 3);

  val2.bits[0] = 0x9DB22D0E;
  val2.bits[1] = 0x4BC6A7EF;
  val2.bits[2] = 0x00418937;
  set_scale(&val2, 0);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_23) {
  // 7922816251426433759354395 - 79228162514264337593950.111 =
  // 7843588088912169421760444.889 -> 7843588088912169421760444.889
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x295E9E1B;
  val1.bits[1] = 0xBAC710CB;
  val1.bits[2] = 0x00068DB8;
  set_scale(&val1, 0);

  val2.bits[0] = 0x9DB85F9F;
  val2.bits[1] = 0x4BC6A7EF;
  val2.bits[2] = 0x00418937;
  set_scale(&val2, 3);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFBE139D9);
  ck_assert(res.bits[1] == 0x4DD2F1A9);
  ck_assert(res.bits[2] == 0x19581062);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_24) {
  // 10004.50 - 10.5 = 9994.00
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 1000450;
  set_scale(&val1, 2);

  val2.bits[0] = 105;
  set_scale(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x000F3FE8);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 2);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_25) {
  // 100045.0 - 1.00 = 100044.00
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 1000450;
  set_scale(&val1, 1);

  val2.bits[0] = 100;
  set_scale(&val2, 2);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x0098A7B0);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 2);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_26) {
  // 0000000000000000000000000.0000
  // 7922816251426433759354395.5 - 0.477777 =
  // 7922816251426433759354395.022223 ->
  // 7922816251426433759354395.0222
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x9DB22D13;
  val1.bits[1] = 0x4BC6A7EF;
  val1.bits[2] = 0x00418937;
  set_scale(&val1, 1);

  val2.bits[0] = 477777;
  set_scale(&val2, 6);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFF8E);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 4);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_27) {
  // 00000000000000000000000000000
  // 7922816251426433759354395  - 0.0000006 =
  // 7922816251426433759354394.9999994 ->
  // 7922816251426433759354395.0000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x295E9E1B;
  val1.bits[1] = 0xBAC710CB;
  val1.bits[2] = 0x00068DB8;

  val2.bits[0] = 6;
  set_scale(&val2, 7);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFEB0);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 4);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_28) {
  // 7922816251426433759354395033 - 0.66 =
  // 79228162514264337593543950330 - 6.6 (scale = 1)
  // 7922816251426433759354395032.34 ->
  // 7922816251426433759354395032.3
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x99999999;
  val1.bits[1] = 0x99999999;
  val1.bits[2] = 0x19999999;

  val2.bits[0] = 66;
  set_scale(&val2, 2);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xFFFFFFF3);
  ck_assert(res.bits[1] == 0xFFFFFFFF);
  ck_assert(res.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_scale(res), 1);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_29) {
  // 79228162514264337.50335
  // 79228162514264337593543950.335
  //-79228162435036175079279612.832
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xF485553F;
  val1.bits[1] = 0x7F29ABCA;
  val1.bits[2] = 0x000001AD;
  set_scale(&val1, 5);

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_scale(&val2, 3);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x4A5AD3A0);
  ck_assert(res.bits[1] == 0xB47D05F6);
  ck_assert(res.bits[2] == 0xFFFFFFFB);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_30) {
  // остаток > 0.5 - округляем вверх
  // 79228162514264337593543950.335 (scale_1 = 3) -
  // 792281625142643375935439.12345 (scale_2 = 5) =
  // 78435880889121694217608511.21155 ->
  // 78435880889121694217608511.212
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 3);

  val2.bits[0] = 0xFFFF6B99;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_scale(&val2, 5);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xD70A3EEC);
  ck_assert(res.bits[1] == 0x0A3D70A3);
  ck_assert(res.bits[2] == 0xFD70A3D7);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_31) {
  // остаток = 0.5, последняя цифра четная - не округляем
  // 79228162514264337593543950.335 (scale_1 = 3) -
  // 792281625142643375935439.1245 (scale_2 = 4) =
  // 78435880889121694217608511.2105 ->
  // 78435880889121694217608511.210
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 3);

  val2.bits[0] = 0x99998ACD;
  val2.bits[1] = 0x99999999;
  val2.bits[2] = 0x19999999;
  set_scale(&val2, 4);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xD70A3EEA);
  ck_assert(res.bits[1] == 0x0A3D70A3);
  ck_assert(res.bits[2] == 0xFD70A3D7);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_32) {
  // остаток = 0.5, последняя цифра нечетная - округляем вверх
  //  792281625142643375935439.1235 -
  //  79228162514264337593543950.335 =
  //-78435880889121694217608511.2115 ->
  //-78435880889121694217608511.212
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x99998AC3;
  val1.bits[1] = 0x99999999;
  val1.bits[2] = 0x19999999;
  set_scale(&val1, 4);

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_scale(&val2, 3);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xD70A3EEC);
  ck_assert(res.bits[1] == 0x0A3D70A3);
  ck_assert(res.bits[2] == 0xFD70A3D7);
  ck_assert_int_eq(get_scale(res), 3);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_33) {
  //-7.9228162514264337593543950335 - 0.00000000000004 =
  //-7.9228162514264737593543950335 ->
  //-7.922816251426473759354395034

  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;
  set_scale(&val1, 28);
  set_sign(&val1, 1);

  val2.bits[0] = 0x00000004;
  val2.bits[1] = 0x00000000;
  val2.bits[2] = 0x00000000;
  set_scale(&val2, 14);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0xD364199A);
  ck_assert(res.bits[1] == 0x9999BDFA);
  ck_assert(res.bits[2] == 0x19999999);
  ck_assert_int_eq(get_scale(res), 27);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_34) {
  // 1.0000000000000000000000000000 - 2 =
  //-1.0000000000000000000000000000
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x10000000;
  val1.bits[1] = 0x3E250261;
  val1.bits[2] = 0x204FCE5E;
  set_scale(&val1, 28);

  val2.bits[0] = 0x00000002;
  val2.bits[1] = 0x00000000;
  val2.bits[2] = 0x00000000;
  set_scale(&val2, 0);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 0);
  ck_assert(res.bits[0] == 0x10000000);
  ck_assert(res.bits[1] == 0x3E250261);
  ck_assert(res.bits[2] == 0x204FCE5E);
  ck_assert_int_eq(get_scale(res), 28);
  ck_assert_int_eq(get_sign(res), 1);
}
END_TEST

START_TEST(test_sub_35) {
  // 79228162514264337593543950335 - (-79228162514264337593543950335) =
  //  > +MAX (код ошибки = 1)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0xFFFFFFFF;
  val1.bits[1] = 0xFFFFFFFF;
  val1.bits[2] = 0xFFFFFFFF;

  val2.bits[0] = 0xFFFFFFFF;
  val2.bits[1] = 0xFFFFFFFF;
  val2.bits[2] = 0xFFFFFFFF;
  set_sign(&val2, 1);

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 1);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

START_TEST(test_sub_36) {
  //-39614081257132168796771975168 - 39614081257132168796771975168 =
  //-79228162514264337593543950336 < -MAX (код ошибки = 2)
  s21_decimal val1 = {0};
  s21_decimal val2 = {0};
  s21_decimal res = {0};

  val1.bits[0] = 0x00000000;
  val1.bits[1] = 0x00000000;
  val1.bits[2] = 0x80000000;
  set_sign(&val1, 1);

  val2.bits[0] = 0x00000000;
  val2.bits[1] = 0x00000000;
  val2.bits[2] = 0x80000000;

  int result = s21_sub(val1, val2, &res);
  ck_assert_int_eq(result, 2);
  ck_assert(res.bits[0] == 0x00000000);
  ck_assert(res.bits[1] == 0x00000000);
  ck_assert(res.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(res), 0);
  ck_assert_int_eq(get_sign(res), 0);
}
END_TEST

Suite *s21_test_sub(void) {
  Suite *s = suite_create("S21_SUB");
  TCase *tc = tcase_create("s21_sub");

  tcase_add_test(tc, test_sub_1);
  tcase_add_test(tc, test_sub_2);
  tcase_add_test(tc, test_sub_3);
  tcase_add_test(tc, test_sub_4);
  tcase_add_test(tc, test_sub_5);
  tcase_add_test(tc, test_sub_6);
  tcase_add_test(tc, test_sub_7);
  tcase_add_test(tc, test_sub_8);
  tcase_add_test(tc, test_sub_9);
  tcase_add_test(tc, test_sub_10);
  tcase_add_test(tc, test_sub_11);
  tcase_add_test(tc, test_sub_12);
  tcase_add_test(tc, test_sub_15);
  tcase_add_test(tc, test_sub_16);
  tcase_add_test(tc, test_sub_17);
  tcase_add_test(tc, test_sub_18);
  tcase_add_test(tc, test_sub_19);
  tcase_add_test(tc, test_sub_20);
  tcase_add_test(tc, test_sub_21);
  tcase_add_test(tc, test_sub_22);
  tcase_add_test(tc, test_sub_23);
  tcase_add_test(tc, test_sub_24);
  tcase_add_test(tc, test_sub_25);
  tcase_add_test(tc, test_sub_26);
  tcase_add_test(tc, test_sub_27);
  tcase_add_test(tc, test_sub_28);
  tcase_add_test(tc, test_sub_29);
  tcase_add_test(tc, test_sub_30);
  tcase_add_test(tc, test_sub_31);
  tcase_add_test(tc, test_sub_32);
  tcase_add_test(tc, test_sub_33);
  tcase_add_test(tc, test_sub_34);

  // коды ошибок
  // 1 — число слишком велико или равно бесконечности
  tcase_add_test(tc, test_sub_13);
  tcase_add_test(tc, test_sub_35);
  // 2 — число слишком мало или равно отрицательной бесконечности
  tcase_add_test(tc, test_sub_14);
  tcase_add_test(tc, test_sub_36);

  suite_add_tcase(s, tc);
  return s;
}
