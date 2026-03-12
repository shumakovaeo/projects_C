#include "s21_sscanf.h"

long long parse_signed_number(const char** str, int width, int* ptr_flag) {
  const char* s = *str;
  int sign = 1, flag = 1, flag_val = 0;
  if (*s == '-' || *s == '+') {
    sign = (*s == '-') ? -1 : 1;
    s++;
    if (width > 0) width--;
  }
  int base = 10;
  if (*s == '0') {
    if (*(s + 1) == 'x' || *(s + 1) == 'X') {
      base = 16;
      s += 2;
      if (width >= 2) width -= 2;
    } else if (*(s + 1) >= '0' && *(s + 1) <= '7') {
      base = 8;
      s++;
      if (width > 0) width--;
    }
  }
  unsigned long long val = 0;
  while (*s && flag) {
    int digit = -2;
    if (*s >= '0' && *s <= '9')
      digit = *s - '0';
    else if (*s >= 'a' && *s <= 'f' && base == 16)
      digit = *s - 'a' + 10;
    else if (*s >= 'A' && *s <= 'F' && base == 16)
      digit = *s - 'A' + 10;
    else
      flag = 0;
    if (flag && (digit >= base || (width == 0))) flag = 0;
    if (flag) {
      val = val * base + digit;
      flag_val = 1;
      s++;
      if (width > 0) width--;
    }
    if (flag_val == 0) *ptr_flag = 0;
  }
  *str = s;
  return (sign < 0) ? -(long long)val : (long long)val;
}

unsigned long long parse_unsigned_number(const char** str, int base, int width,
                                         int* ptr_flag) {
  const char* s = *str;
  unsigned long long val = 0;
  int flag = 1, flag_val = 0;
  if (base == 16 && ((*s == '0') && (*(s + 1) == 'x' || *(s + 1) == 'X'))) {
    s += 2;
  }
  while (*s && flag) {
    int digit = -2;
    if (*s >= '0' && *s <= '9')
      digit = *s - '0';
    else if (*s >= 'a' && *s <= 'f' && base == 16)
      digit = *s - 'a' + 10;
    else if (*s >= 'A' && *s <= 'F' && base == 16)
      digit = *s - 'A' + 10;
    else
      flag = 0;
    if (flag && (digit >= base || (width == 0))) flag = 0;
    if (flag) {
      val = val * base + digit;
      flag_val = 1;
      s++;
      if (width > 0) width--;
    }
    if (flag_val == 0) *ptr_flag = 0;
  }
  *str = s;
  return val;
}

double parse_float_number(const char** str, int width, int* flag) {
  const char* s = *str;
  double val = 0.0, sign = 1.0;
  *flag = 0;
  if (*s == '-' || *s == '+') {
    sign = (*s == '-') ? -1.0 : 1.0;
    s++;
    if (width > 0) width--;
  }
  while (*s >= '0' && *s <= '9' && width != 0) {
    val = val * 10.0 + (*s - '0');
    s++;
    *flag = 1;
    if (width > 0) width--;
  }
  if (*s == '.' && width != 0) {
    s++;
    if (width > 0) width--;
    double frac = 0.0, place = 0.1;
    while (*s >= '0' && *s <= '9' && width != 0) {
      frac += (*s - '0') * place;
      place *= 0.1;
      s++;
      if (width > 0) width--;
    }
    val += frac;
  }
  if ((*s == 'e' || *s == 'E') && width != 0) {
    s++;
    if (width > 0) width--;
    int exp_sign = 1;
    if (*s == '-' || *s == '+') {
      exp_sign = (*s == '-') ? -1 : 1;
      s++;
      if (width > 0) width--;
    }
    int exp_val = 0;
    while (*s >= '0' && *s <= '9' && width != 0) {
      exp_val = exp_val * 10 + (*s - '0');
      s++;
      if (width > 0) width--;
    }
    for (int i = 0; i < exp_val; i++)
      val = (exp_sign > 0) ? val * 10.0 : val / 10.0;
  }
  *str = s;
  return val * sign;
}

char* parse_word(const char** str, int width) {
  const char* start = *str;
  int len = 0;
  while (**str && **str != ' ' && (width <= 0 || len < width)) {
    (*str)++;
    len++;
  }
  char* buf = (char*)calloc(len + 1, sizeof(char));
  if (buf) {
    s21_strncpy(buf, start, len);
    buf[len] = '\0';
  }
  return buf;
}
int specifiers_numb(const char** src, const char* format, va_list* args,
                    int width, int suppress, int assigned, int len) {
  int flag_read = 1;
  int* ptr_flag = &flag_read;
  if (*format == 'd' || *format == 'i') {
    long long val = parse_signed_number(src, width, ptr_flag);
    if (!suppress && flag_read) {
      if (len == 'h')
        *va_arg(*args, short*) = (short)val;
      else if (len == 'l')
        *va_arg(*args, long*) = (long)val;
      else
        *va_arg(*args, int*) = (int)val;
      assigned++;
    }
  } else if (*format == 'u' || *format == 'o' || *format == 'x' ||
             *format == 'X') {
    int base = (*format == 'u') ? 10 : ((*format == 'o') ? 8 : 16);
    unsigned long long val = parse_unsigned_number(src, base, width, ptr_flag);
    if (!suppress && flag_read) {
      if (len == 'h')
        *va_arg(*args, unsigned short*) = (unsigned short)val;
      else if (len == 'l')
        *va_arg(*args, unsigned long*) = (unsigned long)val;
      else
        *va_arg(*args, unsigned int*) = (unsigned int)val;
      assigned++;
    }
  } else if (*format == 'e' || *format == 'E' || *format == 'f' ||
             *format == 'g' || *format == 'G') {
    double val = parse_float_number(src, width, ptr_flag);
    if (!suppress && flag_read) {
      if (len == 'l')
        *va_arg(*args, double*) = (double)val;
      else if (len == 'L')
        *va_arg(*args, long double*) = (long double)val;
      else
        *va_arg(*args, float*) = (float)val;
      assigned++;
    }
  }
  return assigned;
}

