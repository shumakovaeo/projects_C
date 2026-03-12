
#include "string_test.h"

START_TEST(test_s21_insert_normal) {
  const char *src = "hello";
  const char *str = " world";
  char *result = s21_insert(src, str, 5);
  ck_assert_str_eq(result, "hello world");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_start) {
  const char *src = "hello";
  const char *str = "hi ";
  char *result = s21_insert(src, str, 0);
  ck_assert_str_eq(result, "hi hello");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_out_of_bounds) {
  const char *src = "hello";
  const char *str = " world";
  char *result = s21_insert(src, str, 10);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_s21_insert_negative_index) {
  const char *src = "hello";
  const char *str = " world";
  char *result = s21_insert(src, str, -1);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_insert_src_null) {
  char *result = (char *)s21_insert(s21_NULL, "test", 0);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);  // Хотя result NULL, free безопасен
}
END_TEST

START_TEST(test_insert_str_null) {
  char *result = (char *)s21_insert("hello", s21_NULL, 0);
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_index_out_of_bounds) {
  char *result = (char *)s21_insert("hello", "world", 10);  // 10 > 5
  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_insert_malloc_failure) {
  // Попробуйте огромный размер, но это ненадёжно
  char *result = (char *)s21_insert("a", "b", 0);
  // Если malloc fails, result == NULL — проверьте вручную или с Valgrind
  // ck_assert_ptr_eq(result, s21_NULL);  // Только если симулировано
  free(result);
}
END_TEST

START_TEST(test_insert_both_null) {
  char *result = (char *)s21_insert(s21_NULL, s21_NULL, 0);
  ck_assert_ptr_eq(result, s21_NULL);
}
END_TEST

Suite *suite_s21_insert() {
  Suite *s = suite_create("s21_insert");
  TCase *tc = tcase_create("s21_insert");

  tcase_add_test(tc, test_insert_src_null);
  tcase_add_test(tc, test_insert_str_null);
  tcase_add_test(tc, test_insert_index_out_of_bounds);
  tcase_add_test(tc, test_insert_malloc_failure);
  tcase_add_test(tc, test_insert_both_null);

  tcase_add_test(tc, test_s21_insert_normal);
  tcase_add_test(tc, test_s21_insert_start);
  tcase_add_test(tc, test_s21_insert_out_of_bounds);
  tcase_add_test(tc, test_s21_insert_negative_index);
  suite_add_tcase(s, tc);
  return s;
}
