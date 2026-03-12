

GENERATING_GCNO_GCDA_FLAGS = -fprofile-arcs -ftest-coverage
GCOV_LIB = -lgcov
GCOV_FLAGS = --coverage

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic 
LDFLAGS = -lcheck -lsubunit -lm -lpthread $(GCOV_LIB)


COVERAGE_DIR := coverage
GCOV_REPORT_DIR := gcov_report

SRC_DIR := .

LIB_SRC := $(wildcard $(SRC_DIR)/s21_*.c)
LIB_OBJ := $(LIB_SRC:.c=.o)
LIB_NAME := $(SRC_DIR)/s21_string.a
HEADER := $(SRC_DIR)/s21_string.h

TEST_SRC := $(wildcard $(SRC_DIR)/tests/s21_*_test.c) $(SRC_DIR)/tests/main_test.c
TEST_OBJ := $(TEST_SRC:.c=.o)
TEST_EXEC := $(SRC_DIR)/tests/test

all: s21_string.a test

s21_string.a: clean
	$(CC) $(CFLAGS)  -c s21_sprintf.c -o s21_sprintf.o
	$(CC) $(CFLAGS) -c s21_sscanf.c -o s21_sscanf.o
	$(CC) $(CFLAGS)  -c s21_string_plus.c -o s21_string_plus.o
	$(CC) $(CFLAGS)  -c s21_string.c -o s21_string.o
	ar rcs $(LIB_NAME) $(LIB_OBJ)

$(SRC_DIR)/tests/%.o: $(SRC_DIR)/tests/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): clean $(TEST_OBJ)
	$(CC) $(CFLAGS) $(GENERATING_GCNO_GCDA_FLAGS) $(GCOV_FLAGS) -c s21_sprintf.c -o s21_sprintf.o
	$(CC) $(CFLAGS) $(GENERATING_GCNO_GCDA_FLAGS) $(GCOV_FLAGS) -c s21_sscanf.c -o s21_sscanf.o
	$(CC) $(CFLAGS) $(GENERATING_GCNO_GCDA_FLAGS) $(GCOV_FLAGS) -c s21_string_plus.c -o s21_string_plus.o
	$(CC) $(CFLAGS) $(GENERATING_GCNO_GCDA_FLAGS) $(GCOV_FLAGS) -c s21_string.c -o s21_string.o
	ar rcs $(LIB_NAME) $(LIB_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) $(LIB_OBJ) -L$(SRC_DIR) -l:s21_string.a $(LDFLAGS) -o $(TEST_EXEC)

gcov_report:
	@make test || true
	@mkdir -p $(GCOV_REPORT_DIR) $(COVERAGE_DIR) || true
	@lcov --capture --directory . --output-file coverage/cov.info --rc lcov_excl_br_line=0 --rc lcov_branch_coverage=1 2>/dev/null || true
	@genhtml --branch-coverage coverage/cov.info --output-directory $(GCOV_REPORT_DIR) --quiet || true
	@echo "Report generated: $(GCOV_REPORT_DIR)/index.html"

clean:
	rm -f $(LIB_OBJ) $(TEST_OBJ)  $(TEST_EXEC) *.gcda *.gcno $(SRC_DIR)/*.gcda $(SRC_DIR)/*.gcno $(SRC_DIR)/tests/*.gcda $(SRC_DIR)/tests/*.gcno
	rm -rf $(COVERAGE_DIR) $(GCOV_REPORT_DIR)

.PHONY: all clean test s21_string.a gcov_report
