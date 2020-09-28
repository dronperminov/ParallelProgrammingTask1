#pragma once

#include <iostream>

double Dot(double *x, double *y, int n); // скалярное произведение двух векторов размерности n
void LinearCombination(double a, double *x, double b, double *y, int n); // линейная комбинация x = ax + by
void MatrixVectorMultiplication(int *ia, int *ja, double *a, int n, double *x, double *result); // произведение матрицы на вектор
void VectorVectorMultiplication(double *x, double *y, double *result, int n); // покомпонентное произведение векторов