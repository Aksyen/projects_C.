#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  // Проверка на NULL и корректность размеров матриц
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      result == NULL || A->columns != B->rows || A->rows < 1 ||
      A->columns < 1 || B->rows < 1 || B->columns < 1) {
    return INCORRECT_MATRIX;
  }

  // Создание матрицы-результата
  int code_err = s21_create_matrix(A->rows, B->columns, result);
  // Выполнение умножения матриц
  for (int i = 0; code_err == OK && i < A->rows; i++) {
    for (int j = 0; code_err == OK && j < B->columns; j++) {
      double sum = 0.0;
      for (int k = 0; code_err == OK && k < A->columns; k++) {
        sum += A->matrix[i][k] * B->matrix[k][j];
        if (isinf(sum)) {
          // Освобождаем память, если обнаружено переполнение
          s21_remove_matrix(result);
          // Возвращаем ошибку вычисления
          code_err = CALCULATION_ERROR;
        }
      }
      if (code_err == OK) result->matrix[i][j] = sum;
    }
  }

  return code_err;
}