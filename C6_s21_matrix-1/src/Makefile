.PHONY: all s21_matrix.a test gcov_report

FLAG        = -Wall -Wextra -Werror -std=c11 -lm
FLAG_LIB    = -lcheck -lsubunit -lm
FLAG_GCOV   = --coverage

SRC_ARITH   = $(wildcard arithmetic/*.c)
OBJ_ARITH   = $(patsubst arithmetic/%.c,%.o, $(SRC_ARITH))

SRC_CMP     = $(wildcard comparison/*.c)
OBJ_CMP     = $(patsubst comparison/%.c,%.o, $(SRC_CMP))

SRC_CONV    = $(wildcard conversion/*.c)
OBJ_CONV    = $(patsubst conversion/%.c,%.o, $(SRC_CONV))

SRC_OTHER   = $(wildcard other/*.c)
OBJ_OTHER   = $(patsubst other/%.c,%.o, $(SRC_OTHER))

SRC_MAT     = $(wildcard matrix/*.c)
OBJ_MAT     = $(patsubst matrix/%.c,%.o, $(SRC_MAT))

SRC_TEST    = $(wildcard tests/*.c)

LIB_NAME = s21_matrix.a
HEADER = s21_matrix.h

# Правило для создания библиотеки
$(LIB_NAME): $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_MAT)
	gcc -c $(FLAG) $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_MAT) $(HEADER)
	ar rcs $(LIB_NAME) $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_MAT)

all: $(LIB_NAME)

# Правило для запуска тестов
test: clean $(LIB_NAME)
	gcc $(FLAG) $(SRC_TEST) $(LIB_NAME) -o unit_test $(FLAG_LIB)
	./unit_test

# Правило для создания библиотеки с поддержкой gcov
lib_with_gcov_flag: $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_MAT)
	gcc -c $(FLAG_GCOV) $(FLAG) $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_MAT) $(HEADER)
	ar rcs $(LIB_NAME) $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_MAT)

# Правило для создания gcov отчета
gcov_report: clean lib_with_gcov_flag
	gcc $(FLAG_GCOV) $(FLAG) $(SRC_TEST) $(LIB_NAME) -o gcov_unit_test $(FLAG_LIB)
	./gcov_unit_test
	gcov $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_MAT)
	lcov -t "gcov_report" -o s21_matrix_coverage.info -c -d .
	genhtml -o report s21_matrix_coverage.info

# Правило для проверки утечек памяти
leaks: clean $(LIB_NAME)
	gcc $(FLAG) $(SRC_TEST) $(LIB_NAME) -o unit_test $(FLAG_LIB) 
	valgrind --tool=memcheck --leak-check=yes ./unit_test

# Правило для проверки утечек памяти с выводом только ошибок и их местоположения
leaks-errors: clean $(LIB_NAME)
	gcc $(FLAG) $(SRC_TEST) $(LIB_NAME) -o unit_test $(FLAG_LIB)
	valgrind --tool=memcheck --leak-check=yes ./unit_test 2> valgrind_errors.log

# Путь ко всем файлам .c и .h в текущей директории и поддиректориях
SRC_FILES := $(shell find . -type f \( -name "*.c" -o -name "*.h" \))

# Правило для проверки формата файлов
check-format:
	@clang-format -n $(SRC_FILES)

# Правило для автоматического форматирования файлов
format:
	@clang-format -i $(SRC_FILES)

# Добавление правила для проверки проекта с помощью cppcheck с выводом всех сообщений
cppcheck:
	cppcheck --enable=all --inconclusive --quiet --std=c11 --language=c --suppress=missingIncludeSystem $(SRC_FILES)

# Добавление правила для проверки проекта с помощью cppcheck, сохраняя их в файл cppcheck_errors.log
cppcheck-errors:
	cppcheck --enable=all --inconclusive --quiet --std=c11 --language=c --suppress=missingIncludeSystem $(SRC_FILES) 2> cppcheck_errors.log


clean:
	rm -f $(LIB_NAME)
	rm -f *.o
	rm -f *.h.gch
	rm -f unit_test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f gcov_unit_test
	rm -rf report
	rm -f *.info
	rm -f cppcheck_errors.log
	rm -f valgrind_errors.log

rebuild: clean all