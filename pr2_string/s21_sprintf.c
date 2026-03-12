#include "s21_sprintf.h"

void s21_parse_flags(const char** fmt, int* minus, int* plus, int* space,
                     int* hash, int* zero) {
  int is_target = 1;
  while (is_target && **fmt) {
    if (**fmt == '-')
      *minus = 1;
    else if (**fmt == '+')
      *plus = 1;
    else if (**fmt == ' ')
      *space = 1;
    else if (**fmt == '#')
      *hash = 1;
    else if (**fmt == '0')
      *zero = 1;
    else
      is_target = 0;
    if (is_target) (*fmt)++;
  }
}

void s21_parse_width(const char** fmt, va_list* args, int* width) {
  char buffer[20];
  int i = 0;
  *width = 0;
  if (**fmt == '*') {
    *width = va_arg(*args, int);
    (*fmt)++;
  } else if (**fmt >= '0' && **fmt <= '9') {
    while (**fmt >= '0' && **fmt <= '9' && i < 19) {
      buffer[i] = **fmt;
      i++;
      (*fmt)++;
    }
    buffer[i] = '\0';
    *width = atoi(buffer);
  }
}

void s21_parse_precision(const char** fmt, va_list* args, int* precision) {
  char buffer[20];
  if (**fmt == '.') {
    (*fmt)++;
    if (**fmt == '*') {
      *precision = va_arg(*args, int);
      if (*precision < 0) *precision = 6;
      (*fmt)++;
    } else {
      int i = 0;
      *precision = 0;
      if (**fmt >= '0' && **fmt <= '9') {
        while (**fmt >= '0' && **fmt <= '9' && i < 19) {
          buffer[i] = **fmt;
          i++;
          (*fmt)++;
        }
        buffer[i] = '\0';
        *precision = atoi(buffer);
      } else {
        *precision = -2;
      }
    }
  }
}

void s21_parse_length(const char** fmt, int* len_h, int* len_l, int* len_L) {
  int found = 0;
  if (!found && **fmt == 'h') {
    (*fmt)++;
    if (**fmt == 'h')
      *len_h = 2, (*fmt)++;
    else
      *len_h = 1;
    found = 1;
  }
  if (!found && **fmt == 'l') {
    (*fmt)++;
    if (**fmt == 'l')
      *len_l = 2, (*fmt)++;
    else
      *len_l = 1;
    found = 1;
  }
  if (!found && **fmt == 'L') {
    *len_L = 1;
    (*fmt)++;
    found = 1;
  }
}

void s21_reverse(char* buf, int len) {
  int i = 0, j = len - 1;
  while (i < j) {
    char t = buf[i];
    buf[i] = buf[j];
    buf[j] = t;
    i++;
    j--;
  }
}

int s21_int_to_str(long long value, char* buf) {
  int length = 0;
  if (value == 0) {
    buf[0] = '0';
    buf[1] = '\0';
    length = 1;
  } else {
    if (value == LLONG_MIN) {
      const char* min_str = "9223372036854775808";
      int i = 0;
      while (min_str[i]) {
        buf[i] = min_str[i];
        i++;
      }
      buf[i] = '\0';
      length = i;
    } else {
      if (value < 0) value = -value;
      int i = 0;
      while (value > 0) {
        buf[i] = '0' + value % 10;
        value = value / 10;
        i++;
      }
      s21_reverse(buf, i);
      buf[i] = '\0';
      length = i;
    }
  }
  return length;
}

int s21_uint_to_base(unsigned long long value, char* buf, int base,
                     int uppercase) {
  int done = 0;
  int length = 0;
  if (base < 2 || base > 36) {
    buf[0] = '\0';
    done = 1;
  }
  if (value == 0) {
    buf[0] = '0';
    buf[1] = '\0';
    done = 1;
    length = 1;
  }
  if (!done) {
    const char* digits = uppercase ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   : "0123456789abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    unsigned long long num = value;
    while (num > 0) {
      buf[i] = digits[num % base];
      num = num / base;
      i++;
    }
    s21_reverse(buf, i);
    buf[i] = '\0';
    length = i;
  }
  return length;
}

