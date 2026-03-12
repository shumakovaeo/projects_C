all: strlen_tests

CFLAGS=-c -std=c11 -Wall -Werror -Wextra

strlen_tests: s21_string.o s21_string_test.o
	gcc s21_string.c s21_string_test.c -o ../build/Quest_1


s21_string_test.o: s21_string_test.c
	gcc $(CFLAGS) s21_string_test.c
s21_string.o: s21_string.c s21_string.h
	gcc $(CFLAGS) s21_string.c

clean:
	rm -rf *.o

rebuild: clean all
