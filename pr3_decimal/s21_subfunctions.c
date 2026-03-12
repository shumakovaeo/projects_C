#include "s21_subfunctions.h"

#include <stdlib.h>

void add_diff_sign(s21_decimal value_1, s21_decimal value_2, s21_decimal *res) {
  s21_decimal maxdiv10 = {{2576980377, 2576980377, 429496729, 0}},
              ostat_dec = {0}, zero = {0};
  int ostat = 0;
  s21_negate(value_2, &value_2);
  if (s21_is_less_or_equal(value_2, value_1)) {  //|v2|<=v1  v1-|v2|
    set_sign(res, 0);
    ostat = sub_normal(value_1, value_2, res, &ostat_dec);
  } else {
    set_sign(res, 1);
    ostat = sub_normal(value_2, value_1, res, &ostat_dec);
  }
  while (is_less_or_equal_mantis(*res, maxdiv10) &&
         s21_is_greater(ostat_dec, zero))
    ostat = sub_normal(*res, ostat_dec, res, &ostat_dec);
  if (ostat > 5 || (ostat == 5 && ((res->bits[0]) % 2) == 1)) res->bits[0] -= 1;
}

int sub_normal(s21_decimal value_1, s21_decimal value_2, s21_decimal *res,
               s21_decimal *ostat_dec) {
  int ostat = 0;
  if (get_scale(value_1) != get_scale(value_2))
    ostat = scale_equal_sub(&value_1, &value_2, ostat_dec);

  set_scale(res, get_scale(value_1));
  sub_mantis(value_1, value_2, res);

  return ostat;
}

void sub_mantis(s21_decimal value_1, s21_decimal value_2, s21_decimal *res) {
  int mem = 0;
  for (int j = 0; j <= 2; j++) {
    if (value_1.bits[j] - mem >= value_2.bits[j]) {
      res->bits[j] = value_1.bits[j] - value_2.bits[j] - mem;
      mem = 0;
    } else {
      res->bits[j] = MAXNUM - value_2.bits[j] + 1 + value_1.bits[j] - mem;
      mem = 1;
    }
  }
}

void add_mantis(s21_decimal value_1, s21_decimal value_2, s21_decimal *res,
                int *mem) {
  set_sign(res, get_sign(value_1));
  for (int j = 0; j <= 2; j++) {
    if ((value_1.bits[j] == MAXNUM && value_2.bits[j] == 0 && *mem == 0) ||
        (value_2.bits[j] == MAXNUM && value_1.bits[j] == 0 && *mem == 0)) {
      res->bits[j] = MAXNUM;
    } else if (value_1.bits[j] == MAXNUM || value_2.bits[j] == MAXNUM ||
               MAXNUM - value_1.bits[j] < value_2.bits[j] + *mem ||
               MAXNUM - value_2.bits[j] < value_1.bits[j] + *mem) {
      res->bits[j] = value_1.bits[j] - MAXNUM - 1 + value_2.bits[j] + *mem;
      *mem = 1;
    } else {
      res->bits[j] = value_1.bits[j] + value_2.bits[j] + *mem;
      *mem = 0;
    }
  }
}

void over_mantis(s21_decimal *value, int scale) {
  int ost = div10(*value, value);
  int mem = 0;
  set_scale(value, scale - 1);

  s21_decimal maxdiv10 = {{2576980377, 2576980377, 429496729, 0}};

  set_scale(&maxdiv10, scale - 1);
  add_mantis(*value, maxdiv10, value, &mem);
  if (ost > 9 || (ost == 9 && (value->bits[0]) % 2 == 0))
    value->bits[0] += 2;
  else
    value->bits[0] += 1;
}

int scale_equal_add(s21_decimal *value_1, s21_decimal *value_2,
                    int *diff_scale) {
  int scale1 = get_scale(*value_1), scale2 = get_scale(*value_2), r = 0, fl = 1;
  s21_decimal maxdiv10 = {{2576980377, 2576980377, 429496729, 0}}, min = {0},
              max = {0};
  int sc = abs(scale1 - scale2);
  if (scale1 < scale2) {
    min = *value_2;
    max = *value_1;
  } else {
    min = *value_1;
    max = *value_2;
    scale1 = scale2;
    scale2 = get_scale(*value_1);
    fl = 2;
  }
  for (int i = 1; (i <= sc); i++) {
    if (is_less_or_equal_mantis(max, maxdiv10)) {
      mulk(max, 10, &max);
      scale1 += 1;
      set_scale(&max, scale1);
    } else {
      r = div10(min, &min);
      scale2 -= 1;
      *diff_scale += 1;
      set_scale(&min, scale2);
    }
  }
  if (fl == 1) {
    *value_2 = min;
    *value_1 = max;
  } else {
    *value_1 = min;
    *value_2 = max;
  }
  return r;
}