int s21_handle_special_double(long double value, char* buf) {
  int length = 0;
  if (value != value) {
    s21_strncpy(buf, "nan", 3);
    length = 3;
  } else if (isinf(value) || value == INFINITY || value == -INFINITY) {
    if (value < 0) {
      s21_strncpy(buf, "-inf", 4);
      length = 4;
    } else {
      s21_strncpy(buf, "inf", 3);
      length = 3;
    }
  }
  return length;
}

int s21_round_fractional(long double fract, int precision, char* frac_buf,
                         unsigned long long* int_part, long double eps) {
  int fract_len = 0;
  for (int i = 0; i < precision; i++) {
    long double t = fract * 10.0L;
    int digit = (int)floorl(t + eps);
    long double res = t - digit;
    if (res < eps)
      res = 0.0L;
    else if (res > 1.0L - eps) {
      digit++;
      res -= 1.0L;
    }
    frac_buf[fract_len++] = (char)('0' + digit);
    fract = res;
  }
  long double t = fract * 10.0L;
  int next_digit = (int)floorl(t + eps);
  long double remainder = t - next_digit;
  if (remainder < 0) remainder = 0;
  if (remainder > 1.0L) remainder = 1.0L;
  int round_up = 0;
  if (next_digit > 5)
    round_up = 1;
  else if (next_digit < 5)
    round_up = 0;
  else {
    if (remainder > eps)
      round_up = 1;
    else {
      int last = fract_len > 0 ? (frac_buf[fract_len - 1] - '0')
                               : (int)(*int_part % 10);
      if (last % 2 != 0) round_up = 1;
    }
  }
  if (round_up) {
    int j = precision - 1;
    while (j >= 0 && frac_buf[j] == '9') {
      frac_buf[j] = '0';
      j--;
    }
    if (j >= 0)
      frac_buf[j] = (char)(frac_buf[j] + 1);
    else
      (*int_part)++;
  }
  return fract_len;
}

int s21_write_fixed_result(unsigned long long int_part, int is_negative,
                           char* int_buf, char* frac_buf, int frac_len,
                           char* buf) {
  int int_len = s21_uint_to_base(int_part, int_buf, 10, 0);
  int pos = 0;
  if (is_negative) buf[pos++] = '-';
  for (int k = 0; k < int_len; k++) buf[pos++] = int_buf[k];
  if (frac_len > 0) {
    buf[pos++] = '.';
    for (int k = 0; k < frac_len; k++) buf[pos++] = frac_buf[k];
  }
  buf[pos] = '\0';
  return pos;
}

int s21_double_to_fixed(long double value, char* buf, int precision) {
  int is_negative = 0;
  int length = 0;
  long double abs_value = value;
  const long double eps = 1e-18L;
  if (precision < 0) precision = 6;
  int special_length = s21_handle_special_double(value, buf);
  if (special_length) {
    length = special_length;
  } else {
    if (value < 0) is_negative = 1, abs_value = -value;
    unsigned long long int_part = (unsigned long long)floorl(abs_value);
    long double fract = abs_value - (long double)int_part;
    char int_buf[65];
    char frac_buf[256];
    if (precision == 0) {
      long double t = fract * 10.0L;
      int next_digit = (int)floorl(t + eps);
      long double remainder = t - next_digit;
      if (remainder < 0) remainder = 0;
      if (remainder > 1.0L) remainder = 1.0L;
      int round_up = 0;
      if (next_digit > 5)
        round_up = 1;
      else if (next_digit < 5)
        round_up = 0;
      else {
        if (remainder > eps)
          round_up = 1;
        else {
          int last = (int)(int_part % 10);
          if (last % 2 != 0) round_up = 1;
        }
      }
      if (round_up) int_part++;
      int pos = 0;
      if (is_negative) buf[pos++] = '-';
      int len = s21_uint_to_base(int_part, int_buf, 10, 0);
      for (int i = 0; i < len; i++) buf[pos++] = int_buf[i];
      buf[pos] = '\0';
      length = pos;
    } else {
      int frac_len =
          s21_round_fractional(fract, precision, frac_buf, &int_part, eps);
      length = s21_write_fixed_result(int_part, is_negative, int_buf, frac_buf,
                                      frac_len, buf);
    }
  }
  return length;
}

