#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверка на NULL и корректность размеров матриц
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      result == NULL || A->rows < 1 || A->columns < 1 || B->rows < 1 ||
      B->columns < 1 || A->rows != B->rows || A->columns != B->columns) {
    return INCORRECT_MATRIX;
  }

  // Создание матрицы-результата
  int code_err = s21_create_matrix(A->rows, A->columns, result);

  // Выполнение вычитания элементов
  for (int i = 0; code_err == OK && i < A->rows; i++) {
    for (int j = 0; code_err == OK && j < A->columns; j++) {
      double diff = A->matrix[i][j] - B->matrix[i][j];
      if (isinf(diff)) {
        // Освобождаем память, если обнаружено переполнение
        s21_remove_matrix(result);
        // Возвращаем ошибку вычисления
        code_err = CALCULATION_ERROR;
      } else
        result->matrix[i][j] = diff;
    }
  }

  return code_err;
}
