#include <iostream>
#include <iomanip>
#include <clocale>
#include <vector>
#include <omp.h>
#include "GraphGenerator.h"
#include "GraphFiller.h"
#include "ConjugateGradientSolver.h"
#include "VectorMath.h"
#include "Types.h"

double GetRandomValue(double a = -50, double b = 50) {
    return a + rand() * (b - a) / RAND_MAX;
}

void FillVector(double *vector, int n) {
    for (int i = 0; i < n; i++)
        vector[i] = GetRandomValue();
}

double DotPerformanceTest(int n, int threads, int loops = 1000) {
    omp_set_num_threads(threads);
    double *x1 = new double[n];
    double *x2 = new double[n];

    FillVector(x1, n);
    FillVector(x2, n);

    TimePoint t0 = Time::now();

    for (int i = 0; i < loops; i++)
        Dot(x1, x2, n);

    TimePoint t1 = Time::now();
    ms time = std::chrono::duration_cast<ms>(t1 - t0);

    delete[] x1;
    delete[] x2;

    return time.count() / (double) loops;
}

double LinearCombinationPerformanceTest(int n, int threads, int loops = 1000) {
    omp_set_num_threads(threads);

    double *x1 = new double[n];
    double *x2 = new double[n];

    FillVector(x1, n);
    FillVector(x2, n);

    double a = GetRandomValue();
    double b = GetRandomValue();

    TimePoint t0 = Time::now();

    for (int i = 0; i < loops; i++)
        LinearCombination(a, x1, b, x2, n);

    TimePoint t1 = Time::now();
    ms time = std::chrono::duration_cast<ms>(t1 - t0);

    delete[] x1;
    delete[] x2;

    return time.count() / (double) loops;
}

double MatrixVectorMultiplicationPerformanceTest(int n, int threads, int loops = 1000) {
    omp_set_num_threads(threads);
    double *x = new double[n];
    double *y = new double[n];

    int *ia = new int[n + 1];
    int *ja = new int[n*n];
    double *a = new double[n*n];

    FillVector(x, n);
    FillVector(y, n);
    FillVector(a, n*n);

    ia[0] = 0;

    for (int i = 0; i < n; i++) {
        ia[i + 1] = ia[i] + n;

        for (int j = 0; j < n; j++)
            ja[i * n + j] = j;
    }

    TimePoint t0 = Time::now();

    for (int i = 0; i < loops; i++)
        MatrixVectorMultiplication(ia, ja, a, n, x, y);

    TimePoint t1 = Time::now();
    ms time = std::chrono::duration_cast<ms>(t1 - t0);

    delete[] x;
    delete[] y;
    delete[] ia;
    delete[] ja;
    delete[] a;

    return time.count() / (double) loops;
}

void DotPerformanceTest() {
    std::cout << "### Скалярное произведение векторов" << std::endl;
    std::cout << "| T \\ N |   1000  |  10000  |  100000 | 1000000 |" << std::endl;
    std::cout << "|   :-: |     :-: |     :-: |     :-: |     :-: |" << std::endl;

    for (int threads = 1; threads <= 32; threads *= 2) {
        std::cout << "| " << std::setw(5) << threads;
        std::cout << " | " << std::setw(7) << DotPerformanceTest(1000, threads);
        std::cout << " | " << std::setw(7) << DotPerformanceTest(10000, threads);
        std::cout << " | " << std::setw(7) << DotPerformanceTest(100000, threads);
        std::cout << " | " << std::setw(7) << DotPerformanceTest(1000000, threads);
        std::cout << " |" << std::endl;
    }

    std::cout << std::endl;
}

void LinearCombinationPerformanceTest() {
    std::cout << "### Линейная комбинация векторов" << std::endl;
    std::cout << "| T \\ N |   1000  |  10000  |  100000 | 1000000 |" << std::endl;
    std::cout << "|   :-: |     :-: |     :-: |     :-: |     :-: |" << std::endl;

    for (int threads = 1; threads <= 32; threads *= 2) {
        std::cout << "| " << std::setw(5) << threads;
        std::cout << " | " << std::setw(7) << LinearCombinationPerformanceTest(1000, threads);
        std::cout << " | " << std::setw(7) << LinearCombinationPerformanceTest(10000, threads);
        std::cout << " | " << std::setw(7) << LinearCombinationPerformanceTest(100000, threads);
        std::cout << " | " << std::setw(7) << LinearCombinationPerformanceTest(1000000, threads);
        std::cout << " |" << std::endl;
    }

    std::cout << std::endl;
}

void MatrixVectorMultiplicationPerformanceTest() {
    std::cout << "### Матрично-векторное произведение" << std::endl;
    std::cout << "| T \\ N |  250  |  500  |  1000 |  2000 |" << std::endl;
    std::cout << "|   :-: |   :-: |   :-: |   :-: |   :-: |" << std::endl;

    for (int threads = 1; threads <= 32; threads *= 2) {
        std::cout << "| " << std::setw(5) << threads;
        std::cout << " | " << std::setw(5) << MatrixVectorMultiplicationPerformanceTest(250, threads);
        std::cout << " | " << std::setw(5) << MatrixVectorMultiplicationPerformanceTest(500, threads);
        std::cout << " | " << std::setw(5) << MatrixVectorMultiplicationPerformanceTest(1000, threads);
        std::cout << " | " << std::setw(5) << MatrixVectorMultiplicationPerformanceTest(2000, threads);
        std::cout << " |" << std::endl;
    }

    std::cout << std::endl;
}

