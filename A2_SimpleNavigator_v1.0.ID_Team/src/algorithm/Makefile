.PHONY: all clean s21_graph_algorithms.a s21_graph_algorithms_test.a build test gcov_report

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
GCOV_FLAGS = --coverage
AR = ar
ARFLAGS = rcs
CHECK_LIBS = -lcheck -lm -lsubunit

LIB_NAME = s21_graph_algorithms.a
LIB_TEST_NAME = s21_graph_algorithms_test.a

EXTRA_LIBS = -l:../stack/s21_stack_test.a -l:../queue/s21_queue_test.a -l:../graph/s21_graph_test.a

LIB_DIR = code
TEST_DIR = lib_test

LIB_F = $(wildcard *.c)
TEST_F = $(wildcard $(TEST_DIR)/*.c)

BUILD_LIB_DIR = ../build/lib

build: $(LIB_NAME)

$(LIB_NAME): *.c *.h | $(BUILD_LIB_DIR)
	@$(CC) -c $(LIB_F) $(CFLAGS)
	@$(AR) $(ARFLAGS) $(BUILD_LIB_DIR)/$(LIB_NAME) *.o
	@rm -f *.o

$(LIB_TEST_NAME): *.c *.h
	@$(CC) -c $(LIB_F) $(CFLAGS) $(GCOV_FLAGS)
	@$(AR) $(ARFLAGS) $(LIB_TEST_NAME) *.o
	@rm -f *.o

test: *.c *.h $(TEST_DIR)/*.c $(TEST_DIR)/*.h $(LIB_TEST_NAME)
	@$(CC) $(CFLAGS) -c $(TEST_F)
	@$(CC) $(CFLAGS) -o test *.o -L. -l:$(LIB_TEST_NAME) $(EXTRA_LIBS) $(CHECK_LIBS) $(GCOV_FLAGS)
	@rm *.o
	@./test

valgrind_test: test
	@valgrind --tool=memcheck --leak-check=yes --quiet ./test

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	@rm -f $(LIB_NAME) $(LIB_TEST_NAME) test *.gcno *.gcda *.o coverage.info lib_test/*.txt

$(BUILD_LIB_DIR):
	@mkdir -p $@