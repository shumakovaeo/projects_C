#include <stdio.h>

int fib(int n);

int main() {
  // int n;
  double n;
  if ((scanf("%lf", &n) == 1) && (n > 0) && ((int)n == n)) {
    printf("%d", fib(n));
  } else
    printf("n/a");
  return 0;
}

int fib(int n) {
  int z;
  if (n > 2) {
    z = fib(n - 1) + fib(n - 2);
  } else {
    z = 1;
  }
  return z;
}
