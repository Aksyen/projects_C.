#include "queue.h"

Queue* queue_create() {
  Queue* queue = (Queue*)malloc(sizeof(Queue));
  if (!queue) {
    fprintf(stderr, "Ошибка: не удалось выделить память под очередь\n");
    exit(EXIT_FAILURE);
  }
  queue->front = NULL;
  queue->back = NULL;
  return queue;
}

void push_queue(Queue* queue, int value) {
  QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
  if (!node) {
    fprintf(stderr, "Ошибка: не удалось выделить память под элемент очереди\n");
    exit(EXIT_FAILURE);
  }
  node->value = value;
  node->next = NULL;

  if (queue->back) {
    queue->back->next = node;
  } else {
    queue->front = node;
  }
  queue->back = node;
}

int pop_queue(Queue* queue) {
  if (empty_queue(queue)) {
    fprintf(stderr, "Ошибка: попытка удалить элемент из пустой очереди\n");
    exit(EXIT_FAILURE);
  }

  QueueNode* node = queue->front;
  int value = node->value;
  queue->front = node->next;
  if (queue->front == NULL) {
    queue->back = NULL;
  }
  free(node);
  return value;
}

int front_queue(const Queue* queue) {
  if (empty_queue(queue)) {
    fprintf(stderr, "Ошибка: попытка получить элемент из пустой очереди\n");
    exit(EXIT_FAILURE);
  }
  return queue->front->value;
}

int back_queue(const Queue* queue) {
  if (empty_queue(queue)) {
    fprintf(stderr,
            "Ошибка: попытка получить последний элемент из пустой очереди\n");
    exit(EXIT_FAILURE);
  }
  return queue->back->value;
}

bool empty_queue(const Queue* queue) { return queue->front == NULL; }

void destroy_queue(Queue* queue) {
  while (!empty_queue(queue)) {
    pop_queue(queue);
  }
  free(queue);
}
