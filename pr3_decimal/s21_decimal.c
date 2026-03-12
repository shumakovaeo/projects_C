#include "s21_decimal.h"

#include <math.h>
#include <stdlib.h>

#include "s21_subfunctions.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) return -1;
  init_decimal(result);
  if (!is_decimal_valid(value_1) || !is_decimal_valid(value_2)) return -1;

  int mem = 0, ostat = 0, ans = 0, diff_scale = 0;
  s21_decimal res = {0};
  if (get_sign(value_1) == get_sign(value_2)) {
    if (get_scale(value_1) != get_scale(value_2))
      ostat = scale_equal_add(&value_1, &value_2, &diff_scale);
    set_scale(&res, get_scale(value_1));
    int last_dig_odd = (value_1.bits[0] + value_2.bits[0]) % 2;
    if (ostat > 5 || (ostat == 5 && last_dig_odd == 1)) mem = 1;
    add_mantis(value_1, value_2, &res, &mem);
    int t = get_scale(res), zn = get_sign(res);
    if (mem == 1 && t > 0) {
      mem = 0;
      if (get_sign(res) == 1) {
        zn = 1;
        set_sign(&res, 0);
      }
      over_mantis(&res, t);
    }
    set_sign(&res, zn);
  } else if (get_sign(value_2) == 1)
    add_diff_sign(value_1, value_2, &res);
  else
    add_diff_sign(value_2, value_1, &res);
  if (mem == 1) {
    ans = (get_sign(res) == 0) ? 1 : 2;
    init_decimal(&res);
  }
  *result = res;
  return ans;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_negate(value_2, &value_2);
  int ans = s21_add(value_1, value_2, result);
  return ans;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) {
    return -1;
  }
  init_decimal(result);
  if (!is_decimal_valid(value_1) || !is_decimal_valid(value_2)) {
    return -1;
  }

  int code_error = 0;
  int sign_result = get_sign(value_1) ^ get_sign(value_2);
  set_sign(&value_1, 0);
  set_sign(&value_2, 0);

  code_error = mul_by_bits(value_1, value_2, result);

  if (code_error == 0) {
    set_sign(result, sign_result);
  } else {
    if (sign_result == 1) code_error = 2;
  }

  return code_error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (result == NULL) {
    return -1;
  }
  init_decimal(result);
  if (!is_decimal_valid(value_1) || !is_decimal_valid(value_2)) {
    return -1;
  }

  int code_error = 0;
  if (is_zero_decimal(value_2)) {
    code_error = 3;
  } else {
    int sign_a = get_sign(value_1);
    int sign_b = get_sign(value_2);
    int result_sign = sign_a ^ sign_b;
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);

    if (is_zero_decimal(value_1)) {
      int diff = get_scale(value_1) - get_scale(value_2);
      if (diff > 0) {
        set_scale(result, diff);
      }
    } else {
      code_error = div_by_bits(value_1, value_2, result);
      if (code_error == 0) {
        s21_decimal result_truncate = {0};
        s21_truncate(*result, &result_truncate);
        if (s21_is_equal(*result, result_truncate)) {
          *result = result_truncate;
        }
      } else if (result_sign == 1) {
        code_error = 2;
      }
    }

    set_sign(result, result_sign);
  }

  return code_error;
}

int s21_is_less(s21_decimal value1, s21_decimal value2) {
  if (!is_decimal_valid(value1) || !is_decimal_valid(value2)) {
    return -1;
  }

  int is_less = 0;
  if (is_zero_decimal(value1) && is_zero_decimal(value2)) {
    //
  } else if (s21_is_equal(value1, value2) == 0) {
    int sign1 = get_sign(value1);
    int sign2 = get_sign(value2);

    if (sign1 != sign2) {
      is_less = sign1 > sign2;
    } else {
      set_sign(&value1, 0);
      set_sign(&value2, 0);

      int result = normalize_scales(&value1, &value2);
      if (result == 0) {
        is_less = compare_by_bits(value1, value2);
      } else {
        is_less = (result == 1);
      }

      if (sign1 == 1) {
        is_less = !is_less;
      }
    }
  }

  return is_less;
}

int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2) {
  if (!is_decimal_valid(value1) || !is_decimal_valid(value2)) {
    return -1;
  }

  return s21_is_equal(value1, value2) || s21_is_less(value1, value2);
}

int s21_is_greater(s21_decimal value1, s21_decimal value2) {
  if (!is_decimal_valid(value1) || !is_decimal_valid(value2)) {
    return -1;
  }
  return !s21_is_less_or_equal(value1, value2);
}