int scale_equal_sub(s21_decimal *value_1, s21_decimal *value_2,
                    s21_decimal *ostat_dec) {
  s21_decimal temp = *value_2, temp2 = {0};
  int diff_scale = 0, r = 0;
  r = scale_equal_add(value_1, value_2, &diff_scale);
  if (diff_scale != 0) {
    temp2 = *value_2;
    for (int i = 0; i < (diff_scale); i++) mulk(temp2, 10, &temp2);
    sub_mantis(temp, temp2, ostat_dec);
    set_scale(ostat_dec, diff_scale + get_scale(*value_2));
  } else
    *ostat_dec = temp2;
  return r;
}

int is_less_or_equal_mantis(s21_decimal val1, s21_decimal val2) {
  int ans = 0;
  if (val1.bits[2] < val2.bits[2]) {
    ans = 1;
  } else if (val1.bits[2] == val2.bits[2] && val1.bits[1] < val2.bits[1]) {
    ans = 1;
  } else if (val1.bits[2] == val2.bits[2] && val1.bits[1] == val2.bits[1] &&
             val1.bits[0] <= val2.bits[0]) {
    ans = 1;
  }
  return ans;
}

int mul_by_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code_error = 0;

  s21_big_decimal tmp = {0};
  int result_scale = get_scale(value_1) + get_scale(value_2);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      unsigned int a = value_1.bits[i];
      unsigned int b = value_2.bits[j];

      if (a != 0 && b != 0) {
        unsigned long long product = (unsigned long long)a * b;
        add_product_to_big_decimal(&tmp, product, i + j);
      }
    }
  }

  code_error = big_decimal_to_decimal(tmp, result, result_scale);

  return code_error;
}

void add_product_to_big_decimal(s21_big_decimal *tmp,
                                unsigned long long product, int pos) {
  unsigned long long sum = (product & 0xFFFFFFFFULL) + tmp->bits[pos];
  tmp->bits[pos] = sum & 0xFFFFFFFFULL;
  unsigned long long carry = sum >> 32;

  if (pos + 1 < 6) {
    int pos_next = pos + 1;
    sum = tmp->bits[pos_next] + (product >> 32) + carry;
    tmp->bits[pos_next] = sum & 0xFFFFFFFFULL;
    carry = sum >> 32;

    for (int k = pos_next + 1; k < 6 && carry > 0; k++) {
      sum = tmp->bits[k] + carry;
      tmp->bits[k] = sum & 0xFFFFFFFFULL;
      carry = sum >> 32;
    }
  }
}

int big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result,
                           int result_scale) {
  int code_error = 0;
  if (is_big_decimal(value) == 1 || result_scale > 28) {
    code_error = convert_big_decimal_to_decimal(value, result, &result_scale);
  } else {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
  }

  if (code_error == 0) {
    set_scale(result, result_scale);

    if (is_zero_decimal(*result) == 1 && result_scale == 28) {
      code_error = 2;
    }
  }

  return code_error;
}

int convert_big_decimal_to_decimal(s21_big_decimal value, s21_decimal *result,
                                   int *scale) {
  int code_error = 0;
  int result_scale = *scale;
  unsigned long long remainder = 0;
  int count_digits = 0;

  while ((result_scale > 0 && is_big_decimal(value) == 1) ||
         result_scale > 28) {
    remainder = 0;
    for (int i = 5; i >= 0; i--) {
      unsigned long long current = (remainder << 32) | value.bits[i];
      value.bits[i] = current / 10;
      remainder = current % 10;
    }
    result_scale--;

    if (remainder != 0) {
      count_digits++;
    }
  }

  if (is_big_decimal(value)) {
    code_error = 1;
  } else {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];

    int curr_digit = remainder;
    apply_bankers_rounding(result, curr_digit, count_digits);
    *scale = result_scale;
  }

  return code_error;
}

int div_by_bits(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int result_scale = get_scale(value_1) - get_scale(value_2);
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);

  s21_big_decimal remainder = {0};
  decimal_to_big_decimal(value_1, &remainder);

  s21_decimal quotient = {0};
  if (s21_is_greater_or_equal(value_1, value_2)) {
    div_big_decimal(&remainder, value_2, &quotient);
  }

  if (!is_zero_big_decimal(remainder)) {
    add_frac_part_to_decimal(&quotient, remainder, value_2, &result_scale);
  }

  int code_error = 0;
  if (result_scale < 0) {
    int exp = -result_scale;
    result_scale = 0;

    for (int i = 0; i < exp && code_error == 0; i++) {
      code_error = mul_by_10(&quotient);
    }
  }

  if (code_error == 0) {
    set_scale(&quotient, result_scale);
    *result = quotient;
  }

  return code_error;
}

