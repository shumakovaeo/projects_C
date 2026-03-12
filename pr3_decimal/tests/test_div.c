#include "tests.h"

START_TEST(test_div_1) {
  // 5 / 0.001 = 5000
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 5;
  set_scale(&value_1, 0);
  value_2.bits[0] = 1;
  set_scale(&value_2, 3);

  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], 5000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_2) {
  // 1 / 0.005 = 200
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 1;
  set_scale(&value_1, 0);
  value_2.bits[0] = 5;
  set_scale(&value_2, 3);

  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(result.bits[0], 200);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_3) {
  // Деление на ноль
  s21_decimal value_1 = {{100, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_div_4) {
  // -100 / 5
  s21_decimal value_1 = {{100, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{5, 0, 0, 0}};

  s21_decimal result = {0};

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_5) {
  // -100 / -5
  s21_decimal value_1 = {{100, 0, 0, 0}};
  set_sign(&value_1, 1);
  s21_decimal value_2 = {{5, 0, 0, 0}};
  set_sign(&value_2, 1);
  s21_decimal result = {0};

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_6) {
  // 1.5 / 0.3
  s21_decimal value_1 = {{150, 0, 0, 0}};
  set_scale(&value_1, 1);

  s21_decimal value_2 = {{30, 0, 0, 0}};
  set_scale(&value_2, 1);

  s21_decimal result = {0};

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000005);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_7) {
  // 123456 / 123456
  s21_decimal value_1 = {{123456, 0, 0, 0}};
  s21_decimal value_2 = {{123456, 0, 0, 0}};
  s21_decimal result = {0};

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_8) {
  // 0.0000000000000000000000000001 (scale = 28) / 3 = 0
  s21_decimal result = {0};

  s21_decimal value_1 = {{1, 0, 0, 0}};
  set_scale(&value_1, 28);
  s21_decimal value_2 = {{3, 0, 0, 0}};

  int code = s21_div(value_1, value_2, &result);

  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_9) {
  // 1 / 1000.000 = 1 / 1000 = 0.001
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_2.bits[0] = 1000000;
  set_scale(&value_2, 3);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000001);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 3);
}
END_TEST

