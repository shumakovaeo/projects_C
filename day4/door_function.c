#include <math.h>
#include <stdio.h>

double verz(double x);
double lemnisk(double x);
double giperbola(double x);

int main() {
  double pi = acos(-1.0);
  for (int i = 0; i < 42; ++i) {
    double x = pi * (2 * i - 41) / 41;
    if (x == 0)
      printf("%.7f|%.7f|%.7f|-\n", x, verz(x), lemnisk(x));
    else if (x * x >= 2)
      printf("%.7f|%.7f|-|%.7f\n", x, verz(x), giperbola(x));
    else
      printf("%.7f|%.7f|%.7f|%.7f\n", x, verz(x), lemnisk(x), giperbola(x));
  }
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
}
double giperbola(double x) {
  double y;
  if (x != 0)
    y = 1 / (x * x);
  else
    y = '-';
  return y;
}
