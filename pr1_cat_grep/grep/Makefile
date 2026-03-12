FLAG = -std=c11 -Wall -Wextra -Werror
FILE=tests2/t1.txt tests2/t2.txt

all: s21_grep
s21_grep: clean
	gcc $(FLAG) s21_grep.c libgrep.c -o s21_grep

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./s21_grep -in he $(FILE)

clang:
	clang-format -i *.c
	clang-format -i *.h
	clang-format -n *.c
	clang-format -n *.h

clean:
	rm -f s21_grep