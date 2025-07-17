#include "stack.h"

Stack* stack_create() {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  if (!stack) {
    fprintf(stderr, "Ошибка: не удалось выделить память под стек\n");
    exit(EXIT_FAILURE);
  }
  stack->top = NULL;
  return stack;
}

void push_stack(Stack* stack, int value) {
  StackNode* node = (StackNode*)malloc(sizeof(StackNode));
  if (!node) {
    fprintf(stderr, "Ошибка: не удалось выделить память под элемент стека\n");
    exit(EXIT_FAILURE);
  }
  node->value = value;
  node->next = stack->top;
  stack->top = node;
}

int pop_stack(Stack* stack) {
  if (empty_stack(stack)) {
    fprintf(stderr, "Ошибка: попытка удалить элемент из пустого стека\n");
    exit(EXIT_FAILURE);
  }
  StackNode* node = stack->top;
  int value = node->value;
  stack->top = node->next;
  free(node);
  return value;
}

int top_stack(const Stack* stack) {
  if (empty_stack(stack)) {
    fprintf(stderr, "Ошибка: попытка получить элемент из пустого стека\n");
    exit(EXIT_FAILURE);
  }
  return stack->top->value;
}

bool empty_stack(const Stack* stack) { return stack->top == NULL; }

void destroy_stack(Stack* stack) {
  while (!empty_stack(stack)) {
    pop_stack(stack);
  }
  free(stack);
}
