#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  // Проверка на корректность матрицы A
  if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1) {
    return INCORRECT_MATRIX;
  }

  // Инициализация результата
  *result = 0.0;

  // Базовый случай: матрица 1x1
  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  // Базовый случай: матрица 2x2
  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return OK;
  }

  // Для матриц большего размера используем рекурсивное разложение по первой
  // строке
  matrix_t minor;
  int code_err = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  if (code_err != OK) {
    return code_err;
  }

  // Разложение определителя по первой строке
  for (int j = 0; j < A->columns; j++) {
    // Создаем подматрицу (минор), исключая первую строку и j-й столбец
    for (int row = 1; row < A->rows; row++) {
      for (int col = 0, minor_col = 0; col < A->columns; col++) {
        if (col == j) continue;
        minor.matrix[row - 1][minor_col] = A->matrix[row][col];
        minor_col++;
      }
    }

    // Вычисляем определитель минора рекурсивно
    double minor_determinant = 0.0;
    s21_determinant(&minor, &minor_determinant);

    // Добавляем вклад в общий определитель с учетом знака (-1)^(0+j)
    *result += pow(-1, j) * A->matrix[0][j] * minor_determinant;
  }

  s21_remove_matrix(&minor);

  return OK;
}

// #include "../s21_matrix.h"

// int s21_determinant(matrix_t *A, double *result) {
//   // Проверка на корректность матрицы A
//   if (A == NULL || A->matrix == NULL || A->rows != A->columns || A->rows < 1)
//   {
//     return INCORRECT_MATRIX;
//   }
//   int code_err = OK;  // Переменная для отслеживания кода ошибки
//   *result = 0.0;

//   // Базовый случай: матрица 1x1
//   if (A->rows == 1) {
//     *result = A->matrix[0][0];
//   }
//   // Базовый случай: матрица 2x2
//   else if (A->rows == 2) {
//     *result =
//         A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] *
//         A->matrix[1][0];
//   }
//   // Общий случай для матриц большего размера
//   else {
//     matrix_t minor;
//     code_err = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);

//     // Разложение определителя по первой строке
//     for (int j = 0; code_err == OK && j < A->columns; j++) {
//       // Создание минора: исключаем первую строку и j-й столбец
//       for (int row = 1; row < A->rows; row++) {
//         for (int col = 0, minor_col = 0; col < A->columns; col++) {
//           if (col == j) continue;
//           minor.matrix[row - 1][minor_col] = A->matrix[row][col];
//           minor_col++;
//         }
//       }

//       // Вычисляем определитель минора рекурсивно
//       double minor_determinant = 0.0;
//       code_err = s21_determinant(&minor, &minor_determinant);

//       // Если ошибка в вычислении минора, выходим из цикла
//       if (code_err == OK) {
//         // Алгебраическое дополнение с учетом знака (-1)^(0+j)
//         *result += pow(-1, j) * A->matrix[0][j] * minor_determinant;
//       }
//     }
//     s21_remove_matrix(&minor);
//   }

//   return code_err;
// }
