#include "my_matrix.h"

matrix_t set_zero(matrix_t *A) {
  matrix_t B = {0};
  *A = B;
  return *A;
}

double **matrix_alloc(int rows, int columns) {
  double **A = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++) {
    A[i] = (double *)malloc(columns * sizeof(double));
  }
  return A;
}

void matrix_free(double **matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

int check_size(int rows, int columns) {
  int status = OK;
  if (rows <= 0 || columns <= 0) status = WRONG_MATRIX;
  return status;
}

int check_matrix_sum(matrix_t *A, matrix_t *B) {
  int status = OK;
  if (A == NULL || B == NULL) {
    status = WRONG_MATRIX;
  } else {
    int check_A = check_size(A->rows, A->columns);
    int check_B = check_size(B->rows, B->columns);
    if ((check_A + check_B) > OK) {
      status = WRONG_MATRIX;
    } else if ((A->rows != B->rows) || (A->columns != B->columns)) {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}

int check_matrix_mul(matrix_t *A, matrix_t *B) {
  int status = OK;
  if (A == NULL || B == NULL) {
    status = WRONG_MATRIX;
  } else {
    int check_A = check_size(A->rows, A->columns);
    int check_B = check_size(B->rows, B->columns);
    if ((check_A + check_B) > OK) {
      status = WRONG_MATRIX;
    } else if (A->columns != B->rows) {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}

int check_matrix_deter(matrix_t *A) {
  int status = OK;
  if (A == NULL) {
    status = WRONG_MATRIX;
  } else {
    int check_A = check_size(A->rows, A->columns);
    if (check_A) {
      status = WRONG_MATRIX;
    } else if (A->columns != A->rows) {
      status = CALCULATION_ERROR;
    }
  }
  return status;
}

void get_matrix_n_1(matrix_t *A, int i_m, int j_m, matrix_t *result) {
  int n = A->columns;
  my_create_matrix(n - 1, n - 1, result);
  int k = 0;
  for (int i = 0; i < n; i++) {
    int t = 0;
    for (int j = 0; j < n; j++) {
      if ((i != i_m) && (j != j_m)) {
        result->matrix[k][t] = A->matrix[i][j];
        t++;
      }
    }
    if (i != i_m) {
      k++;
    }
  }
}

double get_minor_2n(matrix_t *A) {
  return ((A->matrix[0][0] * A->matrix[1][1]) -
          (A->matrix[0][1] * A->matrix[1][0]));
}

double get_k(int i, int j) { return ((i + j) % 2 == 0) ? 1. : -1.; }

double find_det(matrix_t *A) {
  double result = 0;
  matrix_t minor = {0};
  int n = A->rows;
  if (n == 1) {
    result = A->matrix[0][0];
  } else if (n == 2) {
    result = get_minor_2n(A);
  } else {
    for (int j = 0; j < n; j++) {
      get_matrix_n_1(A, 0, j, &minor);
      result = result + get_k(0, j) * A->matrix[0][j] * find_det(&minor);
      my_remove_matrix(&minor);
    }
  }
  return result;
}