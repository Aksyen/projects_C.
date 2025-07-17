#ifndef GRAPH_H
#define GRAPH_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 10

/**
 * @brief Структура для графа в виде матрицы смежности.
 *
 * @param size Количество вершин.
 * @param matrix Матрица смежности.
 */
typedef struct {
  int size;
  int **matrix;
} Graph;

/**
 * @brief Чтения графа в виде матрицы смежности из файла.
 *
 * @param filename Путь к файлу.
 * @return При успешном выделении памяти указатель на созданный граф, иначе
 * NULL.
 * @note При успешном создании графа после завершении работы с ним, следует
 * освободить память функцией free_graph().
 */
Graph *load_graph_from_file(const char *filename);

/**
 * @brief Запись графа в файл в формате dot.
 *
 * @param filename Путь к файлу.
 * @param graph Указатель на граф.
 * @return При успешной записи 0, иначе 1.
 */
int export_graph_to_dot(const char *filename, const Graph *graph);

/**
 * @brief Выделение памяти для матрицы смежности и установка размера графа.
 *
 * @param size Количество вершин графа, размер.
 * @return При успешном выделении памяти указатель на созданный граф, иначе
 * NULL.
 * @note При успешном создании графа после завершении работы с ним следует
 * освободить память функцией free_graph().
 */
Graph *create_graph(int size);

/**
 * @brief Освобождение выделеной памяти для матрицы смежности и для самого
 * графа.
 *
 * @param graph Указатель на граф.
 */
void free_graph(Graph *graph);

/**
 * @brief Возвращает количество вершин графа
 *
 * @param graph Указатель на граф.
 */
int get_size_graph(const Graph *graph);

/**
 * @brief Возвращает матрицу смежности
 *
 * @param graph Указатель на граф.
 */
const int **get_matrix_graph(const Graph *graph);

/**
 * @brief Возвращает матрицу
 *
 * @param rows Количество строк матрицы.
 * @param cols Количество столбцов матрицы.
 * @return При успешном выделении памяти указатель на созданную матрицу, иначе
 * NULL.
 */
int **create_matrix(int rows, int cols);

/**
 * @brief Освобождение выделеной памяти для матрицы
 *
 * @param mat Указатель на матрицу.
 * @param size Размер матрицы.
 */
void remove_matrix(int **mat, int rows);

/**
 * @brief Преобразование номера вершины в ее буквенное обозначение.
 *
 * @param n Номер вершины.
 */
void get_name_vertex(char name[NAME_SIZE + 1], int n);

/**
 * @brief Определение является ли граф ориентированным. Проверка на
 * симетричность матрицы смежности.
 *
 * @param graph Указатель на граф.
 * @return Если диграф 1, иначе 0.
 */
int is_digraph(const Graph *graph);

#endif