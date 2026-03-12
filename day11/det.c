#include <stdio.h>
#include <stdlib.h>

double det(double **matrix, int n);
void input(double **matrix, int *n, int *m);
void output(double det);

void main(){
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
    if (fl == 1 && n==m && n>0) {
        int **matrix = malloc(n * sizeof(int *));
          for (int i = 0; i < n; i++) matrix[i] = malloc(m * sizeof(int));
         int fl2 = input(matrix, n, m);
          if (fl2 ==1)
          double d  = det(matrix, n);
           output(d);
        for (int i = 0; i < n; i++) free(matrix[i]);
        free(matrix);
    }
    else
        printf("n/a");
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

double det(double **matrix, int n){
    int s=0;
    for (int j = 0; j < m; j++) {
        int **result = malloc((n-1) * sizeof(int *));
            for (int i = 0; i < n; i++) result[i] = malloc(m * sizeof(int));
             double d = det(matrix, n, m, result);

        matrix_mod(matrix, n, m, rezult, q);
        s += a[0][q] *pow((-1), (q)) * det(result, n-1, m-1);
        for (int i = 0; i < n; i++) free(result[i]);
           free(result);
    }
    return s;
}

void matrix_mod(double **a, int n, int m, double **res, int p, int q){
    int k=0, l=0;
    for (int i = 1; i < n; i++)
        for (int j = 0; j < m; j++) {
        if ( j != q) res[k][l] = a[p][q]);
        k
        printf("%d\n", a[p][m - 1]);
    }
}

void output(double det){
    printf("%.6f", det);

}
