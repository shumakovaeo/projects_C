#include <math.h>
#include <stdio.h>

double verz(double x);
double lemnisk(double x);
double giperbola(double x);

int main() {
  double pi = acos(-1.0);

  for (int i = 0; i < 21; ++i) { // 42!!!!!
    double x = pi * (2 * i - 41) / 41;
    printf("%.1f|", x);
    double y = giperbola(x) / 21;
    for (int j = 1; j < i * y; ++j)
      printf(" ");
    printf("*\n");
  }
  // double step = giperbola(pi)/20; // макс.значение на 20 шагов
  for (int j = 0; j < 3; ++j)
    printf(" ");

  for (int k = 0; k <= 21; ++k) {
    printf("%8d", k * 8);
    //    for (int j = 1;  j < step; ++j) printf(" ");
  }
  printf("\n");
  return 0;
}

double verz(double x) {
  double y;
  y = 1 / (1 + x * x);
  return y;
}
double lemnisk(double x) {
  double y;
  if (x * x <= 2)
    y = sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
  else
    y = '-';
  return y;
  return 1;
}
double giperbola(double x) {
  double y;
  if (x != 0)
    y = 1 / (x * x);
  else
    y = '-';
  return y;
}
