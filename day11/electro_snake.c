#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
void sort_horizontal(int **matrix, int n, int m, int **result_matrix);


int input(int **matrix, int n, int m);
void output(int **matrix, int n, int m);


int main(){
    int n=0, m=0, fl = 1;
    double x;
    if (scanf("%lf", &x) == 1 && ((int)x == x) && x > 0) {
        n = x;
        if (scanf("%lf", &x) == 1 && ((int)x == x) && x > 0)
            m = x;
        else {
            fl = 0;
            printf("n/a");
        }
    } else {
        fl = 0;
        printf("n/a");
    }
    if (fl == 1 && n>0) {
        int **matrix = malloc(n * sizeof(int *));
          for (int i = 0; i < n; i++) matrix[i] = malloc(m * sizeof(int));
         int fl2 = input(matrix, n, m);
          if (fl2 ==1)

        if (fl2 ==1) {
             int **result = malloc(n * sizeof(int *));
             for (int i = 0; i < n; i++) result[i] = malloc(m * sizeof(int));
             sort_vertical(matrix, n, m, result);
             output(result, n, m);
    
            // sort_horizontal(matrix, n, m, result);
             //output(result n, m);
           for (int i = 0; i < n; i++) free(result[i]);
        }
        for (int i = 0; i < n; i++) free(matrix[i]);
        free(matrix);
    }
    return 0;
}

int input(int **a, int n, int m) {
    int fl = 1;
    for (int p = 0; p < n; p++) {
        for (int q = 0; q < m; q++) {
            double x;
            if (scanf("%lf", &x) == 1 && ((int)x == x))
                a[p][q] = (int)x;
            else {
                fl = 0;
                printf("n/a");
                break;
            }
        }
        if (fl == 0) break;
    }
    return fl;
}

void output(int **a, int n, int m) {
    for (int p = 0; p < n - 1; p++) {
        for (int q = 0; q < m - 1; q++) printf("%d ", a[p][q]);
        printf("%d\n", a[p][m - 1]);
    }
    for (int q = 0; q < m - 1; q++) printf("%d ", a[n - 1][q]);
    printf("%d", a[n - 1][m - 1]);
}

void sort_vertical(int **matrix, int n, int m, int **result_matrix){
    for (int p = 0; p < n;  p++) {
        for (int q = 0; q < m; q++)
            if (p%2 == 0) result_matrix[p][q] = matrix[q][p];
            else result_matrix[p][q] = matrix[m-1-q][p];

    }

}