void add_frac_part_to_decimal(s21_decimal *quotient, s21_big_decimal remainder,
                              s21_decimal value_2, int *result_scale) {
  int overflow = 0;
  int overscale = 0;
  s21_decimal curr_quotient = {0};
  while (overflow == 0 && overscale == 0 && !is_zero_big_decimal(remainder)) {
    mul_by_10_big_decimal(&remainder);
    div_big_decimal(&remainder, value_2, &curr_quotient);

    if (*result_scale < 28) {
      if (mul_by_10(quotient) != 0) {
        overflow = 1;
      } else {
        s21_add(*quotient, curr_quotient, quotient);
        (*result_scale)++;
      }
    } else {
      overscale = 1;
    }
  }

  if (overflow != 0 || overscale != 0) {
    int curr_digit = curr_quotient.bits[0];
    int count_digits = 1;
    if (!is_zero_big_decimal(remainder)) {
      count_digits++;
    }
    apply_bankers_rounding(quotient, curr_digit, count_digits);
    if (overscale != 0) {
      *result_scale = 28;
    }
  }
}

int mul_by_10_big_decimal(s21_big_decimal *value) {
  int code_error = 0;
  s21_big_decimal result = {0};

  unsigned int carry = 0;

  for (int i = 0; i < 6; i++) {
    unsigned long long sum = (unsigned long long)value->bits[i] * 10 + carry;
    result.bits[i] = sum & 0xFFFFFFFFULL;
    carry = sum >> 32;
  }

  if (carry != 0) {
    code_error = 1;
  } else {
    *value = result;
  }

  return code_error;
}

void div_big_decimal(s21_big_decimal *curr_remainder, s21_decimal divisor,
                     s21_decimal *quotient) {
  init_decimal(quotient);
  int max_bit = -1;
  for (int i = 191; i >= 0 && max_bit == -1; i--) {
    if (get_bit_big_decimal(*curr_remainder, i) == 1) {
      max_bit = i;
    }
  }

  if (max_bit != -1) {
    s21_big_decimal new_remainder = {0};
    for (int i = max_bit; i >= 0; i--) {
      left_shift_big_decimal(&new_remainder);

      if (get_bit_big_decimal(*curr_remainder, i) == 1) {
        set_bit_big_decimal(&new_remainder, 0, 1);
      }

      if (is_greater_or_equal_big_decimal(new_remainder, divisor)) {
        sub_big_decimal(new_remainder, divisor, &new_remainder);
        set_bit(quotient, i, 1);
      }
    }
    *curr_remainder = new_remainder;
  }
}

void left_shift_big_decimal(s21_big_decimal *num) {
  unsigned int carry = 0;
  for (int i = 0; i < 6; i++) {
    unsigned int new_carry = (num->bits[i] >> 31) & 1;
    num->bits[i] = (num->bits[i] << 1) | carry;
    carry = new_carry;
  }
}

int get_bit_big_decimal(s21_big_decimal num, int position) {
  int result = 0;
  if (position >= 0 && position <= 191) {
    int i = position / 32;
    int bit = position % 32;
    result = (num.bits[i] >> bit) & 1;
  }
  return result;
}

void set_bit_big_decimal(s21_big_decimal *num, int position, int value) {
  if (position >= 0 && position <= 191) {
    int i = position / 32;
    int bit = position % 32;
    if (value) {
      num->bits[i] |= (1u << bit);
    } else {
      num->bits[i] &= ~(1u << bit);
    }
  }
}

void set_bit(s21_decimal *num, int position, int value) {
  if (position >= 0 && position <= 95) {
    int i = position / 32;
    int bit = position % 32;
    if (value) {
      num->bits[i] |= (1u << bit);
    } else {
      num->bits[i] &= ~(1u << bit);
    }
  }
}

int is_greater_or_equal_big_decimal(s21_big_decimal value_big_decimal,
                                    s21_decimal value_2) {
  int result = 0;
  if (is_big_decimal(value_big_decimal) == 1) {
    result = 1;
  } else {
    s21_decimal value_1 = {0};
    value_1.bits[0] = value_big_decimal.bits[0];
    value_1.bits[1] = value_big_decimal.bits[1];
    value_1.bits[2] = value_big_decimal.bits[2];

    result = s21_is_greater_or_equal(value_1, value_2);
  }

  return result;
}

void sub_big_decimal(s21_big_decimal value_1, s21_decimal value_decimal,
                     s21_big_decimal *result) {
  s21_big_decimal value_2 = {0};
  decimal_to_big_decimal(value_decimal, &value_2);

  int borrow = 0;
  for (int i = 0; i < 6; i++) {
    unsigned long long a = (unsigned long long)value_1.bits[i];
    unsigned long long b = (unsigned long long)value_2.bits[i] + borrow;

    if (a >= b) {
      result->bits[i] = (unsigned int)(a - b);
      borrow = 0;
    } else {
      unsigned long long base = 1ULL << 32;
      unsigned long long diff = base + a - b;
      result->bits[i] = (unsigned int)diff;
      borrow = 1;
    }
  }
}