START_TEST(test_div_10) {
  // 79228162514264337593543950335 / 0.1
  // 792281625142643375935439503350 -> число слишком велико = 1
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  set_scale(&value_2, 1);

  s21_decimal result = {0};

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 1);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_11) {
  // 10 / 3 = 3.3333333333333333333333333333
  s21_decimal value_1 = {{10, 0, 0, 0}};
  s21_decimal value_2 = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x35555555);
  ck_assert(result.bits[1] == 0xCF2607EE);
  ck_assert(result.bits[2] == 0x6BB4AFE4);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_12) {
  // 79228162514264337593543950333 / 1.8 =
  // 44015645841257965329746639073.8 = 44015645841257965329746639074
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFD;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  value_2.bits[0] = 18;
  set_scale(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xE38E38E2);
  ck_assert(result.bits[1] == 0x38E38E38);
  ck_assert(result.bits[2] == 0x8E38E38E);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_13) {
  // банковское округление вверх при переполнении
  // 14773333333453345334533333333 / 1.2 =
  // 12311111111211121112111111110.83333 = 12311111111211121112111111111
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0x31A4A155;
  value_1.bits[1] = 0xBFC71A1D;
  value_1.bits[2] = 0x2FBC3704;

  value_2.bits[0] = 12;
  set_scale(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFEB3DBC7);
  ck_assert(result.bits[1] == 0x9FD095C2);
  ck_assert(result.bits[2] == 0x27C7832E);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_14) {
  // банковское округление вверх при переполнении, остаток > 0.5
  // 14773333333453345334533333555 / 0.52 = 28410256410487202566410256836.538
  // 28410256410487202566410256837
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0x31A4A233;
  value_1.bits[1] = 0xBFC71A1D;
  value_1.bits[2] = 0x2FBC3704;

  value_2.bits[0] = 52;
  set_scale(&value_2, 2);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x10B2C1C5);
  ck_assert(result.bits[1] == 0x0E5780FD);
  ck_assert(result.bits[2] == 0x5BCC69CE);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_15) {
  // банковское округление вверх при переполнении, остаток = 0.5
  // 55555555556055555555555555555 / 5.2 = 10683760683856837606837606837.5
  // 10683760683856837606837606838 (т.к. последняя цифра нечетная округляем
  // вверх)
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xD74038E3;
  value_1.bits[1] = 0x602FBDE6;
  value_1.bits[2] = 0xB3827A7D;

  value_2.bits[0] = 52;
  set_scale(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x9F8C59B6);
  ck_assert(result.bits[1] == 0x30092E5D);
  ck_assert(result.bits[2] == 0x22856653);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_16) {
  // банковское округление вверх при переполнении, остаток = 0.5
  // 52000000000000000000000000013 / 5.2 = 10000000000000000000000000002.5
  // 1.0000000000000000000000000002 (т.к. последняя цифра четная не увеличиваем)
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0x2000000D;
  value_1.bits[1] = 0x765A0C5F;
  value_1.bits[2] = 0xA8056450;

  value_2.bits[0] = 52;
  set_scale(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x10000002);
  ck_assert(result.bits[1] == 0x3E250261);
  ck_assert(result.bits[2] == 0x204FCE5E);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_17) {
  // 58 / 79228162514264337593543950335
  //  =  0.000000000000000000000000000732
  //  -> 0.0000000000000000000000000007

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 58;
  set_scale(&value_1, 0);

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000007);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_18) {
  // 5.8 / 79228162514264337593543950335
  //  =   0.000000000000000000000000000073
  //  ->  0.0000000000000000000000000001

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 58;
  set_scale(&value_1, 1);

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000001);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_19) {
  // 0.58 / 79228162514264337593543950335
  //  =    0.000000000000000000000000000007 - не влезает
  //  ->   0

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 58;
  set_scale(&value_1, 2);

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_20) {
  // 58 / 79228162514264337593543950335 (scale = 2)
  //  =  0.000000000000000000000000073206
  //  -> 0.0000000000000000000000000732

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 58;

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;
  set_scale(&value_2, 2);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x000002DC);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_21) {
  // 79228162514264337593543950335 / 79228162514264337593543950331
  // 1.0000000000000000000000000000505 -> 1.0000000000000000000000000001

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  set_scale(&value_1, 0);

  value_2.bits[0] = 0xFFFFFFFB;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;
  set_scale(&value_2, 0);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x10000001);
  ck_assert(result.bits[1] == 0x3E250261);
  ck_assert(result.bits[2] == 0x204FCE5E);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_22) {
  // 4000000000000000000000000001 / 4000000000000000000000000000
  // 1.00000000000000000000000000025 -> 1.0000000000000000000000000002

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  set_scale(&value_1, 0);

  value_2.bits[0] = 0xFFFFFFFB;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;
  set_scale(&value_2, 0);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x10000001);
  ck_assert(result.bits[1] == 0x3E250261);
  ck_assert(result.bits[2] == 0x204FCE5E);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_23) {
  // 0.0000000000000000000000000001 (scale = 28) / 1.5 =
  // 0.0000000000000000000000000000666667 ->
  // 0.0000000000000000000000000001
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 1;
  set_scale(&value_1, 28);
  value_2.bits[0] = 15;
  set_scale(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000001);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_24) {
  // 20000000000000000000000000003 / 20000000000000000000000000000
  // 1.00000000000000000000000000015 -> 1.0000000000000000000000000002

  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0x20000003;
  value_1.bits[1] = 0x7C4A04C2;
  value_1.bits[2] = 0x409F9CBC;
  set_scale(&value_1, 0);

  value_2.bits[0] = 0x20000000;
  value_2.bits[1] = 0x7C4A04C2;
  value_2.bits[2] = 0x409F9CBC;
  set_scale(&value_2, 0);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x10000002);
  ck_assert(result.bits[1] == 0x3E250261);
  ck_assert(result.bits[2] == 0x204FCE5E);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_25) {
  // 0.00001 (scale = 5) / 0.0000000000000000000000000006 (scale = 28)
  // 16666666666666666666666.666667 (Scale = 6)
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 1;
  set_scale(&value_1, 5);
  value_2.bits[0] = 6;
  set_scale(&value_2, 28);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x1AAAAAAB);
  ck_assert(result.bits[1] == 0x679303F7);
  ck_assert(result.bits[2] == 0x35DA57F2);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 6);
}
END_TEST

