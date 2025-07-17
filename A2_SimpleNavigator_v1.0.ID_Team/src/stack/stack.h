#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Узел стека.
 */
typedef struct StackNode {
  int value;              /**< Значение элемента */
  struct StackNode* next; /**< Указатель на следующий узел */
} StackNode;

/**
 * @brief Структура стека.
 */
typedef struct Stack {
  StackNode* top; /**< Указатель на вершину стека */
} Stack;

/**
 * @brief Создаёт пустой стек.
 *
 * @return Указатель на созданный стек.
 */
Stack* stack_create();

/**
 * @brief Добавляет элемент на вершину стека.
 *
 * @param stack Указатель на стек.
 * @param value Значение для добавления.
 */
void push_stack(Stack* stack, int value);

/**
 * @brief Удаляет и возвращает верхний элемент стека.
 *
 * @param stack Указатель на стек.
 * @return Значение верхнего элемента.
 *
 * @warning Завершает программу, если стек пуст.
 */
int pop_stack(Stack* stack);

/**
 * @brief Возвращает верхний элемент стека без удаления.
 *
 * @param stack Указатель на стек.
 * @return Значение верхнего элемента.
 *
 * @warning Завершает программу, если стек пуст.
 */
int top_stack(const Stack* stack);

/**
 * @brief Проверяет, пуст ли стек.
 *
 * @param stack Указатель на стек.
 * @return true, если стек пуст, иначе false.
 */
bool empty_stack(const Stack* stack);

/**
 * @brief Очищает стек и освобождает память.
 *
 * @param stack Указатель на стек.
 */
void destroy_stack(Stack* stack);

#endif  // STACK_H
