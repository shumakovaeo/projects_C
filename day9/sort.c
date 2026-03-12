#include <stdio.h>
#define N 10

void input(int *a);
void output(const int *a);
void sort_v(int *a);

int main() {
    int data[N + 1] = {1};

    input(data);

    if (*data == 1) {
        sort_v(data);
        output(data);
    }
    return 0;
}

void input(int *a) {
    for (int p = 1; p <= N; p++) {
        double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x)) {
            *(a + p) = x;
        } else {
            printf("n/a");
            *a = 0;
            break;
        }
    }
}

void output(const int *a) {
    for (int p = 1; p < N; p++) {
        printf("%d ", *(a + p));
    }
    printf("%d", *(a + N));
}

void sort_v(int *a) {
    //  int el, ind;
    for (int p = 2; p <= N; p++) {
        int el = a[p];
        int ind = p - 1;
        while (ind >= 1 && a[ind] > el) {
            a[ind + 1] = a[ind];
            ind--;
        }
        a[ind + 1] = el;
    }
}
