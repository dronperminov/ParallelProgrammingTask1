#include <iostream>
#include <iomanip>
#include <omp.h>
#include "GraphGenerator.h"
#include "GraphFiller.h"
#include "ConjugateGradientSolver.h"
#include "VectorMath.h"
#include "Time.h"

double GetRandomValue(double a = -50, double b = 50) {
    return a + rand() * (b - a) / RAND_MAX;
}

void FillVector(double *vector, int n) {
    for (int i = 0; i < n; i++)
        vector[i] = GetRandomValue();
}

void DotPerformanceTest(double *x1, double *x2, int n, int threads, int loops = 10000) {
    omp_set_num_threads(threads);

    TimePoint t0 = Time::now();

    for (int i = 0; i < loops; i++)
        Dot(x1, x2, n);

    TimePoint t1 = Time::now();
    ms time = std::chrono::duration_cast<ms>(t1 - t0);

    std::cout << "Time (T = " << threads << "): " << time.count() / (double) loops << " ms" << std::endl;
}

void LinearCombinationPerformanceTest(double *x1, double *x2, int n, int threads, int loops = 10000) {
    omp_set_num_threads(threads);

    TimePoint t0 = Time::now();

    double a = GetRandomValue();
    double b = GetRandomValue();

    for (int i = 0; i < loops; i++)
        LinearCombination(a, x1, b, x2, n);

    TimePoint t1 = Time::now();
    ms time = std::chrono::duration_cast<ms>(t1 - t0);

    std::cout << "Time (T = " << threads << "): " << time.count() / (double) loops << " ms" << std::endl;
}

void MatrixVectorMultiplicationPerformanceTest(int *ia, int *ja, double *a, int n, double *x, double *y, int threads, int loops = 1000) {
    omp_set_num_threads(threads);

    TimePoint t0 = Time::now();

    for (int i = 0; i < loops; i++)
        MatrixVectorMultiplication(ia, ja, a, n, x, y);

    TimePoint t1 = Time::now();
    ms time = std::chrono::duration_cast<ms>(t1 - t0);

    std::cout << "Time (T = " << threads << "): " << time.count() / (double) loops << " ms" << std::endl;
}

void VectorMathPerformanceTests() {
    std::cout << std::endl;
    std::cout << "Performance math tests" << std::endl;

    int n = 1000000;

    std::cout << "Dot (n = " << n << "):" << std::endl;
    double *x1 = new double[n];
    double *x2 = new double[n];

    FillVector(x1, n);
    FillVector(x2, n);

    for (int threads = 1; threads <= 32; threads *= 2)
        DotPerformanceTest(x1, x2, n, threads);

    std::cout << std::endl;
    std::cout << "Linear combination (n = " << n << "):" << std::endl;
    for (int threads = 1; threads <= 32; threads *= 2)
        LinearCombinationPerformanceTest(x1, x2, n, threads);

    delete[] x1;
    delete[] x2;

    n = 1000;
    x1 = new double[n];
    x2 = new double[n];

    FillVector(x1, n);
    FillVector(x2, n);

    int *ia = new int[n + 1];
    int *ja = new int[n*n];
    double *a = new double[n*n];

    FillVector(a, n*n);

    ia[0] = 0;

    for (int i = 0; i < n; i++) {
        ia[i + 1] = ia[i] + n;

        for (int j = 0; j < n; j++)
            ja[i * n + j] = j;
    }

    std::cout << std::endl;
    std::cout << "Matrix vector multiplication:" << std::endl;
    for (int threads = 1; threads <= 32; threads *= 2)
        MatrixVectorMultiplicationPerformanceTest(ia, ja, a, n, x1, x2, threads);

    delete[] ia;
    delete[] ja;
    delete[] a;
    delete[] x1;
    delete[] x2;
}

void MakePefrormanceTest(int nx, int ny, int k1, int k2, double eps, int threads, int loops = 10) {
    omp_set_num_threads(threads);

    int generationTime = 0;
    int fillTime = 0;
    int solveTime = 0;

    for (int i = 0; i < loops; i++) {
        int n = 0;
        int *ia = NULL;
        int *ja = NULL;
        double *a = NULL;
        double *b = NULL;
        double *x = NULL;
        int iterations;
        double res;

        GraphGenerator generator(nx, ny, k1, k2, false);
        generationTime += generator.Generate(n, ia, ja, false); // запускаем генерацию

        GraphFiller filler(n, ia, ja, false);
        fillTime += filler.Fill(a, b, false); // заполняем массив

        ConjugateGradientSolver solver(n, ia, ja, a, b, eps, false);
        solveTime += solver.Solve(x, iterations, res, false);

        // освобождаем выделенную память
        delete[] ia;
        delete[] ja;
        delete[] a;
        delete[] b;
        delete[] x;
    }

    std::cout << "| " << std::setw(7) << threads;
    std::cout << " | " << std::setw(10) << generationTime / (double)loops;
    std::cout << " | " << std::setw(10) << fillTime / (double)loops;
    std::cout << " | " << std::setw(11) << solveTime / (double)loops << " |" << std::endl;
}

void PerformanceTest() {
    int k1 = 29;
    int k2 = 37;
    double eps = 1e-5;
    int n[4] = { 500, 1000, 2000, 4000 };

    for (int i = 0; i < 4; i++) {
        std::cout << std::endl;
        std::cout << "Total pefrormance test for Nx = " << n[i] << ", Ny = " << n[i] << ":" << std::endl;
        std::cout << "+---------+------------+------------+-------------+" << std::endl;
        std::cout << "| Threads | Generation |    Fill    |    Solve    |" << std::endl;
        std::cout << "+---------+------------+------------+-------------+" << std::endl;

        for (int threads = 1; threads <= 32; threads *= 2) {
            MakePefrormanceTest(n[i], n[i], k1, k2, eps, threads);
        }

        std::cout << "+---------+------------+------------+-------------+" << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    VectorMathPerformanceTests();
    PerformanceTest();
}