int s21_write_exp_result(unsigned long long int_part, char* int_buf,
                         char* frac_buf, int frac_len, int exponent,
                         int is_negative, int uppercase, char* buf) {
  int int_len = s21_uint_to_base(int_part, int_buf, 10, 0);
  int pos = 0;
  if (is_negative) buf[pos++] = '-';
  for (int i = 0; i < int_len; i++) buf[pos++] = int_buf[i];
  if (frac_len > 0) {
    buf[pos++] = '.';
    for (int i = 0; i < frac_len; i++) buf[pos++] = frac_buf[i];
  }
  buf[pos++] = uppercase ? 'E' : 'e';
  if (exponent >= 0)
    buf[pos++] = '+';
  else
    buf[pos++] = '-', exponent = -exponent;
  if (exponent < 10) {
    buf[pos++] = '0';
    buf[pos++] = '0' + exponent;
  } else {
    char exp_buf[32];
    int exp_len = s21_uint_to_base(exponent, exp_buf, 10, 0);
    for (int i = 0; i < exp_len; i++) buf[pos++] = exp_buf[i];
  }
  buf[pos] = '\0';
  return pos;
}

static int s21_double_to_exp_finite(long double value, char* buf, int precision,
                                    int uppercase, int is_negative,
                                    long double abs_value) {
  int length = 0;
  int exponent = 0;
  long double temp = abs_value;
  int finite_flag = isfinite(temp) ? 1 : 0;

  while (finite_flag && temp >= 10.0L) {
    temp /= 10.0L;
    exponent++;
    finite_flag = isfinite(temp) ? 1 : 0;
  }
  while (finite_flag && temp < 1.0L && temp > 0.0L) {
    temp *= 10.0L;
    exponent--;
    finite_flag = isfinite(temp) ? 1 : 0;
  }

  if (!finite_flag) {
    length = s21_handle_special_double(value, buf);
  } else {
    long double mantissa = temp;
    unsigned long long int_part = (unsigned long long)mantissa;
    long double frac_part = mantissa - (long double)int_part;
    long double scaling = powl(10.0L, precision);
    long double scaled = frac_part * scaling + 0.5L;
    unsigned long long fract_int = (unsigned long long)scaled;
    if (fract_int >= (unsigned long long)scaling) {
      int_part++;
      fract_int = 0;
      if (int_part >= 10) int_part = 1, exponent++;
    }
    char int_buf[65], frac_buf[256];
    int frac_len = 0;
    if (precision > 0) {
      unsigned long long tempv = fract_int;
      if (tempv == 0) {
        for (int i = 0; i < precision; i++) frac_buf[frac_len++] = '0';
      } else {
        while (tempv > 0) {
          frac_buf[frac_len++] = (char)('0' + (tempv % 10));
          tempv /= 10;
        }
        while (frac_len < precision) frac_buf[frac_len++] = '0';
        s21_reverse(frac_buf, frac_len);
      }
    }
    length = s21_write_exp_result(int_part, int_buf, frac_buf, frac_len,
                                  exponent, is_negative, uppercase, buf);
  }
  return length;
}

int s21_double_to_exp(long double value, char* buf, int precision,
                      int uppercase) {
  int is_negative = 0, length = 0;
  long double abs_value = value;
  if (precision < 0) precision = 6;
  int special_length = s21_handle_special_double(value, buf);
  if (special_length) {
    length = special_length;
  } else {
    if (value == 0) {
      int pos = 0;
      buf[pos++] = '0';
      if (precision > 0) {
        buf[pos++] = '.';
        for (int i = 0; i < precision; i++) buf[pos++] = '0';
      }
      buf[pos++] = uppercase ? 'E' : 'e';
      buf[pos++] = '+';
      buf[pos++] = '0';
      buf[pos++] = '0';
      buf[pos] = '\0';
      length = pos;
    } else {
      if (value < 0) is_negative = 1, abs_value = -value;
      length = s21_double_to_exp_finite(value, buf, precision, uppercase,
                                        is_negative, abs_value);
    }
  }
  return length;
}