void VectorMathSpeedUpTest() {
    std::vector<double> spmv;
    std::vector<double> dot;
    std::vector<double> axpby;

    for (int threads = 1; threads <= 32; threads *= 2) {
        dot.push_back(DotPerformanceTest(100000, threads));
        axpby.push_back(LinearCombinationPerformanceTest(100000, threads));
        spmv.push_back(MatrixVectorMultiplicationPerformanceTest(1000, threads));
    }

    std::cout << "### OpenMP ускорение" << std::endl;
    std::cout << "|      Ядро \\ T      |    2    |    4    |    8    |    16   |    32   |" << std::endl;
    std::cout << "|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |" << std::endl;

    std::cout << "|   Dot (N = 100000) |";
    for (size_t i = 1; i < dot.size(); i++)
        std::cout << " " << std::setw(7) << std::setprecision(3) << (dot[0] / dot[i]) << " |";
    std::cout << std::endl;

    std::cout << "| axpby (N = 100000) |";
    for (size_t i = 1; i < axpby.size(); i++)
        std::cout << " " << std::setw(7) << std::setprecision(3) << (axpby[0] / axpby[i]) << " |";
    std::cout << std::endl;

    std::cout << "|    SpMV (N = 1000) |";
    for (size_t i = 1; i < spmv.size(); i++)
        std::cout << " " << std::setw(7) << std::setprecision(3) << (spmv[0] / spmv[i]) << " |";
    std::cout << std::endl << std::endl;
}

void VectorMathPerformanceTest() {
    std::cout << "## Производительность математических ядер" << std::endl;
    DotPerformanceTest();
    LinearCombinationPerformanceTest();
    MatrixVectorMultiplicationPerformanceTest();
    VectorMathSpeedUpTest();
}

void MakePefrormanceTest(int nx, int ny, int k1, int k2, double eps, int threads, int &generationTime, int &fillTime, int &solveTime, int loops) {
    omp_set_num_threads(threads);

    for (int i = 0; i < loops; i++) {
        int n = 0;
        int *ia = NULL;
        int *ja = NULL;
        double *a = NULL;
        double *b = NULL;
        double *x = NULL;
        int iterations;
        double res;

        GraphGenerator generator(nx, ny, k1, k2, false, threads);
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
}

void MakePefrormanceTest(int nx, int ny, int k1, int k2, double eps, int threads, int loops = 10) {
    int generationTime = 0;
    int fillTime = 0;
    int solveTime = 0;

    MakePefrormanceTest(nx, ny, k1, k2, eps, threads, generationTime, fillTime, solveTime, loops);

    std::cout << "| " << std::setw(5) << threads;
    std::cout << " | " << std::setw(13) << generationTime / (double)loops;
    std::cout << " | " << std::setw(14) << fillTime / (double)loops;
    std::cout << " | " << std::setw(13) << solveTime / (double)loops << " |" << std::endl;
}

void PerformanceTest() {
    int k1 = 29;
    int k2 = 37;
    double eps = 1e-5;
    int n[] = { 500, 1000, 2000 };

    std::cout << "## Производительность решения" << std::endl;
    std::cout << "Параметры сетки: k1 = " << k1 << ", k2 = " << k2 << std::endl;

    for (int i = 0; i < 3; i++) {
        std::cout << "### Nx = " << n[i] << ", Ny = " << n[i] << ":" << std::endl;
        std::cout << "|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |" << std::endl;
        std::cout << "|   :-: |           :-: |            :-: |           :-: |" << std::endl;

        for (int threads = 1; threads <= 32; threads *= 2) {
            MakePefrormanceTest(n[i], n[i], k1, k2, eps, threads);
        }

        std::cout << std::endl;
    }
}

void PerformanceSpeedUpTest() {
    std::vector<double> gen;
    std::vector<double> fill;
    std::vector<double> solve;

    for (int threads = 1; threads <= 32; threads *= 2) {
        int generationTime = 0;
        int fillTime = 0;
        int solveTime = 0;

        MakePefrormanceTest(1000, 1000, 29, 37, 1e-5, threads, generationTime, fillTime, solveTime, 5);

        gen.push_back(generationTime);
        fill.push_back(fillTime);
        solve.push_back(solveTime);
    }

    std::cout << "### OpenMP ускорение" << std::endl;
    std::cout << "|      Этап \\ T      |    2    |    4    |    8    |    16   |    32   |" << std::endl;
    std::cout << "|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |" << std::endl;

    std::cout << "|    Генерация графа |";
    for (size_t i = 1; i < gen.size(); i++)
        std::cout << " " << std::setw(7) << std::setprecision(3) << (gen[0] / gen[i]) << " |";
    std::cout << std::endl;

    std::cout << "| Заполнение матрицы |";
    for (size_t i = 1; i < fill.size(); i++)
        std::cout << " " << std::setw(7) << std::setprecision(3) << (fill[0] / fill[i]) << " |";
    std::cout << std::endl;

    std::cout << "|       Решение СЛАУ |";
    for (size_t i = 1; i < solve.size(); i++)
        std::cout << " " << std::setw(7) << std::setprecision(3) << (solve[0] / solve[i]) << " |";
    std::cout << std::endl << std::endl;
}

int main() {
    setlocale(LC_ALL, "russian");
    VectorMathPerformanceTest();
    PerformanceTest();
    PerformanceSpeedUpTest();
}