#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  // Проверка на NULL и корректность размеров матриц
  if (A == NULL || A->matrix == NULL || result == NULL || A->rows < 1 ||
      A->columns < 1) {
    return INCORRECT_MATRIX;
  }

  // Создание матрицы-результата
  int code_err = s21_create_matrix(A->rows, A->columns, result);

  // Выполнение умножения элементов
  for (int i = 0; code_err == OK && i < A->rows; i++) {
    for (int j = 0; code_err == OK && j < A->columns; j++) {
      double product = A->matrix[i][j] * number;
      if (isinf(product)) {
        s21_remove_matrix(
            result);  // Освобождаем память, если обнаружено переполнение
        code_err = CALCULATION_ERROR;  // Возвращаем ошибку вычисления
      } else
        result->matrix[i][j] = product;
    }
  }

  return code_err;
}
