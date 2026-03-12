#include <stdio.h>
#define N 10

void input(int *a);
void output(const int *a);
void swap(int *a, int *b);
void quick_sort(int *a, int first, int last);
void piramid_sort(int *a);

int main() {
    int data[N + 1] = {1};

    input(data);

    if (*data == 1) {
        quick_sort(data, 1, N);
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

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int *a, int first, int last) {
    if (first < last) {
        int left = first, right = last, mid = a[(left + right) / 2];
        do {
            while (a[left] < mid) left++;
            while (a[right] > mid) right--;
            if (left <= right) {
                swap(a + left, a + right);

                left++;
                right--;
            }

        } while (left <= right);
        quick_sort(a, first, right);
        quick_sort(a, left, last);
    }
}
