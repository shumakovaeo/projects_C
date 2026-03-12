#include <stdio.h>
#include <stdlib.h>


int input(int *a, int n);
void output(const int *a, int n);
void sort_v(int *a, int n);

int main() {
    double x;
    int n = 0;
    if (scanf("%lf", &x) == 1 && ((int)x == x) && x > 0) {
        n = (int)x;
    } else {
        printf("n/a");
        n = 0;
    }
    if (n >= 1) {
        int *data = malloc(n);
        int flag = input(data, n);
        if (flag == 1) {
        sort_v(data, n);
        output(data, n);
        }
         free(data);
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
            fl = 0;
            printf("n/a");
            break;
        }
    }
    return fl;
}

void output(const int *a, int n) {
    for (int p = 0; p < n-1; p++) {
        printf("%d ", *(a + p));
    }
    printf("%d", *(a + n-1));
}

void sort_v(int *a, int n) {
    //  int el, ind;
    for (int p = 1; p <n; p++) {
        int el = a[p];
        int ind = p - 1;
        while (ind >= 0 && a[ind] > el) {
            a[ind + 1] = a[ind];
            ind--;
        }
        a[ind + 1] = el;
    }
}
