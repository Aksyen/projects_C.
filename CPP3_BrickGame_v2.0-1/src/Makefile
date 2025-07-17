.PHONY: all build/libtetris.a install uninstall test gcov_report dvi dist clang_format clang_check valgrind clean

# Определение операционной системы
UNAME_S := $(shell uname -s)

# Флаги для разных ОС
ifeq ($(UNAME_S), Darwin)
	LDFLAGS := -lncurses
else ifeq ($(UNAME_S), Linux)
	LDFLAGS := -lncurses -lcheck -lsubunit -lm
endif

CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Werror
STANDART_C = -std=c11
STANDART_CPP = -std=c++20
SRC_TETRIS = brick_game/tetris/backend_tetris.c gui/cli/frontend.c # brick_game.c
SRS_SNAKE = brick_game/snake/snake_game.cpp brick_game/snake/snake_controller.cpp gui/cli/snake_console_view.cpp
GCOV_FLAGS = --coverage
LIB_TETRIS = s21_tetris.a
LIB_SNAKE = s21_snake.a
DEFAULT_BUILD_DIR = build
INSTALL_PATH_FILE = install_path.txt

# Присваиваем INSTALL_PATH значение из файла install_path.txt или по умолчанию
INSTALL_PATH = $(shell if [ -f $(INSTALL_PATH_FILE) ]; then cat $(INSTALL_PATH_FILE); else echo $(DEFAULT_BUILD_DIR); fi)

# Правило по умолчанию - установка
all: install

# Компиляция библиотеки
libraries: $(INSTALL_PATH)/$(LIB_TETRIS) $(INSTALL_PATH)/$(LIB_SNAKE)

$(INSTALL_PATH)/$(LIB_TETRIS): $(SRC_TETRIS)
	@echo "Building library $(LIB_TETRIS)"
	mkdir -p $(INSTALL_PATH)
	$(CC) $(CFLAGS) $(STANDART_C) -c $(SRC_TETRIS)
	ar rcs $(INSTALL_PATH)/$(LIB_TETRIS) *.o
	rm -f *.o

$(INSTALL_PATH)/$(LIB_SNAKE): $(SRS_SNAKE)
	@echo "Building library $(LIB_SNAKE)"
#	mkdir -p $(INSTALL_PATH)
	$(CXX) $(CFLAGS) $(STANDART_CPP) -c $(SRS_SNAKE)
	ar rcs $(INSTALL_PATH)/$(LIB_SNAKE) *.o
	rm -f *.o

# Установка программы с учетом install_path.txt
install: clean $(INSTALL_PATH)/$(LIB_TETRIS) $(INSTALL_PATH)/$(LIB_SNAKE)
	@echo "Creating high_score.txt"
	echo 0 > $(INSTALL_PATH)/high_score.txt
	@echo "Compiling and linking executable"
	$(CC) $(CFLAGS) $(STANDART_C) brick_game.c -L$(INSTALL_PATH) -l:$(LIB_TETRIS) $(LDFLAGS) -o $(INSTALL_PATH)/tetris
	@echo "Creating high_score_snake.txt"
	echo 0 > $(INSTALL_PATH)/high_score_snake.txt
	@echo "Compiling and linking executable"
	$(CXX) $(CFLAGS) $(STANDART_CPP) snake.cpp -L$(INSTALL_PATH) -l:$(LIB_SNAKE) $(LDFLAGS) -o $(INSTALL_PATH)/snake
	make launcher
	make qt_desktop_build

# Запуск программы 
run_teris_consol:
	@echo "Running the game"
	$(INSTALL_PATH)/tetris

run_snake_consol:
	@echo "Running the game"
	$(INSTALL_PATH)/snake

launcher:
	$(CXX) $(CFLAGS) $(STANDART_CPP) launcher.cpp -L$(INSTALL_PATH) $(LDFLAGS) -o $(INSTALL_PATH)/launcher

game:
	@echo "Running the game"
	$(INSTALL_PATH)/launcher

# Qt desktop сборка (Tetris + Snake через BrickGameV2)
qt_desktop_build:
	@echo "==> Building Qt desktop version (BrickGameV2)"
	mkdir -p $(INSTALL_PATH)/desktop
	cd $(INSTALL_PATH)/desktop && cmake ../../ && make

