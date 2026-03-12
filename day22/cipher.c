#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int(n);
    printf("выбор пункта меню 1 выход -1\n");
    scanf("%d", &n);  // считали пункт меню

    char str[100];
    while (n == 1) {
        scanf("%99s", str);  // считали строку названия файла
        char str_fold[100] = "../datasets/";
        int max_add = sizeof(str) - strlen(str) - 1;
        strncat(str_fold, str, max_add);
        str[sizeof(str_fold) - 1] = '\0';
        char t[100];
        FILE* f = fopen(str_fold, "r");  // открыли файл
        if (f == NULL) {
            printf("n/a\n");
        } else {
            char* fl = fgets(t, sizeof(t), f);
            if (fl == NULL) {
                printf("n/a\n");
            }
            while (fl) {  // считали строку файла
                {
                    char* ptr = strchr(t, '\n');
                    if (ptr != NULL) {
                        *ptr = '\0';
                        for (int i = 0; t[i] != '\\' && t[i] != '\0'; i++) printf("%c", t[i]);
                        printf("\n");
                    }
                }
            }
            fclose(f);
        }

        scanf("%d", &n);  // считали пункт меню
    }

    return 0;
}
