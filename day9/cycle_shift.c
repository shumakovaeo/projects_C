
#include <stdio.h>
#define NMAX 10

int input(int *buffer, int length);
void output(const int *buffer, int length);
void shift(int *buffer, int length, int lenght_shift);

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
        if (scanf("%lf", &x) == 1 && ((int)x == x) && (x <= n) && (x >= -n)) {
            int lenght_shift = (int)x;
            shift(data, n, lenght_shift);
            output(data, n);
        } else
            printf("n/a");
    } else
        printf("n/a");

    return 0;
}

int input(int *a, int n) {
    int fl = 1;
    for (int p = 0; p < n; p++) {
        double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x)) {
            *(a + p) = x;
        } else {
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

void shift(int *buffer, int lenght, int lenght_shift) {
    if (lenght_shift > 0) {
        int temp[lenght_shift];
        for (int i = 0; i < lenght_shift; i++) {
            temp[i] = buffer[i];
        }
        for (int i = lenght_shift; i < lenght; i++) {
            buffer[i - lenght_shift] = buffer[i];
        }
        for (int i = lenght - lenght_shift; i < lenght; i++) {
            buffer[i] = temp[i - lenght + lenght_shift];
        }
    }

    if (lenght_shift < 0) {
        int l = -lenght_shift;
        int temp[l];
        for (int i = lenght - l; i < lenght; i++) {
            temp[i - lenght + l] = buffer[i];
        }
        for (int i = lenght - l - 1; i >= 0; i--) {
            buffer[i + l] = buffer[i];
        }
        for (int i = 0; i < l; i++) {
            buffer[i] = temp[i];
        }
    }
}
