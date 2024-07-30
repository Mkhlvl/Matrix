#ifndef SRC_MY_MATRIX_H_
#define SRC_MY_MATRIX_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Для сравнения матриц
#define SUCCESS 1
#define FAILURE 0
#define PRECISION 0.0000001

// Для остальных
#define OK 0
#define WRONG_MATRIX 1
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матриц (create_matrix)
int my_create_matrix(int rows, int columns, matrix_t *result);
// Очистка матриц (remove_matrix)
void my_remove_matrix(matrix_t *A);
// Сравнение матриц (eq_matrix)
int my_eq_matrix(matrix_t *A, matrix_t *B);
// Сложение матриц (sum_matrix)
int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Вычитание матриц (sub_matrix)
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Умножение матрицы на число(mult_number)
int my_mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение двух матриц(mult_matrix)
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Транспонирование матрицы(transpose)
int my_transpose(matrix_t *A, matrix_t *result);
// Минор матрицы и матрица алгебраических дополнений(calc_complements)
int my_calc_complements(matrix_t *A, matrix_t *result);
// Определитель матрицы(determinant)
int my_determinant(matrix_t *A, double *result);
// Обратная матрица(inverse_matrix)
int my_inverse_matrix(matrix_t *A, matrix_t *result);

// Вспомогательные функции

matrix_t set_zero(matrix_t *A);
double **matrix_alloc(int rows, int columns);
void matrix_free(double **matrix, int rows);
int check_size(int rows, int columns);
int check_matrix_sum(matrix_t *A, matrix_t *B);
int check_matrix_mul(matrix_t *A, matrix_t *B);
int check_matrix_deter(matrix_t *A);
void get_matrix_n_1(matrix_t *A, int i_m, int j_m, matrix_t *result);
double get_minor_2n(matrix_t *A);
double get_k(int i, int j);
// double find_det_n2(matrix_t *A);
double find_det(matrix_t *A);
// void matrix_print(matrix_t *result);

#endif  // SRC_MY_MATRIX_H_
