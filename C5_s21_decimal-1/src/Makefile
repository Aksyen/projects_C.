.PHONY: all clean rebuild gcov_report leaks leaks-errors test gcov_s21_string.a check-format format cppcheck cppcheck-errors

FLAG        = -Wall -Wextra -Werror -std=c11 -lm
FLAG_LIB    = -lcheck -lsubunit -lm
FLAG_GCOV   = -fprofile-arcs -ftest-coverage

SRC_ARITH   = $(wildcard arithmetic/*.c)
OBJ_ARITH   = $(patsubst arithmetic/%.c,%.o, $(SRC_ARITH))

SRC_CMP     = $(wildcard comparison/*.c)
OBJ_CMP     = $(patsubst comparison/%.c,%.o, $(SRC_CMP))

SRC_CONV    = $(wildcard conversion/*.c)
OBJ_CONV    = $(patsubst conversion/%.c,%.o, $(SRC_CONV))

SRC_OTHER   = $(wildcard other/*.c)
OBJ_OTHER   = $(patsubst other/%.c,%.o, $(SRC_OTHER))

SRC_COM     = $(wildcard common/*.c)
OBJ_COM     = $(patsubst common/%.c,%.o, $(SRC_COM))

SRC_TEST    = $(wildcard tests/*.c)

# Правило для создания библиотеки
s21_decimal.a: $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COM)
	gcc -c $(FLAG) $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COM) s21_decimal.h
	ar rcs s21_decimal.a $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COM)

all: s21_decimal.a

# Правило для запуска тестов
test: clean s21_decimal.a
	gcc $(FLAG) $(SRC_TEST) s21_decimal.a -o unit_test $(FLAG_LIB)
	./unit_test

# Правило для создания библиотеки с поддержкой gcov
gcov_s21_decimal.a: $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COM)
	gcc -c $(FLAG_GCOV) $(FLAG) $(SRC_ARITH) $(SRC_CMP) $(SRC_CONV) $(SRC_OTHER) $(SRC_COM) s21_decimal.h
	ar rcs s21_decimal.a $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COM)

# Правило для создания gcov отчета
gcov_report: clean gcov_s21_decimal.a
	gcc $(FLAG_GCOV) $(FLAG) $(SRC_TEST) s21_decimal.a -o gcov_unit_test $(FLAG_LIB)
	./gcov_unit_test
	gcov $(OBJ_ARITH) $(OBJ_CMP) $(OBJ_CONV) $(OBJ_OTHER) $(OBJ_COM)
	lcov -t "gcov_report" -o s21_decimal_coverage.info -c -d .
	genhtml -o report s21_decimal_coverage.info

# Правило для проверки утечек памяти
leaks: clean s21_decimal.a
	gcc $(FLAG) $(SRC_TEST) s21_decimal.a -o unit_test $(FLAG_LIB) 
	valgrind --tool=memcheck --leak-check=yes ./unit_test

# Правило для проверки утечек памяти с выводом только ошибок и их местоположения
leaks-errors: clean s21_decimal.a
	gcc $(FLAG) $(SRC_TEST) s21_decimal.a -o unit_test $(FLAG_LIB)
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

# Добавление правила для проверки проекта с помощью cppcheck, выводя только ошибки и сохраняя их в файл cppcheck_errors.log
cppcheck-errors:
	cppcheck --enable=all --inconclusive --quiet --std=c11 --language=c --suppress=missingIncludeSystem $(SRC_FILES) 2> cppcheck_errors.log


clean:
	rm -f s21_decimal.a
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
