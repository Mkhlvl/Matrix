CC=gcc
FLAGS= -Wall -Werror -Wextra
LIBS_LINUX= -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
LIBS_MACOS= -L /usr/local/lib -lcheck

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN=open gcov_report/index.html
LIBS=$(LIBS_MACOS)
# LEAK_CHECK = CK_FORK=no leaks -atExit -- ./executable
endif
 
ifeq ($(OS), Linux)
OPEN=lynx
LIBS=$(LIBS_LINUX)
# LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all -s ./executable
endif


all: test gcov_report

my_matrix.o_with_gcov: my_matrix.c my_util.c 
	$(CC) -c my_matrix.c my_util.c --coverage

my_matrix.a_with_gcov: my_matrix.o_with_gcov 	
	ar -rcs my_matrix.a my_matrix.o my_util.o


test: test.check my_matrix.a_with_gcov
	checkmk clean_mode=1 test.check > test.c
	$(CC) $(FLAGS) test.c my_matrix.a -o executable $(LIBS) --coverage
	./executable

my_matrix.a:
	$(CC) -c my_matrix.c my_util.c
	ar -rcs my_matrix.a my_matrix.o my_util.o

gcov_report: test
	gcovr --html --html-details -o report.html
	open report.html

cpp:
# cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h


clean:
	rm -f *.out *.gcda *.gcno *.o *.a report.* my_test test_with_gcov* *.gcov test.c exe*
