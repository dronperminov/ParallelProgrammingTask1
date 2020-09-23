#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include "VectorMath.h"
#include "Time.h"

class ConjugateGradientSolver {
    int n; // размерность матрицы
    int *ia; // потрет
    int *ja; // матрицы
    double *a; // массив ненулевых коэффициентов матрицы
    double *b; // вектор правой части
    double eps; // точность решения

    int threads; // количество потоков
    bool debug; // нужна ли отладка

    double GetResidualNorm(double *x, double *r) const; // получение нормы невязки
    void InitValues(double *x, double *r, double *m) const; // инициализация начальных значений
    void PrintVector(double *x) const; // вывод вектора
public:
    ConjugateGradientSolver(int n, int *ia, int *ja, double *a, double *b, double eps, int threads, bool debug);

    void Solve(double *&x, int &iterations, double &res); // решение системы
};