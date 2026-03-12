#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

typedef struct {
  unsigned int bits[4];
} s21_decimal;

// 1. Арифметические операторы
/*Возвращаемое значение — код ошибки:
0 — OK;
1 — число слишком велико или равно бесконечности;
2 — число слишком мало или равно отрицательной бесконечности;
3 — деление на 0.*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// 2. Операторы сравнения
/*Возвращаемое значение:
0 — FALSE;
1 — TRUE.*/
int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);

// 3. Преобразователи
/*Возвращаемое значение — код ошибки:
0 — OK;
1 — ошибка конвертации.*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// 4. Другие функции
/*Возвращаемое значение — код ошибки:
0 — OK;
1 — ошибка вычисления.*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif