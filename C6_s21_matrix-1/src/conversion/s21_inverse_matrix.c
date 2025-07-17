#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  // Проверка на корректность матрицы A
  if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
    return INCORRECT_MATRIX;
  }

  // Вычисление определителя матрицы A
  double determinant = 0.0;
  int code_err = s21_determinant(A, &determinant);
  if (code_err != OK || fabs(determinant) < 1e-7) {
    // Если определитель равен 0 или ошибка при вычислении
    code_err = CALCULATION_ERROR;
  } else {
    // Вычисление матрицы алгебраических дополнений
    matrix_t complements, adjugate;
    code_err = s21_calc_complements(A, &complements);
    if (code_err == OK) {
      code_err = s21_transpose(&complements, &adjugate);
      // Удаляем матрицу алгебраических дополнений, она больше не нужна
      s21_remove_matrix(&complements);
      if (code_err == OK) {
        // Создание матрицы-результата для обратной матрицы
        code_err = s21_create_matrix(A->rows, A->columns, result);
      }
    }

    if (code_err != OK) {
      // Удаляем транспонированную матрицу, если возникла ошибка
      s21_remove_matrix(&adjugate);
    }

    // Деление каждого элемента транспонированной матрицы на определитель
    for (int i = 0; code_err == OK && i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = adjugate.matrix[i][j] / determinant;
      }
    }

    if (code_err == OK) {
      s21_remove_matrix(&adjugate);
    }
  }

  return code_err;
}
