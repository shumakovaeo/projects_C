all: cipher

CFLAGS=-c -std=c11 -Wall -Werror -Wextra

cipher: cipher.o
	gcc cipher.c -o ../build/cipher


cipher.o: cipher.c
	gcc $(CFLAGS) cipher.c

clean:
	rm -rf *.o

rebuild: clean all

valgrind:
	valgrind --tool=memcheck --leak-check=yes ../build/cipher


cppcheck:
	cppcheck --enable=all --std=c11 --suppress=missingIncludeSystem cipher.c

clang:
	clang-format -i *.c
	clang-format -i *.h
	clang-format -n *.c
	clang-format -n *.h
