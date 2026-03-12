#include <stdio.h>
#include <stdlib.h>

int input_size(int *a); //ввод одномерн массива размеров
int input(int **a, int m, int n);
void output(int **a, int m, int n);

int sum(int **matrix_first,  int m_first, int n_first, int **matrix_second, 
    int **matrix_result);
int transpose(int **matrix, int m, int n, int **matrix_result, const int m_res, const int n_res);
int mul(int **matrix_first, int m_first, int n_first, int **matrix_second, 
    int n_second, int **matrix_result);

int main()
{int t_mem = 0, flag = 0, n=0; //введем режим действий
    double x;
    if (scanf("%lf", &x) == 1 && ((int)x == x) && x >= 1 && x <= 3) 
        t_mem = x;
    else {
        printf("n/a");
        t_mem = 0;
    }    
    
    if (t_mem == 1) { //сумма
        int flag_r=0, mn[2]; //size 
        flag_r=input_size(mn);
        const int m=mn[0], n=mn[1];
        
        if (flag_r == 1){
            int **data1 = malloc(m*n*sizeof(int) + m*sizeof(int*)); //matr1
            int *ptr = (int*) (data1+m);
            for (int i = 0; i < m; i++) data1[i]=ptr+i*n; 
            int flag1=0;
            flag1 = input(data1, m, n);
            int flag_r=0, mn2[2]; 
            if (flag1 == 1)
                flag_r=input_size(mn2); //size 2
                
            if (flag1 == 1 && flag_r == 1 && m==mn2[0] && n==mn2[1]){                    
                   int **data2 = malloc(m*n*sizeof(int) + m*sizeof(int*)); //matr2
                   int *ptr2 = (int*) (data2+m);
                   for (int i = 0; i < m; i++) data2[i]=ptr2+i*n; 
                   int flag2=0;
                   flag2 = input(data2, m, n);
                       if (flag2 == 1){
                        int **result = malloc(m*n*sizeof(int) + m*sizeof(int*)); //res
                        int *ptr3 = (int*) (result+m);
                       for (int i = 0; i < m; i++) result[i]=ptr3+i*n; 
                        
                        sum(data1, m, n, data2, result);             
                        output(result, m, n);
                        free(result);
                       } 
                   free(data2);
            }
            else printf("n/a");
            free(data1);
        }         
    }
    if (t_mem == 3) { //транспонир 
        int flag_r=0, mn[2]; //size 
        flag_r=input_size(mn);
        const int m=mn[0], n=mn[1];
         if (flag_r == 1){
            int **data = malloc(m*n*sizeof(int) + m*sizeof(int*)); //matr1
            int *ptr = (int*) (data+m);
            for (int i = 0; i < m; i++) data[i]=ptr+i*n; 
            int flag1=0;
            flag1 = input(data, m, n);
            if (flag1 == 1) {
                int **result = malloc(n*m*sizeof(int) + n*sizeof(int*)); //res
                int *ptr3 = (int*) (result+n);
                for (int i = 0; i < n; i++) result[i]=ptr3+i*m;                        
                transpose(data, m, n, result, n, m);             
                output(result, n, m);
                free(result);
            }
            free(data);
        }  
    }     
    if (t_mem == 2) {  //произвед 
        int flag_r=0, mn[2]; //size 
        flag_r=input_size(mn);
        const int m=mn[0], n=mn[1];
        
        if (flag_r == 1){
            int **data1 = malloc(m*n*sizeof(int) + m*sizeof(int*)); //matr1
            int *ptr = (int*) (data1+m);
            for (int i = 0; i < m; i++) data1[i]=ptr+i*n; 
            int flag1=0;
            flag1 = input(data1, m, n);
            int flag_r=0; 
            if (flag1 == 1)
                flag_r=input_size(mn); //size 2
                
            if (flag1 == 1 && flag_r == 1 && n==mn[0]){                    
                int k= mn[1];   
                int **data2 = malloc(n*k*sizeof(int) + n*sizeof(int*)); //matr2
                   int *ptr2 = (int*) (data2+n);
                   for (int i = 0; i < n; i++) data2[i]=ptr2+i*k; 
                   int flag2=0;
                   flag2 = input(data2, n, k);
                       if (flag2 == 1){
                        int **result = malloc(m*k*sizeof(int) + m*sizeof(int*)); //res
                        int *ptr3 = (int*) (result+m);
                       for (int i = 0; i < m; i++) result[i]=ptr3+i*k; 
                        
                        mul(data1, m, n, data2, k, result);             
                        output(result, m, k);
                        free(result);
                       } 
                   free(data2);
            }
            else printf("n/a");
            free(data1);
        }         
    }                        
    return 0;
}

int input_size(int *a) //ввод одномерн массива размеров
{
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
int input(int **a, int m, int n){
    int fl = 1;    
    for (int p = 0; p < m; p++){ 
        for (int q = 0; q < n; q++){
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
void output(int **a, int m, int n){
for (int p = 0; p < m-1; p++) {
        for (int q = 0; q < n-1; q++)
        printf("%d ", a[p][q]);
        printf("%d\n", a[p][n-1]);
    }    
    for (int q = 0; q < n-1; q++)
        printf("%d ", a[m-1][q]);
    printf("%d", a[m-1][n-1]);
}

int sum(int **matrix_first,  int m, int n, int **matrix_second, 
    int **matrix_result){
    for (int p = 0; p < m; p++) 
        for (int q = 0; q < n; q++)
        matrix_result[p][q] = matrix_first[p][q]+matrix_second[p][q];
    }

int transpose(int **matrix,  int m, int n, int **matrix_result, int m_res, int n_res){
for (int p = 0; p < m; p++) 
        for (int q = 0; q < n; q++)
        matrix_result[q][p] = matrix[p][q];

}
int mul(int **matrix_first,  int m, int n, int **matrix_second, int k, int **matrix_result){
    for (int p = 0; p < m; p++)    
        for(int q = 0; q < k; q++){
        int s=0;
        for (int j = 0; j < n; j++)
            s += matrix_first[p][j]*matrix_second[j][q];            
        matrix_result[p][q] = s;
    }                         
    }
