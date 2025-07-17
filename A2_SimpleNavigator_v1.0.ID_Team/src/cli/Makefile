.PHONY: clean build
TARGET = Navigator

CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -pedantic -lncurses -lm

EXTRA_LIBS = -l:s21_graph_algorithms.a -l:s21_graph.a \
-l:s21_stack.a -l:s21_queue.a

BUILD_DIR = ../build
BUILD_LIB_DIR = $(BUILD_DIR)/lib

build: $(TARGET)

$(TARGET): *.c *.h | $(BUILD_DIR)
	@$(CC) -o $(BUILD_DIR)/$(TARGET) *.c $(LIB_F) -L$(BUILD_LIB_DIR) $(EXTRA_LIBS) $(CFLAGS)

valgrind_test: test
	@valgrind --tool=memcheck --leak-check=yes --quiet ./test

cppcheck:
	@cppcheck --enable=all --suppress=missingIncludeSystem *.c

clean:
	@rm -f $(TARGET) *.dot

$(BUILD_DIR):
	@mkdir -p $@