int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2) {
  if (!is_decimal_valid(value1) || !is_decimal_valid(value2)) {
    return -1;
  }
  return !s21_is_less(value1, value2);
}

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  if (!is_decimal_valid(value1) || !is_decimal_valid(value2)) {
    return -1;
  }
  int is_equal = 1;

  if (is_zero_decimal(value1) && is_zero_decimal(value2)) {
    //
  } else if (get_sign(value1) != get_sign(value2)) {
    is_equal = 0;
  } else {
    if (normalize_scales(&value1, &value2) == 0) {
      for (size_t i = 0; i < 3 && is_equal == 1; i++) {
        if (value1.bits[i] != value2.bits[i]) {
          is_equal = 0;
        }
      }
    } else {
      is_equal = 0;
    }
  }

  return is_equal;
}

int s21_is_not_equal(s21_decimal value1, s21_decimal value2) {
  if (!is_decimal_valid(value1) || !is_decimal_valid(value2)) {
    return -1;
  }
  return !s21_is_equal(value1, value2);
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;
  init_decimal(dst);
  dst->bits[0] = (unsigned int)abs(src);

  int zn = (src >= 0) ? 0 : 1;
  set_sign(dst, zn);
  set_scale(dst, 0);
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL) return 1;
  init_decimal(dst);
  int zn = (src >= 0) ? 0 : 1, ans = 0;
  set_sign(dst, zn);
  src = (src >= 0) ? src : ((-1) * src);
  if (src == INFINITY)
    ans = 1;
  else if (src != 0 && src < 1e-28)
    ans = 1;
  else if (src == 0)
    ans = 0;
  else {
    int j = 0, k = 0, k2 = 0;
    float step = 1;
    double s = src;
    if (src > 1) {
      for (k = 0; (k < 29 && src > step); k++) step *= 10;
      k--;
      s = s / pow(10, k);
    } else {
      for (k2 = 0; (k2 < 29 && src < step); k2++) step /= 10;
      s = s * pow(10, k2);
    }
    int q = (int)s;
    int q2 = (int)((s - q) * pow(10, 6));
    int ostat = (int)((s - q) * pow(10, 7)) - q2 * 10;
    if (ostat > 5 || (ostat == 5 && (q2 % 2) == 1)) q2 += 1;
    for (j = 0; j < 6 && q2 % 10 == 0; j++) q2 = q2 / 10;
    dst->bits[0] = q * pow(10, 6 - j) + q2;
    if (k > 0 && k <= 6 - j)
      set_scale(dst, 6 - j - k);
    else if (k > 6 - j)
      for (int l = 0; l < k + j - 6; l++) ans = mulk(*dst, 10, dst);
    else if (k == 0 && (k2 == 0))
      set_scale(dst, 6 - j);
    else if (k2 > 0 && k2 + 6 - j < 29)
      set_scale(dst, 6 - j + k2);
    else if (k2 + 6 - j > 28) {
      for (int l = 0; l < k2 - 22 - j; l++) ostat = div10(*dst, dst);
      if (ostat >= 5) dst->bits[0] += 1;
      for (j = 0; j < 6 && dst->bits[0] % 10 == 0; j++)
        dst->bits[0] = dst->bits[0] / 10;
      set_scale(dst, 28 - j);
    }
  }
  return ans;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return 1;
  int ans = 0, zn = 0;
  s21_decimal temp = {0};
  temp.bits[0] = MAXNUM;
  if (get_sign(src) == 1) {
    zn = 1;
    s21_negate(src, &src);
  };
  if (s21_is_less(temp, src))
    ans = 1;
  else {
    if (get_scale(src) > 0) {
      for (int i = 0; i < get_scale(src); i++) {
        div10(src, &src);
      }
    }
    *dst = src.bits[0];
    if (zn == 1) {
      *dst = (-1) * (*dst);
    }
  }
  return ans;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return 1;
  }
  *dst = 0.0f;
  if (!is_decimal_valid(src)) {
    return 1;
  }

  int code_error = 0;
  int sign = get_sign(src);
  set_sign(&src, 0);

  long double result = 0.0L;
  if (!is_zero_decimal(src)) {
    long double pow2_32 = powl(2.0L, 32.0L);
    long double pow2_64 = powl(2.0L, 64.0L);

    result = (long double)src.bits[2] * pow2_64;
    result += (long double)src.bits[1] * pow2_32;
    result += (long double)src.bits[0];

    code_error = round_number_by_decimal(src, &result);
  }

  if (code_error == 0) {
    *dst = (float)result;
    if (sign == 1) {
      *dst *= -1;
    }
  }

  return code_error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  return general_rounding(value, result, 1);
}

int s21_round(s21_decimal value, s21_decimal *result) {
  return general_rounding(value, result, 2);
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  return general_rounding(value, result, 0);
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return 1;
  }
  int code_error = 0;
  if (!is_decimal_valid(value)) {
    code_error = 1;
    init_decimal(result);
  } else {
    *result = value;
    int sign = get_sign(value);
    set_sign(result, !sign);
  }

  return code_error;
}
