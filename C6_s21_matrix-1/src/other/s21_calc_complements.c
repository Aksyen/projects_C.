#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  // Проверка на корректность матрицы A
  if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
    return INCORRECT_MATRIX;
  }

  // Создание результирующей матрицы
  int code_err = s21_create_matrix(A->rows, A->columns, result);
  if (code_err != OK) {
    return code_err;
  }

  // Специальный случай для матрицы 1x1 — результатом будет матрица с элементом
  // 1
  if (A->rows == 1) {
    result->matrix[0][0] = 1;
    return OK;
  }

  // Проходим по каждому элементу матрицы A
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      // Создаем подматрицу для вычисления минора
      matrix_t minor;
      s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

      // Заполняем подматрицу элементами исходной матрицы, исключая i-ю строку и
      // j-й столбец
      for (int row = 0, minor_row = 0; row < A->rows; row++) {
        if (row == i) continue;  // Пропускаем i-ю строку
        for (int col = 0, minor_col = 0; col < A->columns; col++) {
          if (col == j) continue;  // Пропускаем j-й столбец
          minor.matrix[minor_row][minor_col] = A->matrix[row][col];
          minor_col++;
        }
        minor_row++;
      }

      // Вычисляем определитель подматрицы
      double minor_determinant = 0.0;
      s21_determinant(&minor, &minor_determinant);
      s21_remove_matrix(&minor);

      // Алгебраическое дополнение с учетом знака (-1)^(i+j)
      result->matrix[i][j] = pow(-1, i + j) * minor_determinant;
    }
  }

  return OK;
}
