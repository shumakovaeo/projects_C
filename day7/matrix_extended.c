#include <stdio.h>
#include <stdlib.h>
#define X 100

int input(int M, int N, int (*a)[N]);
int input_size(int *a); //ввод одномерн массива размеров
void output(int m, int n, const int (*a)[n]);
int input2(int **a, int m, int n);
void output2(int **a, int m, int n);
void max_str(int *res, int m, int n, const int (*a)[n]);
void min_stl(int *res, int m, int n, const int (*a)[n]);
void max_str2(int *res, int m, int n,  int **a);
void min_stl2(int *res, int m, int n,  int **a);
void output1(const int *a, int n);//вывод одномерн массива
void quest(int m, int n, int **a);

int main() {    
    int t_mem = 0, flag = 0, n=0; //введем режим выделения памяти
    double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x) && x >= 1 && x <= 4) {
        t_mem = x;
    } else {
        printf("n/a");
        t_mem = 0;
    }    
    if (t_mem>=1) {
        int flag_r=0, mn[2];
        flag_r=input_size(mn);
        const int M=mn[0], N=mn[1];
        if (flag_r == 1)
        switch (t_mem)
        {
        case 1:
            {
            if (M <= X && N <= X){
            int data[M][N];
            flag = input(M, N, data);
            if (flag == 1) {output( M, N, data);
                printf("\n");
            int res1[M], res2[N];
            max_str(res1, M, N, data);
            output1(res1, M);
            printf("\n");
            min_stl(res2, M, N, data);
            output1(res2, N);
        }}
            else
               printf("n/a");            
        }
            break;
       case 2: //single array matrix
            {
            int **data = malloc(M*N*sizeof(int) + M*sizeof(int*));
            int *ptr = (int*) (data+M);
            for (int i = 0; i < M; i++) data[i]=ptr+i*N;
            quest(M, N, data);
            free(data);
        }
            break; 
        case 3: //pointers to arrays 
            {
            int **data = malloc(M*sizeof(int*));
            for (int i = 0; i < M; i++) data[i]= malloc(N*sizeof(int));
            quest(M, N, data);
            for (int i = 0; i < M; i++) free(data[i]);
        }
            break;
        case 4: //pointers to segm. 2 array 
            {
            int **pointer_data = malloc(M*sizeof(int*));
            int *data = malloc(M*N*sizeof(int));
            for (int i = 0; i < M; i++) pointer_data[i]= data + N*i;
            quest(M, N, pointer_data);
            free(data);
            free(pointer_data);
        }
            break;   
    }}
    return 0;
}
int input_size(int *a) {
    int fl = 1;
        double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x) && x > 0) {
            a[0] = x;
            if (scanf("%lf", &x) == 1 && ((int)x == x) && x > 0) 
                 a[1] = x;
            else {
            fl = 0;
            printf("n/a");
             } }
        else {
            fl = 0;
            printf("n/a");
        }    
    return fl;
}
int input(int M, int N, int (*a)[N]) {
    int fl = 1;
    for (int p = 0; p < M; p++)
        for (int q = 0; q < N; q++) {
        double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x)) {
            a[p][q] = (int) x;            
        } else {
            fl = 0;
            printf("n/a");
            break;
        }
    }
    return fl;
}

void output(int m, int n, const int (*a)[n]) {
     for (int p = 0; p < m-1; p++) {
        for (int q = 0; q < n-1; q++)
        printf("%d ", a[p][q]);
        printf("%d\n", a[p][n-1]);
        }    
    for (int q = 0; q < n-1; q++)
        printf("%d ", a[m-1][q]);
    printf("%d", a[m-1][n-1]);
}

int input2(int **a, int M, int N){
    int fl = 1;    
    for (int p = 0; p < M; p++){ 
        for (int q = 0; q < N; q++){
        double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x)) 
            a[p][q] = (int) x;
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

void output2(int **a, int M, int N){

for (int p = 0; p < M-1; p++) {
        for (int q = 0; q < N-1; q++)
        printf("%d ", a[p][q]);
        printf("%d\n", a[p][N-1]);
    }    
    for (int q = 0; q < N-1; q++)
        printf("%d ", a[M-1][q]);
    printf("%d", a[M-1][N-1]);
}

void max_str(int *res, int m, int n, const int (*a)[n]){
for (int p = 0; p < m; p++) {
        res[p] = a[p][0];
        for (int q = 1; q < n; q++)
        if (a[p][q] > res[p]) res[p] =  a[p][q]; 
}
}

void max_str2(int *res, int m, int n, int **a){
for (int p = 0; p < m; p++) {
        res[p] = a[p][0];
        for (int q = 1; q < n; q++)
        if (a[p][q] > res[p]) res[p] =  a[p][q]; 
}
}
void min_stl(int *res, int m, int n, const int (*a)[n]){
for (int q = 0; q < n; q++) {
        res[q] = a[0][q];
        for (int p = 1; p < m; p++)
        if (a[p][q] < res[q]) res[q] =  a[p][q]; 
}
}
void min_stl2(int *res, int m, int n, int **a){
for (int q = 0; q < n; q++) {
        res[q] = a[0][q];
        for (int p = 1; p < m; p++)
        if (a[p][q] < res[q]) res[q] =  a[p][q]; 
}
}
void output1(const int *a, int n) {
    for (int p = 0; p < n-1; p++) {
        printf("%d ", *(a + p));
    }
    printf("%d", *(a + n-1));
}

void quest(int m, int n, int **a){
    int flag = 0;
    flag = input2(a, m, n);
    if (flag == 1) {output2(a, m, n);
                printf("\n");
            int res1[m], res2[n];
            max_str2(res1, m, n, a);
            output1(res1, m);
            printf("\n");
            min_stl2(res2, m, n, a);
            output1(res2, n);}
}