CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
GCOV_FLAGS = --coverage
AR = ar
ARFLAGS = rcs
CHECK_LIBS = -lcheck -lm -lsubunit
SRCS = s21_string.c s21_strerror.c s21_sprintf.c s21_sscanf.c s21_functions_c_sharp.c
OBJS = s21_string.o s21_strerror.o s21_sprintf.o s21_sscanf.o s21_functions_c_sharp.o

LIB_NAME = s21_string.a
HEADER = s21_string.h

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $(OBJS)

s21_string.o: s21_string.c $(HEADER)
	$(CC) $(CFLAGS) -c s21_string.c

s21_strerror.o: s21_strerror.c $(HEADER)
	$(CC) $(CFLAGS) -c s21_strerror.c

s21_sprintf.o: s21_sprintf.c s21_string.c $(HEADER)
	$(CC) $(CFLAGS) -c s21_sprintf.c

s21_sscanf.o: s21_sscanf.c s21_string.c $(HEADER)
	$(CC) $(CFLAGS) -c s21_sscanf.c -lm

s21_functions_c_sharp.o: s21_functions_c_sharp.c s21_string.c $(HEADER)
	$(CC) $(CFLAGS) -c s21_functions_c_sharp.c

test: $(LIB_NAME) test.c
	$(CC) $(CFLAGS) -o test test.c -L. -l:$(LIB_NAME) $(CHECK_LIBS)
	./test

clang-format:
	clang-format -style=file -i *.c *.h

valgrind: test
	valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 --log-fd=1 --quiet ./test

valgrind2: test
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         ./test

clean:
	rm -f $(OBJS) $(LIB_NAME) test *.gcno *.gcda *.o coverage.info
	rm -rf coverage_report

gcov_report: clean $(SRCS) test.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(SRCS)
	$(AR) $(ARFLAGS) $(LIB_NAME) $(OBJS)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -o test test.c -L. -l:$(LIB_NAME) $(CHECK_LIBS)
	./test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	@echo "Coverage report generated in coverage_report/index.html"

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRCS) test.c

.PHONY: all clean test gcov_report clang-format valgrind cppcheck