int normalize_scales(s21_decimal *value_1, s21_decimal *value_2) {
  int result = 0;
  int diff = get_scale(*value_1) - get_scale(*value_2);
  if (diff != 0) {
    int exp = diff;
    s21_decimal value_to_increase = {0};
    if (diff > 0) {
      value_to_increase = *value_2;
    } else {
      exp *= -1;
      value_to_increase = *value_1;
    }

    int code_error = 0;
    for (int i = 0; i < exp && code_error == 0; i++) {
      code_error = mul_by_10(&value_to_increase);
    }

    if (code_error == 0) {
      int curr_scale = get_scale(value_to_increase);
      set_scale(&value_to_increase, curr_scale + exp);

      if (diff > 0) {
        *value_2 = value_to_increase;
      } else {
        *value_1 = value_to_increase;
      }
    } else {
      result = diff > 0 ? 1 : -1;
    }
  }
  return result;
}

int compare_by_bits(s21_decimal value1, s21_decimal value2) {
  int is_less = 0;
  int is_not_equal = 0;

  for (int i = 2; i >= 0 && is_not_equal == 0; i--) {
    if (value1.bits[i] != value2.bits[i]) {
      is_less = value1.bits[i] < value2.bits[i];
      is_not_equal = 1;
    }
  }

  return is_less;
}

int round_number_by_decimal(s21_decimal src, long double *result) {
  int exp = 0;
  while (*result > 9999999.0) {
    (*result) /= 10.0L;
    exp++;
  }

  int scale = get_scale(src);
  set_scale(&src, exp);

  s21_decimal src_round = {0};
  int code_error = bankers_round(src, &src_round);

  if (code_error == 0) {
    long double final_num = src_round.bits[0];

    if (exp > scale) {
      exp -= scale;
      for (int i = 0; i < exp; i++) {
        final_num *= 10.0L;
      }

    } else if (scale > exp) {
      scale -= exp;
      for (int i = 0; i < scale; i++) {
        final_num /= 10.0L;
      }
    }

    *result = final_num;
  }

  return code_error;
}

int bankers_round(s21_decimal value, s21_decimal *result) {
  return general_rounding(value, result, 3);
}

int general_rounding(s21_decimal value, s21_decimal *result,
                     int type_rounding) {
  if (result == NULL) {
    return 1;
  }
  init_decimal(result);
  if (!is_decimal_valid(value)) {
    return 1;
  }

  if (is_zero_decimal(value)) {
    set_sign(result, get_sign(value));
  } else {
    *result = value;
    if (get_scale(value) != 0) {
      general_rounding_by_bits(result, type_rounding);
    }
  }

  return 0;
}

void general_rounding_by_bits(s21_decimal *result, int type_rounding) {
  int scale = get_scale(*result);
  int sign = get_sign(*result);
  if (sign == 1) {
    set_sign(result, 0);
  }

  int count_digits = 0;
  unsigned long long remainder = 0;
  for (int i = 0; i < scale && !is_zero_decimal(*result); i++) {
    remainder = 0;
    for (int j = 2; j >= 0; j--) {
      unsigned long long number =
          ((unsigned long long)remainder << 32) | result->bits[j];
      result->bits[j] = (unsigned int)(number / 10);
      remainder = number % 10;
    }
    if (remainder != 0) {
      count_digits++;
    }
  }

  set_scale(result, 0);
  int curr_digit = remainder;

  if (type_rounding == 1) {
    apply_floor_rounding(result, sign, count_digits);
  } else if (type_rounding == 2) {
    apply_math_rounding(result, curr_digit);
  } else if (type_rounding == 3) {
    apply_bankers_rounding(result, curr_digit, count_digits);
  }

  set_sign(result, sign);
}

void apply_floor_rounding(s21_decimal *result, int sign, int count_digits) {
  if (count_digits != 0 && sign == 1) {
    s21_add(*result, (s21_decimal){{1, 0, 0, 0}}, result);
  }
}

void apply_math_rounding(s21_decimal *result, int curr_digit) {
  if (curr_digit >= 5) {
    s21_add(*result, (s21_decimal){{1, 0, 0, 0}}, result);
  }
}

void apply_bankers_rounding(s21_decimal *result, int curr_digit,
                            int count_digits) {
  int round_up = 0;
  if (curr_digit > 5) {
    round_up = 1;
  } else if (curr_digit == 5 && count_digits > 1) {
    round_up = 1;
  } else if (curr_digit == 5 && (result->bits[0] & 1)) {
    round_up = 1;
  }

  if (round_up == 1) {
    s21_add(*result, (s21_decimal){{1, 0, 0, 0}}, result);
  }
}
