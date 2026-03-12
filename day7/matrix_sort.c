#include <stdio.h>
#include <stdlib.h>

int input_size(int *a); //ввод одномерн массива размеров
int input2(int **a, int m, int n);
void output2(int **a, int m, int n);
void sum_str2(int *res, int m, int n,  int **a);

void quest(int m, int n, int **a);

int main() {    
    int t_mem = 0, flag = 0, n=0; //введем режим выделения памяти
    double x;
        if (scanf("%lf", &x) == 1 && ((int)x == x) && x >= 1 && x <= 3) {
        t_mem = x;
    } else {
        printf("n/a");
        t_mem = 0;
    }    
    if (t_mem>=1) {
        int flag_r=0, mn[2];
        flag_r=input_size(mn);
        const int M=mn[0], N=mn[1]+1;
        if (flag_r == 1)
        switch (t_mem)
        {
        case 1: //single array matrix
            {
            int **data = malloc(M*N*sizeof(int) + M*sizeof(int*));
            int *ptr = (int*) (data+M);
            for (int i = 0; i < M; i++) data[i]=ptr+i*N;
            quest(M, N, data);
            free(data);
        }
            break; 
        case 2: //pointers to arrays 
            {
            int **data = malloc(M*sizeof(int*));
            for (int i = 0; i < M; i++) data[i]= malloc(N*sizeof(int));
            quest(M, N, data);
            for (int i = 0; i < M; i++) free(data[i]);
        }
            break;
        case 3: //pointers to segm. 2 array 
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

int input2(int **a, int M, int N){
    int fl = 1;    
    for (int p = 0; p < M; p++){ 
        for (int q = 0; q < N-1; q++){
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

void sum_str2(int *res, int m, int n, int **a){
for (int p = 0; p < m; p++) {
        res[p] = a[p][0];
        for (int q = 1; q < n-1; q++)
        res[p] +=  a[p][q]; 
        a[p][n-1] = res[p];
}
}
void sort_v(int m, int n, int **a) {
    //  int el, ind;
    for (int p = 1; p <m; p++) {
        int el[n]; 
       for (int j = 0; j <n; j++) el[j]= a[p][j];
        int ind = p - 1;
        while (ind >= 0 && a[ind][n-1] > el[n-1]) {
            for (int j = 0; j <n; j++) {
                a[ind + 1][j] = a[ind][j];
            }
            ind--;
        }
        for (int j = 0; j <n; j++) a[ind + 1][j] = el[j];
    }
}
void quest(int m, int n, int **a){
    int flag = 0;
    flag = input2(a, m, n);
    if (flag == 1) {
            int res1[m];
            sum_str2(res1, m, n, a);
            
            sort_v(m, n, a);
            output2(a, m, n-1);
            }
}