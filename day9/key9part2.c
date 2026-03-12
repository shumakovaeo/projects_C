#include <stdio.h>
#define LEN 100

int sum(int *buff1, int len1, int *buff2, int len2, int *result, int result_length);
int sub(int *buff1, int len1, int *buff2, int len2, int *result, int result_length);
int input(int *buffer, int length);
void output(const int *buffer, int length, int start);
/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод: 
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод: 
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/
int main()
{
   int data1[LEN], data2[LEN];

    int n1 = input(data1, LEN);

        int n2=0;
    if (n1 >= 1) {
     n2 = input(data2, LEN);

    }

   if (n1 >= 1 && n2 >= 1) {
        int res_l = (n1 > n2) ? n1 : n2;

        int result[LEN+1];

        int ans = sum(data1, n1, data2, n2, result, res_l+1);
        output(result, res_l+1, ans);
       // sub(data1, n1, data2, n2, result, res_l);
       // output(resutl, res_l);
    }

  return 0;
}

int input(int *a, int n) {
    int len1 =0;
    for (int p = 0; p < n; p++) {
        char x, y;
        x = getchar();
        y = getchar();
        if (y==' ' && ((int) x>=48)  && ((int) x<= 57)) {
            *(a + p) = (int)x - 48;
  //          printf("el=%d\n", *(a + p)+1);
            len1++;
        } else {
          if (y=='\n' && ((int) x>=48)  && ((int) x<= 57) ){
            *(a + p) = (int)x - 48;
            len1++;
            break;}
          else{
            printf("n/a");
            len1 = 0;
            break;}}
    }
    return len1;
}

void output(const int *a, int n, int s) {
    for (int p = s; p < n - 1; p++) {
        printf("%d ", *(a + p));
    }
    printf("%d", *(a + n - 1));
}

int sum(int *buff1, int len1, int *buff2, int len2, int *result, int res_l){
  int uvel =0, ans=0, temp=0;

  if (len1<res_l-1) {
       for (int i = res_l-1; i-res_l+len1 >=0; i--){
           temp = buff1[i-res_l+len1]+buff2[i]+uvel;
           result[i] = temp % 10;
            uvel = temp / 10;
            }
      for (int i = res_l-len1-2; i >=0; i--){
        result[i]=buff2[i];
      }
  }
  else
    if (len2<res_l-1) {
      for (int i = res_l-1; i-res_l+len2 >=0; i--){
           temp = buff1[i]+buff2[i-res_l+len2]+uvel;
           result[i] = temp % 10;
           uvel = temp / 10;
         }
         for (int i = res_l-len2-2; i >=0; i--){
        result[i]=buff1[i];
      }
    }
    else{
       for (int i = res_l-2; i >= 0; i--){
         temp = buff1[i]+buff2[i]+uvel;
         result[i+1] = temp % 10;
        uvel = temp / 10;
      }
      result[0] = uvel;
}


//for (int i = 0; i < res_l; i++){  if (result[i] == 0) {    ans++;}  else    break;}

return ans;
}



//void sub(int *buff1, int len1, int *buff2, int len2, int *result, int result_length);