run_qt:
	@echo "==> Running Qt desktop version"
	./$(INSTALL_PATH)/desktop/BrickGameV2



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
	rm -rf gcov
	rm -f unit_test/unit_test unit_test/high_score.txt unit_test/test_snake
	rm -f brickgame_v2.zip
	rm -rf docs/browser
	rm -f unit_test/test_snake_cov unit_test/*.gcda unit_test/*.gcno 

# Создание документации о проекте
dvi:
	@echo "Generating documentation"
	@doxygen docs/Doxyfile

# предназначена для автоматизации процесса создания дистрибутива программы — архива
dist:
	@echo "Creating distribution archive"
# создаем временную директорию для всех файлов проекта, которую назовем brickgame_v2
	mkdir -p ../brickgame_v2  
# копируем все необходимые файлы в эту временную директорию
	cp -r  ../src ../brickgame_v2
# создаем zip-архив из директории brickgame_v2. Опция -r указывает на рекурсивное добавление всех файлов и директорий
	zip -r brickgame_v2.zip ../brickgame_v2
# удаляем временную директорию, так как она больше не нужна, а архив уже создан 
	rm -rf ../brickgame_v2

# Тестирование
test_tetris: clean $(INSTALL_PATH)/$(LIB_TETRIS)
	@echo "Running unit tests"
	echo 0 > unit_test/high_score.txt
	$(CC) $(CFLAGS) unit_test/unit_test.c -L$(INSTALL_PATH) -l:$(LIB_TETRIS) $(LDFLAGS) -o unit_test/unit_test
	cd unit_test && ./unit_test

test: unit_test/snake_game_test.cpp brick_game/snake/snake_game.cpp
	@echo "Running unit tests for snake"
	g++ -std=c++20 -Wall -Wextra -Werror -I./unit_test \
	    unit_test/snake_game_test.cpp brick_game/snake/snake_game.cpp \
		brick_game/snake/snake_controller.cpp \
	    -o unit_test/test_snake \
	    -lgtest -lgtest_main -pthread
	./unit_test/test_snake

test_snake_cov: unit_test/snake_game_test.cpp brick_game/snake/snake_game.cpp
	g++ -std=c++20 -Wall -Wextra -Werror -I./unit_test $(GCOV_FLAGS) \
	    unit_test/snake_game_test.cpp brick_game/snake/snake_game.cpp \
		brick_game/snake/snake_controller.cpp \
	    -o unit_test/test_snake_cov -lgtest -lgtest_main -pthread
	./unit_test/test_snake_cov



# Отчет по покрытию
# gcov_report: clean $(INSTALL_PATH)/$(LIB_TETRIS)
# 	@echo "Generating coverage report"
# 	mkdir -p gcov
# 	echo 0 > gcov/high_score.txt
# 	$(CC) $(CFLAGS) $(GCOV_FLAGS) unit_test/unit_test.c brick_game/tetris/backend.c -L$(INSTALL_PATH) -l:$(LIB_TETRIS) $(LDFLAGS) -o gcov/gcov_test
# 	cd gcov && ./gcov_test
# 	lcov --capture --directory . --output-file gcov/coverage.info
# 	lcov --remove gcov/coverage.info '*unit_test/*' --output-file gcov/coverage.info
# 	genhtml -o gcov/report gcov/coverage.info

gcov_report2: test_snake_cov
	@echo "Generating coverage report"
	mkdir -p gcov
	lcov --capture --directory . --output-file gcov/coverage.info
	lcov --remove gcov/coverage.info '/usr/*' '*/gtest/*' \
	    --output-file gcov/filtered.info
	genhtml -o gcov/report gcov/filtered.info
	@echo "HTML report generated in gcov/report/index.html"

gcov_report: test_snake_cov
	@echo "Generating coverage report"
	mkdir -p gcov
	lcov --capture --directory . \
	     --output-file gcov/coverage.info \
	     --rc lcov_branch_coverage=1 \
	     --ignore-errors mismatch
	lcov --remove gcov/coverage.info \
	     '/usr/*' '*/unit_test/*' \
	     --output-file gcov/filtered.info
	genhtml -o gcov/report gcov/filtered.info
	@echo "HTML report available at gcov/report/index.html"


# Путь ко всем файлам .c и .h в текущей директории и поддиректориях
SRC_FILES := $(shell find . -type f \( -name "*.c" -o -name "*.h" -o -name "*.cpp" -o -name "*.hpp" \))

clang_format:
	@echo "Running clang-format"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(SRC_FILES)
	rm -f .clang-format

clang_check:
	@echo "Running clang-check"
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(SRC_FILES)
	rm -f .clang-format

valgrind: test
	@echo "Running Valgrind"
	cd unit_test && valgrind --tool=memcheck --leak-check=yes ./test_snake


# install gcovr: sudo apt install gcovr
