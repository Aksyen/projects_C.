#include "graph.h"

static void save_digraph_to_dot(FILE *f, const Graph *graph);
static void save_graph_to_dot(FILE *f, const Graph *graph);

Graph *load_graph_from_file(const char *filename) {
  if (filename == NULL) {
    fprintf(stderr, "Error: filename is NULL\n");
    return NULL;
  }

  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    perror("Error opening file");
    return NULL;
  }

  int size = 0;
  if (fscanf(f, "%d", &size) != 1 || size <= 0) {
    fprintf(stderr, "Error: invalid graph size\n");
    fclose(f);
    return NULL;
  }

  Graph *graph = create_graph(size);
  if (graph == NULL) {
    fclose(f);
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (fscanf(f, "%d", &graph->matrix[i][j]) != 1 ||
          graph->matrix[i][j] < 0) {
        fprintf(stderr, "Error: invalid matrix element at (%d,%d)\n", i, j);
        fclose(f);
        free_graph(graph);
        return NULL;
      }
    }
  }

  fclose(f);
  return graph;
}

Graph *create_graph(int size) {
  if (size < 1) {
    fprintf(stderr, "Error: siae less than 1\n");
    return NULL;
  }

  Graph *graph = (Graph *)calloc(1, sizeof(Graph));
  if (graph == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  graph->size = size;
  graph->matrix = create_matrix(graph->size, graph->size);
  if (graph->matrix == NULL) {
    free(graph);
    errno = ENOMEM;
    return NULL;
  }

  return graph;
}

void free_graph(Graph *graph) {
  if (graph == NULL) return;
  remove_matrix(graph->matrix, graph->size);

  free(graph);
}

int export_graph_to_dot(const char *filename, const Graph *graph) {
  if (graph == NULL || filename == NULL) {
    fprintf(stderr, "Error: NULL pointer\n");
    return 1;
  }
  int status = 0;
  FILE *f = fopen(filename, "w");

  if (f == NULL) {
    perror(filename);
    return 1;
  }

  if (is_digraph(graph)) {
    save_digraph_to_dot(f, graph);
  } else
    save_graph_to_dot(f, graph);

  fclose(f);
  return status;
}

/**
 * @brief Определение является ли граф ориентированным. Проверка на
 * симетричность матрицы сможности.
 *
 * @param graph Указатель на граф.
 * @return Если диграф 1, иначе 0.
 */
int is_digraph(const Graph *graph) {
  int is_dig = 0;
  for (int i = 0; i < graph->size && !is_dig; i++) {
    for (int j = i + 1; j < graph->size && !is_dig; j++) {
      if (graph->matrix[i][j] != graph->matrix[j][i]) is_dig = 1;
    }
  }
  return is_dig;
}

/**
 * @brief Запись в файл граф.
 *
 * @param f Файл.
 * @param graph Указатель на граф.
 */
static void save_graph_to_dot(FILE *f, const Graph *graph) {
  char name1[NAME_SIZE + 1] = {0};
  char name2[NAME_SIZE + 1] = {0};
  fprintf(f, "graph graphname {\n");
  for (int i = 0; i < graph->size; i++) {
    for (int j = i; j < graph->size; j++) {
      if (graph->matrix[i][j] != 0) {
        get_name_vertex(name1, i);
        get_name_vertex(name2, j);
        fprintf(f, "\t%s -- %s [label=%d];\n", name1, name2,
                graph->matrix[i][j]);
      }
    }
  }
  fprintf(f, "}\n");
}

/**
 * @brief Запись в файл граф.
 *
 * @param f Файл.
 * @param graph Указатель на diграф.
 */
static void save_digraph_to_dot(FILE *f, const Graph *graph) {
  char name1[NAME_SIZE + 1] = {0};
  char name2[NAME_SIZE + 1] = {0};

  fprintf(f, "digraph graphname {\n");
  for (int i = 0; i < graph->size; i++) {
    for (int j = 0; j < graph->size; j++) {
      if (graph->matrix[i][j] != 0) {
        get_name_vertex(name1, i);
        get_name_vertex(name2, j);
        fprintf(f, "\t%s -> %s [label=%d];\n", name1, name2,
                graph->matrix[i][j]);
      }
    }
  }
  fprintf(f, "}\n");
}

int get_size_graph(const Graph *graph) { return graph->size; }

const int **get_matrix_graph(const Graph *graph) {
  return (const int **)graph->matrix;
}

int **create_matrix(int rows, int cols) {
  if (rows < 1 || cols < 1) {
    return NULL;
  }

  int **matrix = (int **)malloc(rows * sizeof(int *));
  if (matrix == NULL) return NULL;

  for (int i = 0; i < rows; i++) {
    matrix[i] = (int *)calloc(cols, sizeof(int));
    if (matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(matrix[j]);
      }
      free(matrix);
      matrix = NULL;
      return NULL;
    }
  }
  return matrix;
}

void remove_matrix(int **mat, int rows) {
  if (mat != NULL) {
    for (int i = 0; i < rows; i++) {
      free(mat[i]);
    }
    free(mat);
  }
}

void get_name_vertex(char name[NAME_SIZE + 1], int n) {
  int i = 1;
  char c = n % 26 + 'a';
  n /= 26;

  name[0] = c;
  for (; i < NAME_SIZE && n >= 1; i++) {
    c = n % 26 + 'a';
    n /= 26;
    name[i] = c;
  }
  name[i] = 0;
}
