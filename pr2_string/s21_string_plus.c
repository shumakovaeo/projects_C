
#include "s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size_t start_index) {
  void* result = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    if (start_index <= src_len) {
      s21_size_t new_len = src_len + str_len;
      char* buf = (char*)malloc(new_len + 1);
      if (buf != S21_NULL) {
        s21_memcpy(buf, src, start_index);
        s21_memcpy(buf + start_index, str, str_len);
        s21_memcpy(buf + start_index + str_len, src + start_index,
                   src_len - start_index);
        buf[new_len] = '\0';
        result = buf;
      }
    }
  }
  return result;
}

void* s21_to_lower(const char* str) {
  void* result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    char* buf = (char*)malloc(len + 1);
    if (buf != S21_NULL) {
      s21_size_t i = 0;
      for (; i < len; i++) {
        char ch = str[i];
        buf[i] = (ch >= 'A' && ch <= 'Z') ? ch + 0x20 : ch;
      }
      buf[len] = '\0';
      result = buf;
    }
  }
  return result;
}

void* s21_to_upper(const char* str) {
  void* result = S21_NULL;
  if (str != S21_NULL) {
    s21_size_t len = s21_strlen(str);
    char* buf = (char*)malloc(len + 1);
    if (buf != S21_NULL) {
      s21_size_t i = 0;
      for (; i < len; i++) {
        char ch = str[i];
        buf[i] = (ch >= 'a' && ch <= 'z') ? ch - 0x20 : ch;
      }
      buf[len] = '\0';
      result = buf;
    }
  }
  return result;
}

void* s21_trim(const char* src, const char* trim_chars) {
  void* result = S21_NULL;
  if (src != S21_NULL) {
    const char* trim_local = (trim_chars != S21_NULL) ? trim_chars : "";
    s21_size_t src_len = s21_strlen(src);
    s21_size_t start = 0;
    while (start < src_len && s21_strchr(trim_local, src[start]) != S21_NULL) {
      start++;
    }
    s21_size_t end = src_len;
    while (end > start && s21_strchr(trim_local, src[end - 1]) != S21_NULL) {
      end--;
    }
    s21_size_t new_len = end - start;
    char* buf = (char*)malloc(new_len + 1);
    if (buf != S21_NULL) {
      s21_memcpy(buf, src + start, new_len);
      buf[new_len] = '\0';
      result = buf;
    }
  }
  return result;
}
