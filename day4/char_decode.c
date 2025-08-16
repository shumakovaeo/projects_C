#include <stdio.h>

int encod();
int decode();
int twosymb();

int main(int argc, char *argv[]) {
  // char *f= argv[1];
  // scanf("%d", &f);
  // getchar();

  if (*argv[1] == '0' && argc == 2)
    encod();

  else if (*argv[1] == '1' && argc == 2)
    decode();
  else
    printf("n/a");
  return 0;
}

int encod() {

  char s, t;
  s = getchar();
  if (s != '\n')
    t = getchar();
  do {
    if ((s != ' ') && (t == ' ')) {
      printf("%x ", s);
      s = getchar();
      if (s != '\n')
        t = getchar();
    } else if ((s != ' ') && (t == '\n')) {
      printf("%x", s);
      break;
    } else if ((s != ' ') && (t != ' ')) {
      printf("n/a");
      break;
    }
  } while (s != '\n' && s != EOF);

  return 0;
}

int decode() {

  int n = twosymb();
  if (n == 0)
    return 0;
  char t = getchar();

  do {
    if (t == ' ') {
      printf("%c ", n);

      n = twosymb();
      if (n == 0)
        return 0;
      t = getchar();

    } else if (t == '\n') {
      printf("%c", n);
      break;
    } else {
      printf("n/a");
      break;
    }
  } while (n != 0);

  return 0;
}

int twosymb() {
  char s, t;
  s = getchar();
  if (s != '\n')
    t = getchar();
  else {
    puts("n/a");
    return 0;
  }
  if ((int)s < 58)
    s = (int)s - 48;
  else if ((int)s < 71)
    s = (int)s - 55;
  else
    s = (int)s - 87;

  if ((int)t < 58)
    t = (int)t - 48;
  else if ((int)t < 71)
    t = (int)t - 55;
  else
    t = (int)t - 87;
  int n = 16 * (s) + t;
  // printf("n=%x", n);
  return n;
}
