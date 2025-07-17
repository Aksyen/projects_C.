#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // Проверка на корректность входных данных
  if (result == NULL) {
    return INCORRECT_MATRIX;
  }

  if (rows < 1 || columns < 1) {
    result->matrix = NULL;
    return INCORRECT_MATRIX;
  }

  // Инициализация указателей матрицы
  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    return CALCULATION_ERROR;
  }

  // Инициализация строк матрицы
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      // Освобождаем уже выделенную память в случае ошибки
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      return CALCULATION_ERROR;
    }
  }

  // Установка значений полей структуры
  result->rows = rows;
  result->columns = columns;

  return OK;
}

// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//   int code_err = OK;

//   // Проверка на корректность входных данных
//   if (result == NULL) {
//     code_err = INCORRECT_MATRIX;
//   } else if (rows < 1 || columns < 1) {
//     result->matrix = NULL;
//     code_err = INCORRECT_MATRIX;
//   } else {
//     // Инициализация указателей матрицы
//     result->matrix = (double **)calloc(rows, sizeof(double *));
//     if (result->matrix == NULL) {
//       code_err = CALCULATION_ERROR;
//     } else {
//       // Инициализация строк матрицы
//       for (int i = 0; code_err == OK && i < rows; i++) {
//         result->matrix[i] = (double *)calloc(columns, sizeof(double));
//         if (result->matrix[i] == NULL) {
//           // Освобождаем уже выделенную память в случае ошибки
//           for (int j = 0; j < i; j++) {
//             free(result->matrix[j]);
//           }
//           free(result->matrix);
//           result->matrix = NULL;
//           code_err = CALCULATION_ERROR;
//         }
//       }
//       if (code_err == OK) {
//         // Установка значений полей структуры
//         result->rows = rows;
//         result->columns = columns;
//       }
//     }
//   }

//   return code_err;
// }
