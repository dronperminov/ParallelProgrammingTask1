#pragma once

#include <iostream>

double Dot(double *x, double *y, int n, int threads); // скалярное произведение двух векторов размерности n
void LinearCombination(double a, double *x, double b, double *y, int n, int threads); // линейная комбинация x = ax + by
void MatrixVectorMultiplication(int *ia, int *ja, double *a, int n, double *x, double *result, int threads); // произведение матрицы на вектор