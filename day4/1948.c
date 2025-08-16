#include <stdio.h>

int maxprdel(int x);
int prost(int a);
int delit(int x, int y);

int main(void) {
  int a, m = 0;
  if ((scanf("%d", &a) == 1) && a != 0) {
    if (a < 0)
      a = -a;
    m = maxprdel(a);

    printf("%d", m);
  } else
    printf("n/a");

  return 0;
}

int maxprdel(int a) {
  int m;
  for (int i = 2; i <= a; ++i) {
    if ((prost(i) == 1) && (delit(i, a) == 1) && (i > m)) {
      m = i;
    }
  }
  return m;
}

int prost(int a) {
  int f = 1;
  for (int j = 2; j < a; j++)
    if (delit(j, a) == 1) {
      f = 0;
      break;
    } else
      f = 1;
  return f;
}

int delit(int x, int y) {
  while (y - x >= 0) {
    y = y - x;
  }
  if (y == 0)
    return 1;
  else
    return 0;
}
