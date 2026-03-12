#include <stdio.h>
#include <stdlib.h>
#define X 100

int input(int m, int n, int (*a)[n]);
int input_size(int *a);
void output(int m, int n, const int (*a)[n]);
int input2(int **a, int m, int n);
void output2(int **a, int m, int n);

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
            if (flag == 1) output(M, N, data);}
            else
               printf("n/a");
            }
            break;
       case 2: //single array matrix
            {
            int **data = malloc(M*N*sizeof(int) + M*sizeof(int*));
            int *ptr = (int*) (data+M);
            for (int i = 0; i < M; i++) data[i]=ptr+i*N;
            flag = input2(data, M, N);
            if (flag == 1) output2(data, M, N);
            free(data);
        }
            break; 
        case 3: //pointers to arrays 
            {
            int **data = malloc(M*sizeof(int*));
            for (int i = 0; i < M; i++) data[i]= malloc(N*sizeof(int));
            flag = input2(data, M, N);
            if (flag == 1) output2(data, M, N);
            for (int i = 0; i < M; i++) free(data[i]);
        }
            break;
        case 4: //pointers to segm. 2 array 
            {
            int **pointer_data = malloc(M*sizeof(int*));
            int *data = malloc(M*N*sizeof(int));
            for (int i = 0; i < M; i++) pointer_data[i]= data + N*i;
            flag = input2(pointer_data, M, N);
            if (flag == 1) output2(pointer_data, M, N);
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
