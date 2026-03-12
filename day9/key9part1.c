/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>
#define NMAX 10

int input(int *buffer, int length);
void output(const int *buffer, int length);
int sum_numbers(const int *buffer, int length);
int find_numbers(const int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n, data[NMAX + 1] = {1};
    double x;
    if (scanf("%lf", &x) == 1 && ((int)x == x) && x > 0 && x <= NMAX) {
        n = (int)x;
    } else {
        printf("n/a");
        return 0;
    }
    int flag = input(data, n);

    if (flag == 1) {
        int s = sum_numbers(data, n);
        printf("%d\n", s);
        int ans[NMAX];
        int lenght_ans = find_numbers(data, n, s, ans);
        output(ans, lenght_ans);
    }
    return 0;
}

int input(int *a, int n) {
    int fl = 1;
    for (int p = 0; p < n; p++) {
        double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x)) {
            *(a + p) = x;
        } else {
            printf("n/a");
            fl = 0;
            break;
        }
    }
    return fl;
}

void output(const int *a, int n) {
    for (int p = 0; p < n - 1; p++) {
        printf("%d ", *(a + p));
    }
    printf("%d", *(a + n - 1));
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(const int *buffer, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        if (buffer[i] % 2 == 0) {
            sum += buffer[i];
        }
    }
    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(const int *a, int length, int number, int *numbers) {
    int l = 0;
    for (int i = 0; i < length; i++) {
        if ((a[i] != 0) && number % a[i] == 0) {
            numbers[l] = a[i];
            l++;
        }
    }

    return l;
}
