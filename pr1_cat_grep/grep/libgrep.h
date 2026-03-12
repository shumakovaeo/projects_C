#ifndef L_G2_H
#define L_G2_H

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, v, c, l, n, h, s, o, f;
  char *pattern;
  size_t pattern_size;
  int len_pattern;
} arguments;

void pattern_add(arguments *arg, const char *pattern);
void ad_reg_from_file(arguments *arg, char *filepath);

void print_match(regex_t *reg, char *line, arguments *arg, int line_count);

void prosess_file(arguments *arg, char *path, regex_t *reg);

void output(arguments *arg, int argc, char **argv);

#endif