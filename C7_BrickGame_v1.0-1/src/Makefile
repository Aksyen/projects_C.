.PHONY: all build/libtetris.a install uninstall test gcov_report dvi dist clang_format clang_check valgrind clean

# Определение операционной системы
UNAME_S := $(shell uname -s)

# Флаги для разных ОС
ifeq ($(UNAME_S), Darwin)
	LDFLAGS := -lncurses
#	OS_INSTALL := brew install ncurses
else ifeq ($(UNAME_S), Linux)
	LDFLAGS := -lncurses -lcheck -lsubunit -lm
#	OS_INSTALL := sudo apt-get install libncurses5-dev libcheck-dev
endif

CFLAGS = -Wall -Wextra -Werror -std=c11
#LDFLAGS = -lncurses -lcheck -lsubunit -lm
SRC = brick_game/tetris/backend.c gui/cli/frontend.c brick_game.c
GCOV_FLAGS = --coverage
LIB_NAME = s21_tetris.a
DEFAULT_BUILD_DIR = builds
INSTALL_PATH_FILE = install_path.txt

# Присваиваем INSTALL_PATH значение из файла install_path.txt или по умолчанию
INSTALL_PATH = $(shell if [ -f $(INSTALL_PATH_FILE) ]; then cat $(INSTALL_PATH_FILE); else echo $(DEFAULT_BUILD_DIR); fi)

# Правило по умолчанию - установка
all: install

# Компиляция библиотеки
$(INSTALL_PATH)/$(LIB_NAME): $(SRC)
	@echo "Building library $(LIB_NAME)"
	mkdir -p $(INSTALL_PATH)
	gcc $(CFLAGS) -c $(SRC)
	ar rcs $(INSTALL_PATH)/$(LIB_NAME) *.o
	rm -f *.o

# Установка программы с учетом install_path.txt
install: clean $(INSTALL_PATH)/$(LIB_NAME)
	@echo "Creating high_score.txt"
	echo 0 > $(INSTALL_PATH)/high_score.txt
	@echo "Compiling and linking executable"
	gcc $(CFLAGS) brick_game.c -L$(INSTALL_PATH) -l:$(LIB_NAME) $(LDFLAGS) -o $(INSTALL_PATH)/tetris

# Запуск программы
run: clean install
	@echo "Running the game"
	$(INSTALL_PATH)/tetris

# указать новый путь установки(по умолчанию builds)
set_install_path:
	@bash set_install_path.sh

# Удаление установленной программы
uninstall:
	@echo "Removing build directory"
	rm -rf $(INSTALL_PATH)

# Очистка
clean: uninstall
	@echo "Cleaning project"
	rm -rf gcov builds
	rm -f unit_test/unit_test unit_test/high_score.txt
	rm -f brickgame_v1.zip
	rm -f docs/*.aux docs/*.log docs/*.dvi docs/*.pdf docs/*.html docs/*.toc docs/*.out

# Создание документации о проекте
dvi:
	@echo "Generating documentation"
	xelatex -output-directory=docs docs/documentation.tex

# предназначена для автоматизации процесса создания дистрибутива программы — архива
dist: dvi
	@echo "Creating distribution archive"
# создаем временную директорию для всех файлов проекта, которую назовем brickgame_v1
	mkdir -p brickgame_v1  
# копируем все необходимые файлы в эту временную директорию
	cp -r Makefile brick_game.c brick_game.h Diagrama.png Diagrama.pdf install_path.txt set_install_path.sh ../README.md ../misc docs brick_game gui unit_test brickgame_v1
# создаем zip-архив из директории brickgame_v1. Опция -r указывает на рекурсивное добавление всех файлов и директорий
	zip -r brickgame_v1.zip brickgame_v1
# удаляем временную директорию, так как она больше не нужна, а архив уже создан 
	rm -rf brickgame_v1

# Тестирование
test: clean $(INSTALL_PATH)/$(LIB_NAME)
	@echo "Running unit tests"
	echo 0 > unit_test/high_score.txt
	gcc $(CFLAGS) unit_test/unit_test.c -L$(INSTALL_PATH) -l:$(LIB_NAME) $(LDFLAGS) -o unit_test/unit_test
	cd unit_test && ./unit_test

# Отчет по покрытию
gcov_report: clean $(INSTALL_PATH)/$(LIB_NAME)
	@echo "Generating coverage report"
	mkdir -p gcov
	echo 0 > gcov/high_score.txt
	gcc $(CFLAGS) $(GCOV_FLAGS) unit_test/unit_test.c brick_game/tetris/backend.c -L$(INSTALL_PATH) -l:$(LIB_NAME) $(LDFLAGS) -o gcov/gcov_test
	cd gcov && ./gcov_test
	lcov --capture --directory . --output-file gcov/coverage.info
	lcov --remove gcov/coverage.info '*unit_test/*' --output-file gcov/coverage.info
	genhtml -o gcov/report gcov/coverage.info

# Путь ко всем файлам .c и .h в текущей директории и поддиректориях
SRC_FILES := $(shell find . -type f \( -name "*.c" -o -name "*.h" \))

clang_format:
	@echo "Running clang-format"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h $(SRC_FILES)
	rm -f .clang-format

clang_check:
	@echo "Running clang-check"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h $(SRC_FILES)
	rm -f .clang-format

valgrind: test
	@echo "Running Valgrind"
	cd unit_test && valgrind --tool=memcheck --leak-check=yes ./unit_test

# install gcovr: sudo apt install gcovr
# install xelatex: sudo apt-get install texlive-xetex (or sudo apt-get install texlive-latex-extra)
