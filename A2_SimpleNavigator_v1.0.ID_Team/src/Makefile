GRAPH_TARGET = s21_graph
ALGORITHM_TARGET = s21_graph_algorithms
QUEUE_TARGET = s21_queue
STACK_TARGET = s21_stack
CLI_TARGET = Navigator

GRAPH_DIR = graph
QUEUE_DIR = queue
STACK_DIR = stack
ALGORITHM_DIR = algorithm
CLI_DIR = cli

BUILD_DIR = build
BUILD_LIB_DIR = $(BUILD_DIR)/lib

.PHONY: all clean style check_style gcov_report test get_gcov

all: $(GRAPH_TARGET) $(ALGORITHM_TARGET) $(CLI_TARGET)

$(GRAPH_TARGET):
	@$(MAKE) -s -C $(GRAPH_DIR) build

$(ALGORITHM_TARGET):
	@$(MAKE) -s -C $(QUEUE_DIR) build
	@$(MAKE) -s -C $(STACK_DIR) build
	@$(MAKE) -s -C $(ALGORITHM_DIR) build

$(CLI_TARGET): $(GRAPH_TARGET) $(ALGORITHM_TARGET)
	@$(MAKE) -s -C $(CLI_DIR) build


run_cli: $(CLI_TARGET)
	@./$(BUILD_DIR)/$(CLI_TARGET)

test:
	@$(MAKE) -s -C $(GRAPH_DIR) test
	@$(MAKE) -s -C $(QUEUE_DIR) test
	@$(MAKE) -s -C $(STACK_DIR) test
	@$(MAKE) -s -C $(ALGORITHM_DIR) test

gcov_report: test
	@mkdir -p coverage
	@lcov --capture --directory . --output-file coverage/info.info
	@genhtml coverage/info.info -o coverage/html
	@echo -e "\n\nCoverage report generated at:\n\
	\033[33m Linux - coverage/html/index.html \033[0m\n\
	\033[33m Windows - coverage\html\index.html \033[0m"

clean:
	@$(MAKE) -s -C $(GRAPH_DIR) clean
	@$(MAKE) -s -C $(QUEUE_DIR) clean
	@$(MAKE) -s -C $(STACK_DIR) clean
	@$(MAKE) -s -C $(ALGORITHM_DIR) clean
	@$(MAKE) -s -C $(CLI_DIR) clean
	@rm -rf coverage
	@rm -rf $(BUILD_DIR)

valgrind_test: $(TEST_TARGET)
	@$(MAKE) -s -C $(GRAPH_DIR) valgrind_test
	@$(MAKE) -s -C $(QUEUE_DIR) valgrind_test
	@$(MAKE) -s -C $(STACK_DIR) valgrind_test
	@$(MAKE) -s -C $(ALGORITHM_DIR) valgrind_test

my_cppcheck_all:
	@cppcheck --enable=all --suppress=missingIncludeSystem .

style:
	@find . -name "*.c" -exec clang-format -i {} +
	@find . -name "*.h" -exec clang-format -i {} +

style_check:
	@find . -name "*.c" -exec clang-format -n {} +
	@find . -name "*.h" -exec clang-format -n {} +

