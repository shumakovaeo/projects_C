#include "s21_string.h"

#include <stdio.h>
#include <string.h>

void s21_strlen_test();
void s21_strcmp_test();

int main() {
    //    s21_strlen_test();
    s21_strcmp_test();

    return 0;
}

void s21_strlen_test() {
    char str[1000] = "I like school 21";
    int l = s21_strlen(str);
    printf("%s\n", str);
    printf("%d\n", l);
    if (l >= 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    l = 0;

    char str1[10] = "";
    l = s21_strlen(str1);
    printf("\n%s\n", str1);
    printf("%d\n", l);
    if (l == 0)
        printf("SUCCESS");
    else
        printf("FAIL");
    l = 0;
    char str2[] = {'a', 'b', '\0', 'c'};
    l = s21_strlen(str2);
    printf("\n%s\n", str2);
    printf("%d\n", l);
    if (l == 4)
        printf("SUCCESS");
    else
        printf("FAIL");

    char str3[] = {'a', 'b', 'c'};

    printf("\n%s\n", str3);
    l = s21_strlen(str3);
    printf("%d\n", l);
    if (l == 3)
        printf("SUCCESS");
    else
        printf("FAIL");
}

void s21_strcmp_test() {
    char str1[1000] = "I like school 21";
    char str2[1000] = "Hello, C";
    int l = s21_strcmp(str1, str2);
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%d\n", l);
    printf("%d\n", strcmp(str1, str2));
    if (l >= 0)
        printf("SUCCESS");
    else
        printf("FAIL");

    char str3[1000] = "I like school 21";
    char str4[1000] = "Желаю удачи в изучении языков";
    l = s21_strcmp(str3, str4);
    printf("%s\n", str3);
    printf("%s\n", str4);
    printf("%d\n", l);
    printf("%d\n", strcmp(str3, str4));
    if (l >= 0)
        printf("SUCCESS");
    else
        printf("FAIL");

    char str5[1000] = "Hello";
    char str6[1000] = "Hello";
    l = s21_strcmp(str5, str6);
    printf("%s\n", str5);
    printf("%s\n", str6);
    printf("%d\n", l);
    printf("%d\n", strcmp(str5, str6));
    if (l >= 0)
        printf("SUCCESS");
    else
        printf("FAIL");
}