START_TEST(test_div_26) {
  // 8 / 0.512 = 15.625
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 8;
  set_scale(&value_1, 0);
  value_2.bits[0] = 512;
  set_scale(&value_2, 3);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00003D09);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 3);
}
END_TEST

START_TEST(test_div_27) {
  // -79228162514264337593543950330 / 79228162514264337593543950315
  // = -1.0000000000000000000000000001893
  //-> -1.0000000000000000000000000002
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFA;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;
  set_sign(&value_1, 1);

  value_2.bits[0] = 0xFFFFFFEB;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x10000002);
  ck_assert(result.bits[1] == 0x3E250261);
  ck_assert(result.bits[2] == 0x204FCE5E);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 28);
}
END_TEST

START_TEST(test_div_28) {
  // 1 / 79228162514264337593543950335
  // =  0.00000000000000000000000000001262
  //->  0
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0);
  ck_assert(result.bits[1] == 0);
  ck_assert(result.bits[2] == 0);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_29) {
  // -79228162514264337593543950335 / 2.5
  // = -31691265005705735037417580134
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;
  set_sign(&value_1, 1);

  value_2.bits[0] = 25;
  set_scale(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x66666666);
  ck_assert(result.bits[1] == 0x66666666);
  ck_assert(result.bits[2] == 0x66666666);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_30) {
  // 79228162514264337593543950335 / 0.001
  //=79228162514264337593543950335000 (> MAX)
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  value_2.bits[0] = 1;
  set_scale(&value_2, 3);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 1);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_31) {
  //   79228162514264337593543950335 / -0.001
  //= -79228162514264337593543950335000 (< -MAX)
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  value_2.bits[0] = 1;
  set_scale(&value_2, 3);
  set_sign(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 2);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_32) {
  // 79228162514264337593543950335 / 0
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 3);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_33) {
  //   79228162514264337593543950335 / 2 =
  //   39614081257132168796771975167.5
  //-> 39614081257132168796771975168
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x80000000);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_34) {
  //   79228162514264337593543950335 / 10 =
  //   79228162514264337593543950335.5
  //-> 79228162514264337593543950335
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0xFFFFFFFF);
  ck_assert(result.bits[1] == 0xFFFFFFFF);
  ck_assert(result.bits[2] == 0xFFFFFFFF);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(get_scale(result), 1);
}
END_TEST

START_TEST(test_div_35) {
  // 79228162514264337593543950335 / -0.99
  //-80028446984105391508630252863. <- MAX
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  value_2.bits[0] = 99;
  set_scale(&value_2, 2);
  set_sign(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 2);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(get_scale(result), 0);
}
END_TEST

