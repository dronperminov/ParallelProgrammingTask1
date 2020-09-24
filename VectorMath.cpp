#include "VectorMath.h"

// скалярное произведение двух векторов размерности n
double Dot(double *x, double *y, int n, int threads) {
    double result = 0;

    #pragma omp parallel for reduction(+:result) num_threads(threads)
    for (int i = 0; i < n; i++) {
        result += x[i] * y[i];
    }

    return result;
}


// линейная комбинация x = ax + by
void LinearCombination(double a, double *x, double b, double *y, int n, int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        x[i] = x[i] * a + y[i] * b;
    }
}

// произведение матрицы на вектор
void MatrixVectorMultiplication(int *ia, int *ja, double *a, int n, double *x, double *result, int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        double sum = 0;

        for (int index = ia[i]; index < ia[i + 1]; index++)
            sum += a[index] * x[ja[index]];

        result[i] = sum;
    }
}

// покомпонентное произведение векторов
void VectorVectorMultiplication(double *x, double *y, double *result, int n, int threads) {
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        result[i] = x[i] * y[i];
    }
}