int s21_double_to_general(long double value, char* buf, int precision,
                          int uppercase) {
  int length = 0;
  if (precision == 0) precision = 1;
  if (precision < 0) precision = 6;
  int special_length = s21_handle_special_double(value, buf);
  if (special_length) {
    length = special_length;
  } else {
    long double abs_value = fabsl(value);
    int exponent = abs_value != 0.0L ? (int)floorl(log10l(abs_value)) : 0;
    int use_exp = (exponent < -4 || exponent >= precision) ? 1 : 0;
    if (!use_exp) {
      int decimal_places = precision - 1 - exponent;
      if (decimal_places < 0) decimal_places = 0;
      length = s21_double_to_fixed(value, buf, decimal_places);
      if (decimal_places == 0) {
        long double rounded = floorl(abs_value + 0.5L);
        int new_exp = rounded != 0.0L ? (int)floorl(log10l(rounded)) : 0;
        if (new_exp > exponent) {
          length = s21_double_to_exp(value, buf, precision - 1, uppercase);
        }
      }
    } else {
      length = s21_double_to_exp(value, buf, precision - 1, uppercase);
    }
  }
  return length;
}

void s21_handle_char(char** out, va_list* args, int width, int minus) {
  char target = (char)va_arg(*args, int);
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  int padding = width - 1;
  if (width && !minus) {
    for (int i = 0; i < padding; i++) *(*out)++ = ' ';
    *(*out)++ = target;
  } else if (width && minus) {
    *(*out)++ = target;
    for (int i = 0; i < padding; i++) *(*out)++ = ' ';
  } else
    *(*out)++ = target;
}

void s21_handle_string(char** out, va_list* args, int width, int precision,
                       int minus) {
  char* target = va_arg(*args, char*);
  if (precision == -2) precision = 0;
  if (target == NULL) target = "(null)";
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  int len = 0;
  while (target[len] != '\0' && (precision < 0 || len < precision)) len++;
  int padding = width - len;
  if (padding < 0) padding = 0;
  if (padding && !minus)
    for (int i = 0; i < padding; i++) *(*out)++ = ' ';
  for (int i = 0; i < len; i++) *(*out)++ = target[i];
  if (padding && minus)
    for (int i = 0; i < padding; i++) *(*out)++ = ' ';
}

void s21_handle_padding(char** out, int width, int total_len, int minus,
                        int zero, int precision, const char* content,
                        int content_len) {
  int padding = width - total_len;
  if (padding < 0) padding = 0;
  char pad_char = ' ';
  if (zero && !minus && precision < 0) pad_char = '0';
  if (!minus) {
    if (pad_char == '0') {
      int index = 0;
      if (content_len >= 1 &&
          (content[0] == '+' || content[0] == '-' || content[0] == ' ')) {
        *(*out)++ = content[0];
        index = 1;
      } else if (content_len >= 2 && content[0] == '0' &&
                 (content[1] == 'x' || content[1] == 'X')) {
        *(*out)++ = '0';
        *(*out)++ = content[1];
        index = 2;
      }
      for (int i = 0; i < padding; i++) *(*out)++ = '0';
      for (int i = index; i < content_len; i++) *(*out)++ = content[i];
    } else {
      for (int i = 0; i < padding; i++) *(*out)++ = pad_char;
      for (int i = 0; i < content_len; i++) *(*out)++ = content[i];
    }
  } else {
    for (int i = 0; i < content_len; i++) *(*out)++ = content[i];
    for (int i = 0; i < padding; i++) *(*out)++ = ' ';
  }
}

void s21_handle_signed(char** out, va_list* args, int width, int precision,
                       int minus, int plus, int space, int zero, int len_h,
                       int len_l) {
  long long value;
  if (len_l == 2)
    value = va_arg(*args, long long);
  else if (len_l == 1)
    value = va_arg(*args, long);
  else if (len_h == 2)
    value = (signed char)va_arg(*args, int);
  else if (len_h == 1)
    value = (short)va_arg(*args, int);
  else
    value = va_arg(*args, int);
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  if (precision < 0) precision = -1;
  char num_buf[65];
  int num_len;
  if (precision == 0 && value == 0) {
    num_len = 0;
    num_buf[0] = '\0';
  } else {
    num_len = s21_int_to_str(llabs(value), num_buf);
  }
  char sign_char = '\0';
  if (value < 0)
    sign_char = '-';
  else if (value >= 0) {
    if (plus)
      sign_char = '+';
    else if (space)
      sign_char = ' ';
  }
  int zeros_needed = 0;
  if (precision > num_len) zeros_needed = precision - num_len;
  int content_len = num_len + zeros_needed;
  if (sign_char != '\0') content_len++;
  char content_buf[128];
  int content_pos = 0;
  if (sign_char != '\0') content_buf[content_pos++] = sign_char;
  for (int i = 0; i < zeros_needed; i++) content_buf[content_pos++] = '0';
  for (int i = 0; i < num_len; i++) content_buf[content_pos++] = num_buf[i];
  int use_zero_padding = (precision < 0) && zero;
  s21_handle_padding(out, width, content_len, minus, use_zero_padding,
                     precision, content_buf, content_pos);
}

