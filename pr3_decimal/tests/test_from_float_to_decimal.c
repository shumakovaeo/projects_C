
#include "tests.h"

START_TEST(s21_float_000) {
  float inp = 1. / 0.;
  s21_decimal out;
  int error = s21_from_float_to_decimal(inp, &out);
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], 0);
  ck_assert_int_eq(error, 1);
}
END_TEST
START_TEST(s21_float_00) {
  float inp = 2;
  s21_decimal *out = NULL;
  int error = s21_from_float_to_decimal(inp, out);
  ck_assert_ptr_eq(out, NULL);
  ck_assert_int_eq(error, 1);
}
END_TEST
START_TEST(s21_float_0) {
  float inp = 2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000002, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_1) {
  float inp = -321.2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000C8C, 0, 0, 0x80010000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_2) {
  float inp = 321.2;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000C8C, 0, 0, 0x00010000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_3) {
  float inp = 321213143.8323;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x13255310, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_4) {
  float inp = 9732131234575756436473.323123474;
  s21_decimal out = {{3211, 123145, 231, 312441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0xC7238000, 0x9472ED75, 0x0000020F, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_5) {
  float inp = 73.329959999;
  s21_decimal out = {{3211, 123145, 231, 312441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x006FE484, 0, 0, 0x00050000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_6) {
  float inp = 0.003;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000003, 0, 0, 0x00030000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_7) {
  float inp = 0.00312345;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0004C419, 0, 0, 0x00080000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_8) {
  float inp = 0.00000003123959595945;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0004C44C, 0, 0, 0x000D0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_10_5) {
  float inp = 0.00000000000000000000000000016929383838292;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000002, 0, 0, 0x001C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_11) {
  float inp = .00000000000000000000000000000000193929383838292;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  ck_assert_int_eq(error, 1);
}
END_TEST

START_TEST(s21_float_14) {
  float inp = 7015000000000000000000000000.365656;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0xC7000000, 0xFFD18396, 0x16AAAC07, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_16) {
  float inp = 0.00000000000000000000000073736361612636;
  s21_decimal out = {{32131, 1231435, 2311, 3121441}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00001CCE, 0, 0, 0x001C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_22) {
  float inp = -1.307818E+07;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00C78EA4, 0x00000000, 0x00000000, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_23) {
  float inp = -30914.76;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x002F2C14, 0x00000000, 0x00000000, 0x80020000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_24) {
  float inp = 1.965111E-26;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x000000C5, 0x00000000, 0x00000000, 0x001C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_25) {
  float inp = -750.9904;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00729790, 0x00000000, 0x00000000, 0x80040000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_26) {
  float inp = 72932.2;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x000B20EA, 0x00000000, 0x00000000, 0x00010000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_27) {
  float inp = 7.526432E-06;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0072D820, 0x00000000, 0x00000000, 0x000C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_29) {
  float inp = -1.391184E+17;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x9DB88000, 0x01EE3F72, 0x00000000, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_30) {
  float inp = 3.693497E-09;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00385BB9, 0x00000000, 0x00000000, 0x000F0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_33) {
  float inp = -2.013319E-14;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x001EB887, 0x00000000, 0x00000000, 0x80140000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_34) {
  float inp = -280.7036;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x002AD4FC, 0x00000000, 0x00000000, 0x80040000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_35) {
  float inp = -3.196059E+18;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x2030B000, 0x2C5AAEBA, 0x00000000, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_39) {
  float inp = 4.511203E-27;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0000002D, 0x00000000, 0x00000000, 0x001C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_40) {
  float inp = -7.442655E+23;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x1B360000, 0xB6AE8261, 0x00009D9A, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_42) {
  float inp = -5.447201E-28;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000005, 0x00000000, 0x00000000, 0x801C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_48) {
  float inp = 1.230342E+28;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0xAD800000, 0xA66BA8BD, 0x27C12686, 0x00000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_53) {
  float inp = -3.22218E-27;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000020, 0x00000000, 0x00000000, 0x801C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_54) {
  float inp = 1.290434E-09;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0013B0C2, 0x00000000, 0x00000000, 0x000F0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_60) {
  float inp = 6.76729E-11;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x000A5379, 0x00000000, 0x00000000, 0x00100000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_61) {
  float inp = -1.56421E+08;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0952CB88, 0x00000000, 0x00000000, 0x80000000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_62) {
  float inp = 1.248784E-11;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00130E10, 0x00000000, 0x00000000, 0x00110000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_63) {
  float inp = 3.830389E-28;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x00000004, 0x00000000, 0x00000000, 0x001C0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_67) {
  float inp = -0.005833615;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0x0059038F, 0x00000000, 0x00000000, 0x80090000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_70) {
  float inp = 0;
  s21_decimal out = {{0, 0, 0, 0}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{0, 0, 0, 0}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(s21_float_71) {
  float inp = 8.58598287E-24;
  s21_decimal out = {{0x00009D40, 0x0000EB82, 0x00008442, 0x00001472}};
  int error = s21_from_float_to_decimal(inp, &out);
  s21_decimal res = {{8586, 0x00000000, 0x00000000, 0x1B0000}};
  for (int i = 0; i < 4; i++) ck_assert_int_eq(out.bits[i], res.bits[i]);
  ck_assert_int_eq(error, 0);
}
END_TEST

Suite *s21_test_from_float_to_decimal(void) {
  Suite *s = suite_create("S21_FROM_FLOAT_TO_DECIMAL");
  TCase *tc = tcase_create("s21_from_float_to_decimal");

  tcase_add_test(tc, s21_float_000);
  tcase_add_test(tc, s21_float_00);
  tcase_add_test(tc, s21_float_0);
  tcase_add_test(tc, s21_float_1);
  tcase_add_test(tc, s21_float_2);
  tcase_add_test(tc, s21_float_3);
  tcase_add_test(tc, s21_float_4);
  tcase_add_test(tc, s21_float_5);
  tcase_add_test(tc, s21_float_6);
  tcase_add_test(tc, s21_float_7);
  tcase_add_test(tc, s21_float_8);

  tcase_add_test(tc, s21_float_10_5);
  tcase_add_test(tc, s21_float_11);

  tcase_add_test(tc, s21_float_14);

  tcase_add_test(tc, s21_float_16);

  tcase_add_test(tc, s21_float_22);
  tcase_add_test(tc, s21_float_23);
  tcase_add_test(tc, s21_float_24);
  tcase_add_test(tc, s21_float_25);
  tcase_add_test(tc, s21_float_26);
  tcase_add_test(tc, s21_float_27);
  tcase_add_test(tc, s21_float_29);
  tcase_add_test(tc, s21_float_30);

  tcase_add_test(tc, s21_float_33);
  tcase_add_test(tc, s21_float_34);
  tcase_add_test(tc, s21_float_35);

  tcase_add_test(tc, s21_float_39);
  tcase_add_test(tc, s21_float_40);

  tcase_add_test(tc, s21_float_42);

  tcase_add_test(tc, s21_float_48);

  tcase_add_test(tc, s21_float_53);
  tcase_add_test(tc, s21_float_54);

  tcase_add_test(tc, s21_float_60);
  tcase_add_test(tc, s21_float_61);
  tcase_add_test(tc, s21_float_62);
  tcase_add_test(tc, s21_float_63);

  tcase_add_test(tc, s21_float_67);

  tcase_add_test(tc, s21_float_70);
  tcase_add_test(tc, s21_float_71);

  suite_add_tcase(s, tc);
  return s;
}