int uslov(const char* src, const char* format) {
  int ans =
      ((*format == 'd' &&
        (*src == '+' || *src == '-' || (*src >= '0' && *src <= '9'))) ||
       (*format == 'i' &&
        (*src == '+' || *src == '-' || (*src >= '0' && *src <= '9') ||
         (*src >= 'a' && *src <= 'f') || (*src >= 'A' && *src <= 'F'))) ||
       ((*format == 'u' || *format == 'o' || *format == 'x' ||
         *format == 'X') &&
        ((*src >= '0' && *src <= '9') || (*src >= 'a' && *src <= 'f') ||
         (*src >= 'A' && *src <= 'F'))) ||
       ((*format == 'f' || *format == 'e' || *format == 'E' || *format == 'g' ||
         *format == 'G') &&
        ((*src >= '0' && *src <= '9') || (*src == '+') || (*src == '-'))));
  return ans;
}

int specifiers_char_str(const char** src, const char* format, va_list* args,
                        int width, int suppress, int assigned, int len) {
  if (*format == 'c') {
    if (!suppress) {
      if (len == 'l')
        *va_arg(*args, wchar_t*) = (wchar_t) * *src;
      else
        *va_arg(*args, char*) = **src;
      assigned++;
    }
    *src += 1;
  } else if (*format == 's') {
    char* word = parse_word(src, width);
    if (!suppress && word) {
      if (len == 'l') {
        wchar_t* dest = va_arg(*args, wchar_t*);
        const char* src1 = word;
        s21_size_t i = 0;
        while (src1[i] && i < s21_strlen(word)) {
          dest[i] = (wchar_t)(unsigned char)src1[i];
          i++;
        }
        dest[i] = L'\0';
      } else {
        char* dest = va_arg(*args, char*);
        s21_strncpy(dest, word, s21_strlen(word));
        dest[s21_strlen(word)] = '\0';
      }
      assigned++;
    }
    if (word) free(word);
  }
  return assigned;
}
int w_width(const char** format) {
  int width = -1;
  if (isdigit(**format)) {
    width = 0;
    while (isdigit(**format)) {
      width = width * 10 + (**format - '0');
      *format += 1;
    }
    if (width == 0) width--;
  }
  return width;
}
char l_len(const char** format) {
  char len = 0;
  if (**format == 'h' || **format == 'l' || **format == 'L') {
    len = **format;
    *format += 1;
  }
  return len;
}
int literal(const char** src, const char** format) {
  int flag = 1;
  if (**format == ' ') {
    while (**src == ' ') *src += 1;
  } else {
    if (**src == **format)
      *src += 1;
    else if (**src != '\0')
      flag = 0;
  }
  *format += 1;
  return flag;
}

int s21_sscanf(const char* str, const char* format, ...) {
  int assigned = -1;
  if (str != S21_NULL && format != S21_NULL && s21_strlen(str) != 0) {
    va_list args;
    va_start(args, format);
    int flag = 1;
    const char* src = str;
    assigned = 0;
    while (*format && flag) {
      if (*format == '%') {
        format++;
        int suppress = (*format == '*');
        if (suppress) format++;
        int width = w_width(&format);
        char len = l_len(&format);
        if (*format == 'n' && !suppress) *va_arg(args, int*) = (int)(src - str);
        if (*src != '\0') {
          if (*format != 'c' && *format != 'n')
            while (*src == ' ') src++;
          if (uslov(src, format))
            assigned = specifiers_numb(&src, format, &args, width, suppress,
                                       assigned, len);
          else if (*format == 'c' || *format == 's')
            assigned = specifiers_char_str(&src, format, &args, width, suppress,
                                           assigned, len);
          else if (*format == 'p') {
            int flag_read = 1;
            int* ptr_flag = &flag_read;
            void* val = (void*)parse_unsigned_number(&src, 16, width, ptr_flag);
            if (!suppress) {
              *va_arg(args, void**) = val;
              assigned++;
            }
          } else if (*format == '%' && *src == '%')
            src++;
          else if (*format == '%' && *src != '%')
            flag = 0;
          format++;
        }
      } else
        flag = literal(&src, &format);
    }
    va_end(args);
  }
  return assigned;
}