void s21_handle_unsigned(char** out, va_list* args, int width, int precision,
                         int minus, int zero, int len_h, int len_l) {
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  if (minus && width == 0) width = 10;
  unsigned long long value;
  if (len_l == 2)
    value = va_arg(*args, unsigned long long);
  else if (len_l == 1)
    value = va_arg(*args, unsigned long);
  else if (len_h == 2)
    value = (unsigned char)va_arg(*args, unsigned int);
  else if (len_h == 1)
    value = (unsigned short)va_arg(*args, unsigned int);
  else
    value = va_arg(*args, unsigned int);
  char num_buf[65];
  int num_len = s21_uint_to_base(value, num_buf, 10, 0);
  if (precision == 0 && value == 0) num_len = 0;
  int zeros_needed = 0;
  if (precision > num_len) zeros_needed = precision - num_len;
  int total_len = num_len + zeros_needed;
  char content_buf[128];
  int content_pos = 0;
  for (int i = 0; i < zeros_needed; i++) content_buf[content_pos++] = '0';
  for (int i = 0; i < num_len; i++) content_buf[content_pos++] = num_buf[i];
  s21_handle_padding(out, width, total_len, minus, (precision >= 0 ? 0 : zero),
                     precision, content_buf, content_pos);
}

unsigned long long s21_fetch_unsigned(va_list* args, int len_h, int len_l) {
  unsigned long long value = 0;
  if (len_l == 2)
    value = va_arg(*args, unsigned long long);
  else if (len_l == 1)
    value = va_arg(*args, unsigned long);
  else if (len_h == 2)
    value = (unsigned char)va_arg(*args, unsigned int);
  else if (len_h == 1)
    value = (unsigned short)va_arg(*args, unsigned int);
  else
    value = va_arg(*args, unsigned int);
  return value;
}

void s21_handle_hex(char** out, va_list* args, int width, int precision,
                    int minus, int hash, int zero, int uppercase, int len_h,
                    int len_l) {
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  unsigned long long value = s21_fetch_unsigned(args, len_h, len_l);
  char num_buf[65];
  int num_len = s21_uint_to_base(value, num_buf, 16, uppercase);
  int prefix_len = 0;
  if (hash && value != 0) prefix_len = 2;
  int zeros_needed = 0;
  if (precision > num_len) zeros_needed = precision - num_len;
  int total_len = num_len + zeros_needed + prefix_len;
  char content_buf[128];
  int content_pos = 0;
  if (prefix_len) {
    content_buf[content_pos++] = '0';
    content_buf[content_pos++] = uppercase ? 'X' : 'x';
  }
  for (int i = 0; i < zeros_needed; i++) content_buf[content_pos++] = '0';
  for (int i = 0; i < num_len; i++) content_buf[content_pos++] = num_buf[i];
  s21_handle_padding(out, width, total_len, minus, zero, precision, content_buf,
                     content_pos);
}

void s21_handle_octal(char** out, va_list* args, int width, int precision,
                      int minus, int hash, int zero, int len_h, int len_l) {
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  unsigned long long value = s21_fetch_unsigned(args, len_h, len_l);
  char num_buf[65];
  int num_len = s21_uint_to_base(value, num_buf, 8, 0);
  int prefix_len = 0;
  if (hash && value != 0) prefix_len = 1;
  int zeros_needed = 0;
  if (precision > num_len) zeros_needed = precision - num_len;
  int total_len = num_len + zeros_needed + prefix_len;
  char content_buf[128];
  int content_pos = 0;
  if (prefix_len) content_buf[content_pos++] = '0';
  for (int i = 0; i < zeros_needed; i++) content_buf[content_pos++] = '0';
  for (int i = 0; i < num_len; i++) content_buf[content_pos++] = num_buf[i];
  s21_handle_padding(out, width, total_len, minus, zero, precision, content_buf,
                     content_pos);
}

