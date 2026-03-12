#include "s21_string.h"

void* s21_memchr(const void* str, int c, s21_size_t n) {
  char* result = S21_NULL;

  s21_size_t i = 0;
  while (i < n && !result) {
    if (((const char*)str)[i] == (char)c) {
      result = (char*)str + i;
    }
    i++;
  }

  return result;
}

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  const unsigned char* str_tmp1 = (const unsigned char*)str1;
  const unsigned char* str_tmp2 = (const unsigned char*)str2;
  int result = 0;

  for (s21_size_t i = 0; i < n && result == 0; i++) {
    if (str_tmp1[i] != str_tmp2[i]) {
      result = str_tmp1[i] - str_tmp2[i];
    }
  }

  return result;
}

void* s21_memcpy(void* dest, const void* src, s21_size_t n) {
  if (dest > src && (char*)dest < (char*)src + n) {
    for (s21_size_t i = n; i > 0; --i) {
      ((char*)dest)[i - 1] = ((char*)src)[i - 1];
    }
  } else {
    for (s21_size_t i = 0; i < n; ++i) {
      ((char*)dest)[i] = ((char*)src)[i];
    }
  }

  return dest;
}

void* s21_memset(void* str, int c, s21_size_t n) {
  for (s21_size_t i = 0; i < n; ++i) {
    ((char*)str)[i] = (char)c;
  }
  return str;
}

char* s21_strncat(char* dest, const char* src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i = 0;

  while (i < n && src[i]) {
    dest[dest_len + i] = src[i];
    i++;
  }

  dest[dest_len + i] = '\0';

  return dest;
}

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;
  s21_size_t i = 0;
  int done = 0;

  while (!done && str[i] != '\0') {
    if (str[i] == (char)c) {
      result = (char*)&str[i];
      done = 1;
    } else {
      i++;
    }
  }

  if (!done && (char)c == '\0' && str[i] == '\0') {
    result = (char*)&str[i];
  }

  return result;
}

int s21_strncmp(const char* str1, const char* str2, s21_size_t n) {
  const unsigned char* s1 = (const unsigned char*)str1;
  const unsigned char* s2 = (const unsigned char*)str2;

  int result = 0;
  s21_size_t i = 0;

  while (i < n && result == 0) {
    if (s1[i] != s2[i]) {
      result = s1[i] - s2[i];
    } else if (s1[i] == '\0') {
      result = 0;
    } else {
      i++;
    }

    if (result == 0 && s1[i] == '\0' && s2[i] == '\0') i = n;
  }

  return result;
}

char* s21_strncpy(char* dest, const char* src, s21_size_t n) {
  s21_size_t i = 0;

  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }

  while (i < n) {
    dest[i] = '\0';
    i++;
  }

  return dest;
}

s21_size_t s21_strcspn(const char* str1, const char* str2) {
  s21_size_t result = s21_strlen(str1);
  int match = 0;

  for (s21_size_t i = 0; str1[i] != '\0' && !match; i++) {
    for (s21_size_t j = 0; str2[j] != '\0' && !match; j++) {
      if (str1[i] == str2[j]) {
        result = i;
        match = 1;
      }
    }
  }

  return result;
}

char* s21_strerror(int errnum) {
  static const char* strerr[] = ERR_MSGS;

#ifdef __APPLE__
#define ERR_MIN 1
#define ERR_MAX ERR_MSGS_COUNT
#else
#define ERR_MIN 0
#define ERR_MAX (ERR_MSGS_COUNT - 1)
#endif

  if (errnum >= ERR_MIN && errnum <= ERR_MAX) {
#ifdef __APPLE__
    return (char*)(strerr[errnum - 1]);
#else
    return (char*)(strerr[errnum]);
#endif
  }

  static char unknown_buf[64];
#ifdef __MUSL__
  s21_sprintf(unknown_buf, "No error information");
#elif __APPLE__
  const char* prefix = (errnum == 0) ? "Undefined error: " : "Unknown error: ";
  s21_sprintf(unknown_buf, "%s%d", prefix, errnum);
#else
  s21_sprintf(unknown_buf, "Unknown error %d", errnum);
#endif

  return unknown_buf;
}

s21_size_t s21_strlen(const char* str) {
  s21_size_t result = 0;

  while (str[result] != '\0') {
    result++;
  }

  return result;
}

char* s21_strrchr(const char* str, int c) {
  char* result = S21_NULL;
  int done = 0;
  int i = 0;

  while (!done) {
    if (str[i] == '\0') {
      if ((char)c == '\0') {
        result = (char*)&str[i];
      }
      done = 1;
    } else if (str[i] == (char)c) {
      result = (char*)&str[i];
    }

    i++;
  }

  return result;
}

char* s21_strpbrk(const char* str1, const char* str2) {
  char* result = S21_NULL;
  int match = 0;

  for (s21_size_t i = 0; str1[i] != '\0' && !match; i++) {
    for (s21_size_t j = 0; str2[j] != '\0' && !match; j++) {
      if (str1[i] == str2[j]) {
        result = (char*)&str1[i];
        match = 1;
      }
    }
  }

  return result;
}

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;
  int match = 0;

  if (needle[0] == '\0') {
    result = (char*)haystack;
    match = 1;
  }

  for (s21_size_t i = 0; haystack[i] != '\0' && !match; i++) {
    int found = 1;

    for (s21_size_t j = 0; needle[j] != '\0' && found; j++) {
      if (haystack[i + j] != needle[j]) {
        found = 0;
      }
    }

    if (found) {
      result = (char*)&haystack[i];
      match = 1;
    }
  }

  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* last_state = S21_NULL;
  char* result = S21_NULL;

  if (str == S21_NULL) {
    str = last_state;
  }

  if (str != S21_NULL) {
    while (*str && s21_strchr(delim, *str)) {
      str++;
    }

    if (*str != '\0') {
      result = str;

      while (*str && !s21_strchr(delim, *str)) {
        str++;
      }

      if (*str != '\0') {
        *str = '\0';
        last_state = str + 1;
      } else {
        last_state = S21_NULL;
      }
    } else {
      last_state = S21_NULL;
    }
  }

  return result;
}
