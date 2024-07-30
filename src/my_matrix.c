#include "my_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int my_create_matrix(int rows, int columns, matrix_t *result) {
  *result = set_zero(result);
  int status = check_size(rows, columns);
  if (status == OK) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = matrix_alloc(rows, columns);
    if (result->matrix == NULL) {
      status = WRONG_MATRIX;
    }
  }
  return status;
}

void my_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    matrix_free(A->matrix, A->rows);
    *A = set_zero(A);
  }
}

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  int status = FAILURE;
  int check_A = check_size(A->rows, A->columns);
  int check_B = check_size(B->rows, B->columns);
  if ((check_A == OK) && (check_B == OK)) {
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          if (((A->matrix[i][j] >= 0) && (B->matrix[i][j] >= 0)) ||
              ((A->matrix[i][j] <= 0) && (B->matrix[i][j] <= 0))) {
            if (fabs(A->matrix[i][j] - B->matrix[i][j]) < PRECISION) {
              status = SUCCESS;
            } else {
              status = FAILURE;
              break;
            }
          }
    }
  }
  return status;
}

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  *result = set_zero(result);
  int status = check_matrix_sum(A, B);
  if (status == OK) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
  }
  return status;
}

int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  *result = set_zero(result);
  int status = check_matrix_sum(A, B);
  if (status == OK) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
  }
  return status;
}

int my_mult_number(matrix_t *A, double number, matrix_t *result) {
  *result = set_zero(result);
  int status = check_size(A->rows, A->columns);
  if (status == OK) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
  }
  return status;
}

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  *result = set_zero(result);
  int status = check_matrix_mul(A, B);
  if (status == OK) {
    my_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++) {
        double sum = 0;
        for (int k = 0; k < A->columns; k++) {
          sum = sum + A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = sum;
      }
  }
  return status;
}

int my_transpose(matrix_t *A, matrix_t *result) {
  *result = set_zero(result);
  int status = check_size(A->rows, A->columns);
  if (status == OK) {
    my_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
  }
  return status;
}
int my_calc_complements(matrix_t *A, matrix_t *result) {
  *result = set_zero(result);
  int status = check_matrix_deter(A);
  matrix_t minor = {0};
  if (status == OK) {
    int n = A->rows;
    my_create_matrix(n, n, result);
    if (n == 1) {
      result->matrix[0][0] = 1;
    } else {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
          get_matrix_n_1(A, i, j, &minor);
          result->matrix[i][j] = get_k(i, j) * find_det(&minor);
          my_remove_matrix(&minor);
        }
    }
  }
  return status;
}

int my_determinant(matrix_t *A, double *result) {
  int status = check_matrix_deter(A);
  if (status == OK) {
    *result = find_det(A);
  } else {
    *result = 0;
  }
  return status;
}

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  *result = set_zero(result);
  int status = check_matrix_deter(A);
  if (status == OK) {
    double det = find_det(A);
    if (det != 0) {
      matrix_t calc_comp = {0};
      matrix_t trans = {0};
      my_calc_complements(A, &calc_comp);
      my_transpose(&calc_comp, &trans);
      my_remove_matrix(&calc_comp);
      my_mult_number(&trans, (1. / det), result);
      my_remove_matrix(&trans);
    } else {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}