void s21_handle_pointer(char** out, va_list* args, int width, int minus,
                        int zero) {
  if (width < 0) {
    minus = 1;
    width = -width;
  }
  void* ptr = va_arg(*args, void*);
  unsigned long long value = (unsigned long long)(uintptr_t)ptr;
  char num_buf[65];
  int num_len = s21_uint_to_base(value, num_buf, 16, 0);
  int prefix_len = 2;
  int total_len = prefix_len + num_len;
  char content_buf[128];
  int content_pos = 0;
  content_buf[content_pos++] = '0';
  content_buf[content_pos++] = 'x';
  for (int i = 0; i < num_len; i++) content_buf[content_pos++] = num_buf[i];
  s21_handle_padding(out, width, total_len, minus, zero, -1, content_buf,
                     content_pos);
}

int s21_float_pack(long double value, int* width, int* minus, char* content_buf,
                   const char* num_buf, int num_len, int plus, int space) {
  int temp = *width;
  if (temp < 0) {
    *minus = 1;
    temp = -temp;
  }
  *width = temp;
  char sign_char = '\0';
  if (value >= 0) {
    if (plus)
      sign_char = '+';
    else if (space)
      sign_char = ' ';
  }
  if (num_len > 0) {
    if (num_buf[0] == '-' || num_buf[0] == 'i' || num_buf[0] == 'n') {
      sign_char = '\0';
    }
  }
  int pos = 0;
  if (sign_char != '\0') {
    content_buf[0] = sign_char;
    pos = 1;
  }
  int i = 0;
  while (i < num_len) {
    content_buf[pos] = num_buf[i];
    pos++;
    i++;
  }
  return pos;
}

void s21_float_general_process(char* buf, int num_len, int precision, int hash,
                               int* out_len) {
  int dot_allowed = (precision >= 0 || precision == -2);
  int do_trim = hash && dot_allowed ? 0 : 1;
  if (do_trim) {
    int pos_e = -1;
    for (int i = 0; i < num_len; i++)
      if (buf[i] == 'e' || buf[i] == 'E') pos_e = i;
    if (pos_e >= 0) {
      int j = pos_e - 1;
      while (j >= 0 && buf[j] == '0') {
        for (int k = j; k < num_len - 1; k++) buf[k] = buf[k + 1];
        num_len--;
        pos_e--;
        j--;
      }
      if (j >= 0 && buf[j] == '.') {
        for (int k = j; k < num_len - 1; k++) buf[k] = buf[k + 1];
        num_len--;
      }
    } else {
      int has_dot = 0;
      for (int i = 0; i < num_len; i++)
        if (buf[i] == '.') has_dot = 1;
      if (has_dot) {
        int end = num_len - 1;
        while (end >= 0 && buf[end] == '0') end--;
        if (end >= 0 && buf[end] == '.') end--;
        num_len = end + 1;
        buf[num_len] = '\0';
      }
    }
  }
  if (hash) {
    int has_dot = 0;
    for (int i = 0; i < num_len; i++)
      if (buf[i] == '.') has_dot = 1;
    if (!has_dot) {
      buf[num_len++] = '.';
      buf[num_len] = '\0';
    }
  }
  *out_len = num_len;
}

void s21_handle_float_fixed(char** out, va_list* args, int width, int precision,
                            int minus, int plus, int space, int zero,
                            int len_L) {
  if (precision == -2) precision = 0;
  if (precision < 0) precision = 6;
  long double value =
      len_L ? va_arg(*args, long double) : va_arg(*args, double);
  char num_buf[256];
  int num_len = s21_double_to_fixed(value, num_buf, precision);
  char content_buf[256];
  int content_pos = s21_float_pack(value, &width, &minus, content_buf, num_buf,
                                   num_len, plus, space);
  int content_len = content_pos;
  int pad_prec = (zero && !minus) ? -1 : precision;
  s21_handle_padding(out, width, content_len, minus, zero, pad_prec,
                     content_buf, content_pos);
}

void s21_handle_float_exp(char** out, va_list* args, int width, int precision,
                          int minus, int plus, int space, int zero,
                          int uppercase, int len_L) {
  if (precision == -2) precision = 0;
  long double value =
      len_L ? va_arg(*args, long double) : va_arg(*args, double);
  char num_buf[256];
  int num_len = s21_double_to_exp(value, num_buf, precision, uppercase);
  char content_buf[256];
  int content_pos = s21_float_pack(value, &width, &minus, content_buf, num_buf,
                                   num_len, plus, space);
  int content_len = content_pos;
  s21_handle_padding(out, width, content_len, minus, zero, precision,
                     content_buf, content_pos);
}

