#include "s21_string.h"

int s21_strlen(char *str) {
    int s = 0;
    const char *buf = str;
    while (*buf++) s++;

    return s;
}

int s21_strcmp(char *str1, char *str2) {
    int s = 0;
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; ++i)
        if (str1[i] < str2[i]) {
            s -= str2[i] - str1[i];
            break;
        }

        else if (str1[i] > str2[i]) {
            s += str1[i] - str2[i];
            break;
        }
    return s;
}
