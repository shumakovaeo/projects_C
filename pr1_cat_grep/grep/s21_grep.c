#include "libgrep.h"

arguments *argument_parser(int argc, char **argv) {
  arguments *arg = malloc(sizeof(arguments));
  *arg = (arguments){0};
  int opt;
  while ((opt = getopt(argc, argv, "e:invclhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg->e = 1;
        pattern_add(arg, optarg);
        break;
      case 'n':
        arg->n = 1;
        break;
      case 's':
        arg->s = 1;
        break;
      case 'i':
        arg->i = REG_ICASE;
        break;
      case 'v':
        arg->v = 1;
        break;
      case 'c':
        arg->c = 1;
        break;
      case 'l':
        arg->l = 1;
        break;
      case 'h':
        arg->h = 1;
        break;
      case 'o':
        arg->o = 1;
        break;
      case 'f':
        arg->f = 1;
        ad_reg_from_file(arg, optarg);
        break;
      default:
        break;
    }
  }
  if (arg->pattern == NULL) {
    pattern_add(arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg->h = 1;
  }
  return arg;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s FILE\n", argv[0]);
    return 0;
  }
  arguments *arg = argument_parser(argc, argv);
  output(arg, argc, argv);

  free(arg->pattern);
  free(arg);
  return 0;
}