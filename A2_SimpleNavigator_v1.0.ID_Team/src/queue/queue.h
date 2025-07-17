#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Узел очереди.
 */
typedef struct QueueNode {
  int value;              /**< Значение элемента */
  struct QueueNode* next; /**< Указатель на следующий узел */
} QueueNode;

/**
 * @brief Структура очереди.
 */
typedef struct Queue {
  QueueNode* front; /**< Указатель на первый элемент */
  QueueNode* back; /**< Указатель на последний элемент */
} Queue;

/**
 * @brief Создаёт пустую очередь.
 *
 * @return Указатель на созданную очередь.
 */
Queue* queue_create();

/**
 * @brief Добавляет элемент в конец очереди.
 *
 * @param queue Указатель на очередь.
 * @param value Значение для добавления.
 */
void push_queue(Queue* queue, int value);

/**
 * @brief Удаляет и возвращает первый элемент очереди.
 *
 * @param queue Указатель на очередь.
 * @return Значение первого элемента.
 *
 * @warning Завершает программу, если очередь пуста.
 */
int pop_queue(Queue* queue);

/**
 * @brief Возвращает первый элемент очереди без удаления.
 *
 * @param queue Указатель на очередь.
 * @return Значение первого элемента.
 *
 * @warning Завершает программу, если очередь пуста.
 */
int front_queue(const Queue* queue);

/**
 * @brief Возвращает последний элемент очереди без удаления.
 *
 * @param queue Указатель на очередь.
 * @return Значение последнего элемента.
 *
 * @warning Завершает программу, если очередь пуста.
 */
int back_queue(const Queue* queue);

/**
 * @brief Проверяет, пуста ли очередь.
 *
 * @param queue Указатель на очередь.
 * @return true, если очередь пуста, иначе false.
 */
bool empty_queue(const Queue* queue);

/**
 * @brief Очищает очередь и освобождает память.
 *
 * @param queue Указатель на очередь.
 */
void destroy_queue(Queue* queue);

#endif  // QUEUE_H