START_TEST(test_div_36) {
  // 0.000 / -12345 = -0.000
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0;
  set_scale(&value_1, 3);

  value_2.bits[0] = 12345;
  set_scale(&value_2, 0);
  set_sign(&value_2, 1);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000000);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 3);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(test_div_37) {
  // 0.0000000000000000000000000005 / 1 =
  // 0.0000000000000000000000000005
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 5;
  set_scale(&value_1, 28);

  value_2.bits[0] = 1;
  set_scale(&value_2, 0);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000005);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 28);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_div_38) {
  // 5 / 0.0000000000000000000000000001 =
  // 50000000000000000000000000000
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 5;
  set_scale(&value_1, 0);

  value_2.bits[0] = 1;
  set_scale(&value_2, 28);

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x50000000);
  ck_assert(result.bits[1] == 0x36B90BE5);
  ck_assert(result.bits[2] == 0xA18F07D7);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_div_39) {
  // 5 / 79228162514264337593543950335
  // =  0.000000000000000000000000000063108872
  //->  0.0000000000000000000000000001
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 5;
  set_scale(&value_1, 0);

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000001);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 28);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_div_40) {
  // 79228162514264337593543950335 / 79228162514264337593543950334
  // 1.00000000000000000000000000001262177448
  // 1.0000000000000000000000000000 -> 1
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFF;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  value_2.bits[0] = 0xFFFFFFFE;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000001);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(test_div_41) {
  // 79228162514264337593543950334 / 79228162514264337593543950335
  // 0.999999999999999999999999999987
  // 1.0000000000000000000000000000 -> 1
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};

  value_1.bits[0] = 0xFFFFFFFE;
  value_1.bits[1] = 0xFFFFFFFF;
  value_1.bits[2] = 0xFFFFFFFF;

  value_2.bits[0] = 0xFFFFFFFF;
  value_2.bits[1] = 0xFFFFFFFF;
  value_2.bits[2] = 0xFFFFFFFF;

  int code = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(code, 0);
  ck_assert(result.bits[0] == 0x00000001);
  ck_assert(result.bits[1] == 0x00000000);
  ck_assert(result.bits[2] == 0x00000000);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

Suite *s21_test_div(void) {
  Suite *s = suite_create("S21_DIV");
  TCase *tc = tcase_create("s21_div");

  tcase_add_test(tc, test_div_1);
  tcase_add_test(tc, test_div_2);
  tcase_add_test(tc, test_div_3);
  tcase_add_test(tc, test_div_4);
  tcase_add_test(tc, test_div_5);
  tcase_add_test(tc, test_div_6);
  tcase_add_test(tc, test_div_7);
  tcase_add_test(tc, test_div_8);
  tcase_add_test(tc, test_div_9);
  tcase_add_test(tc, test_div_11);
  tcase_add_test(tc, test_div_12);
  tcase_add_test(tc, test_div_13);
  tcase_add_test(tc, test_div_14);
  tcase_add_test(tc, test_div_15);
  tcase_add_test(tc, test_div_16);
  tcase_add_test(tc, test_div_17);
  tcase_add_test(tc, test_div_18);
  tcase_add_test(tc, test_div_19);
  tcase_add_test(tc, test_div_20);
  tcase_add_test(tc, test_div_21);
  tcase_add_test(tc, test_div_22);
  tcase_add_test(tc, test_div_23);
  tcase_add_test(tc, test_div_24);
  tcase_add_test(tc, test_div_25);
  tcase_add_test(tc, test_div_26);
  tcase_add_test(tc, test_div_27);
  tcase_add_test(tc, test_div_28);
  tcase_add_test(tc, test_div_29);
  tcase_add_test(tc, test_div_33);
  tcase_add_test(tc, test_div_34);
  tcase_add_test(tc, test_div_36);
  tcase_add_test(tc, test_div_37);
  tcase_add_test(tc, test_div_38);
  tcase_add_test(tc, test_div_39);
  tcase_add_test(tc, test_div_40);
  tcase_add_test(tc, test_div_41);

  // коды ошибок
  // 1 — число слишком велико или равно бесконечности
  tcase_add_test(tc, test_div_10);
  tcase_add_test(tc, test_div_30);
  // 2 — число слишком мало или равно отрицательной бесконечности
  tcase_add_test(tc, test_div_31);
  tcase_add_test(tc, test_div_35);
  // 3 — деление на 0
  tcase_add_test(tc, test_div_32);

  suite_add_tcase(s, tc);

  return s;
}