void s21_handle_float_general(char** out, va_list* args, int width,
                              int precision, int minus, int plus, int space,
                              int zero, int uppercase, int len_L, int hash) {
  int effective;
  if (precision == 0)
    effective = 1;
  else if (precision == -2 || precision < 0)
    effective = 6;
  else
    effective = precision;
  long double value =
      len_L ? va_arg(*args, long double) : va_arg(*args, double);
  char num_buf[512];
  int num_len = s21_double_to_general(value, num_buf, effective, uppercase);
  int final_len = 0;
  s21_float_general_process(num_buf, num_len, precision, hash, &final_len);
  char content_buf[512];
  int content_pos = s21_float_pack(value, &width, &minus, content_buf, num_buf,
                                   final_len, plus, space);
  int content_len = content_pos;
  s21_handle_padding(out, width, content_len, minus, zero, -1, content_buf,
                     content_pos);
}

void s21_handle_n(va_list* args, int count) {
  int* ptr = va_arg(*args, int*);
  *ptr = count;
}

void s21_dispatch_specifier(char** out, char* start, char spec, va_list* args,
                            int minus, int plus, int space, int hash, int zero,
                            int width, int precision, int len_h, int len_l,
                            int len_L) {
  if (spec == 'c') {
    s21_handle_char(out, args, width, minus);
  } else if (spec == 's') {
    s21_handle_string(out, args, width, precision, minus);
  } else if (spec == 'd' || spec == 'i') {
    s21_handle_signed(out, args, width, precision, minus, plus, space, zero,
                      len_h, len_l);
  } else if (spec == 'u') {
    s21_handle_unsigned(out, args, width, precision, minus, zero, len_h, len_l);
  } else if (spec == 'x' || spec == 'X') {
    s21_handle_hex(out, args, width, precision, minus, hash, zero,
                   (spec == 'X'), len_h, len_l);
  } else if (spec == 'o') {
    s21_handle_octal(out, args, width, precision, minus, hash, zero, len_h,
                     len_l);
  } else if (spec == 'p') {
    s21_handle_pointer(out, args, width, minus, zero);
  } else if (spec == 'f') {
    s21_handle_float_fixed(out, args, width, precision, minus, plus, space,
                           zero, len_L);
  } else if (spec == 'e' || spec == 'E') {
    s21_handle_float_exp(out, args, width, precision, minus, plus, space, zero,
                         (spec == 'E'), len_L);
  } else if (spec == 'g' || spec == 'G') {
    s21_handle_float_general(out, args, width, precision, minus, plus, space,
                             zero, (spec == 'G'), len_L, hash);
  } else if (spec == 'n') {
    s21_handle_n(args, (int)(*out - start));
  } else if (spec == '%') {
    char content_buf[2];
    content_buf[0] = '%';
    int content_len = 1;
    s21_handle_padding(out, width, content_len, minus, zero, precision,
                       content_buf, content_len);
  } else {
    *(*out)++ = '%';
    *(*out)++ = spec;
  }
}

int s21_sprintf(char* str, const char* format, ...) {
  int result;
  if (!str || !format) {
    result = -1;
  } else {
    va_list args;
    va_start(args, format);
    char* out = str;
    while (*format) {
      if (*format != '%') {
        *out++ = *format++;
      } else {
        format++;
        int minus = 0, plus = 0, space = 0, hash = 0, zero = 0;
        int width = 0, precision = -1, len_h = 0, len_l = 0, len_L = 0;
        s21_parse_flags(&format, &minus, &plus, &space, &hash, &zero);
        s21_parse_width(&format, &args, &width);
        s21_parse_precision(&format, &args, &precision);
        s21_parse_length(&format, &len_h, &len_l, &len_L);
        char spec = *format ? *format++ : '\0';
        s21_dispatch_specifier(&out, str, spec, &args, minus, plus, space, hash,
                               zero, width, precision, len_h, len_l, len_L);
      }
    }
    *out = '\0';
    va_end(args);
    result = (int)(out - str);
  }
  return result;
}
