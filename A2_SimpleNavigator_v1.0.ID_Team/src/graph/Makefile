.PHONY: all clean $(LIB_NAME) build test gcov_report

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic
GCOV_FLAGS = --coverage
AR = ar
ARFLAGS = rcs
CHECK_LIBS = -lcheck -lm -lsubunit

LIB_NAME = s21_graph.a
LIB_TEST_NAME = s21_graph_test.a

LIB_F = graph.c
TEST_F = test.c

BUILD_LIB_DIR = ../build/lib

build: $(LIB_NAME)

$(LIB_NAME): *.c *.h | $(BUILD_LIB_DIR)
	$(CC) -c $(LIB_F) $(CFLAGS)
	$(AR) $(ARFLAGS) $(BUILD_LIB_DIR)/$(LIB_NAME) *.o
	rm -f *.o

$(LIB_TEST_NAME): *.c *.h
	$(CC) -c $(LIB_F) $(CFLAGS) $(GCOV_FLAGS)
	$(AR) $(ARFLAGS) $(LIB_TEST_NAME) *.o
	rm -f *.o

test: *.c *.h $(LIB_TEST_NAME)
	$(CC) $(CFLAGS) -c $(TEST_F)
	$(CC) $(CFLAGS) -o test *.o -L. -l:$(LIB_TEST_NAME) $(CHECK_LIBS) $(GCOV_FLAGS)
	rm *.o
	./test

valgrind_test: test
	valgrind --tool=memcheck --leak-check=yes --quiet ./test

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	rm -f $(LIB_TEST_NAME) test *.gcno *.gcda *.o coverage.info *.txt *.dot

$(BUILD_LIB_DIR):
	@mkdir -p $@