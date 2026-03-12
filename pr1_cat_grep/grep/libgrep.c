#include "libgrep.h"

void pattern_add(arguments *arg, const char *pattern) {
  if (!pattern) return;
  size_t pat_len = strlen(pattern);
  if (arg->len_pattern == 0) {
    // Первый паттерн — выделяем память
    arg->pattern = malloc(pat_len + 1);
    if (!arg->pattern) {
      perror("malloc");
      return;
    }
    strcpy(arg->pattern, pattern);
    arg->pattern_size = pat_len + 1;
  } else {
    // Добавляем "|pattern"
    size_t needed =
        strlen(arg->pattern) + 1 + pat_len + 1;  // "|" + pattern + '\0'
    char *tmp = realloc(arg->pattern, needed);
    if (!tmp) {
      perror("realloc");
      free(arg->pattern);
      return;
    }
    arg->pattern = tmp;
    strcat(arg->pattern, "|");
    strcat(arg->pattern, pattern);
    arg->pattern_size = needed;
  }
  arg->len_pattern++;
}

void ad_reg_from_file(arguments *arg, char *filepath) {
  FILE *f = fopen(filepath, "r");
  if (!f) {
    if (!arg->s) {
      perror(filepath);
    }
    return;
  }
  char *line = NULL;
  size_t memline = 0;
  ssize_t read = 0;
  read = getline(&line, &memline, f);
  while (read != -1) {
    if (line[read - 1] == '\n') line[read - 1] = '\0';
    pattern_add(arg, line);
    read = getline(&line, &memline, f);
  }
  free(line);
  fclose(f);
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
}

// флаг o
void print_match(regex_t *reg, char *line, arguments *arg, int line_count) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(reg, line + offset, 1, &match, 0);
    if (result != 0) break;
    if (arg->n) printf("%d:", line_count);
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void prosess_file(arguments *arg, char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (!f) {
    if (!arg->s) {
      perror(path);
    }
    return;
  }
  char *line = NULL;
  size_t memline = 0;
  ssize_t read = 0;
  int line_count = 1;
  int c = 0;
  read = getline(&line, &memline, f);
  while (read != -1) {
    int result = regexec(reg, line, 0, NULL, 0);  // 0 если найдено
    if ((result == 0 && !arg->v) || (result != 0 && arg->v)) {
      if (!arg->c && !arg->l) {
        if (!arg->h) printf("%s:", path);
        if (arg->n && !arg->o) printf("%d:", line_count);
        if (arg->o) {
          print_match(reg, line, arg, line_count);
        } else {
          output_line(line, read);
          if (strchr(line, '\n') == NULL &&
              (arg->i || arg->e || arg->n || arg->h))
            printf("\n");
        }
      }
      c++;
    }
    read = getline(&line, &memline, f);
    line_count++;
  }
  free(line);
  if (arg->c && !arg->l) {
    if (!arg->h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (arg->l && c > 0) printf("%s\n", path);
  fclose(f);
}

void output(arguments *arg, int argc, char **argv) {
  regex_t reg;
  // рег.выражение из паттернов
  int error = regcomp(&reg, arg->pattern, REG_EXTENDED | arg->i);
  if (error) {
    perror("Error");
    return;
  }
  for (int i = optind; i < argc; i++) {
    prosess_file(arg, argv[i], &reg);
  }
  regfree(&reg);
}