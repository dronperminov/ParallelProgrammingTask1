#include "ConjugateGradientSolver.h"

ConjugateGradientSolver::ConjugateGradientSolver(int n, int *ia, int *ja, double *a, double *b, double eps, int threads, bool debug) {
    this->n = n;
    this->ia = ia;
    this->ja = ja;

    this->a = a;
    this->b = b;
    this->eps = eps;

    this->threads = threads;
    this->debug = debug;
}

// получение нормы невязки
double ConjugateGradientSolver::GetResidualNorm(double *x, double *r) const {
    MatrixVectorMultiplication(ia, ja, a, n, x, r, threads); // r = Ax
    LinearCombination(-1, r, 1, b, n, threads); // r = -Ax + b
    
    return sqrt(Dot(r, r, n, threads)); // ||b - Ax||
}

// инициализация начальных значений
void ConjugateGradientSolver::InitValues(double *x, double *r, double *m) const {
    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        x[i] = 0;
        r[i] = b[i]; // b - A*O = b

        int diagIndex = ia[i];

        while (ja[diagIndex] != i)
            diagIndex++;

        m[i] = 1.0 / a[diagIndex];
    }
}

// вывод вектора
void ConjugateGradientSolver::PrintVector(double *x) const {
    std::cout << "x: [ ";

    for (int i = 0; i < n; i++) {
        std::cout << x[i] << " ";
    }

    std::cout << "]" << std::endl;
    std::cout << std::endl;
}

// решение системы
int ConjugateGradientSolver::Solve(double *&x, int &iterations, double &res, bool printInfo) {
    TimePoint t0 = Time::now(); // запускаем замер времени

    x = new double[n]; // начальное решение

    double *r = new double[n]; // начальная невязка
    double *m = new double[n]; // вектор из обратных элементов диагонали матрицы A

    double *z_k = new double[n];
    double *p_k = new double[n];
    double *q_k = new double[n];
    double *debug_r = new double[n]; // вектор для вычисления невязки в debug режиме

    InitValues(x, r, m); // инициализируем значения

    double rho_prev = 0; // предыдущее ро
    iterations = 1; // текущая итерация
    bool isConverge = false; // сошёлся ли алгоритм

    do {
        VectorVectorMultiplication(m, r, z_k, n, threads); // z_k = M^-1 * r_k
        double rho_k = Dot(r, z_k, n, threads); // rho_k = <r_0, z_k>

        if (debug) {
            std::cout << "Iteration " << iterations << ", |b - Ax|: " << GetResidualNorm(x, debug_r) << ", rho: " << rho_k << std::endl;
        }

        if (iterations == 1) {
            LinearCombination(0, p_k, 1, z_k, n, threads); // p_k = z_k
        }
        else {
            LinearCombination(rho_k / rho_prev, p_k, 1, z_k, n, threads); // p_k = z_k + beta * p_k
        }

        MatrixVectorMultiplication(ia, ja, a, n, p_k, q_k, threads); // q_k = A * p_k
        double alpha = rho_k / Dot(p_k, q_k, n, threads); // rho_k / <p_k, q_k>
        LinearCombination(1, x, alpha, p_k, n, threads); // x = x + alpha * p_k
        LinearCombination(1, r, -alpha, q_k, n, threads); // r_k = r_k - alpha * q_k

        if (rho_k < eps) {
            isConverge = true;
        }
        else {
            iterations++;
        }

        rho_prev = rho_k;
    }
    while (!isConverge);

    if (debug) {
        PrintVector(x);
    }

    TimePoint t1 = Time::now(); // останавливаем замер времени
    ms time = std::chrono::duration_cast<ms>(t1 - t0); // вычисляем разницу времени
    res = GetResidualNorm(x, debug_r);

    if (printInfo) {
        std::cout << std::right;
        std::cout << "+--------------------------------------+" << std::endl;
        std::cout << "|              Solve part              |" << std::endl;
        std::cout << "+--------------------+-----------------+" << std::endl;
        std::cout << "|   Elapsed time, ms | " << std::setw(15) << time.count() << " |" << std::endl;
        std::cout << "|           |b - Ax| | " << std::setw(15) << res << " |" << std::endl;
        std::cout << "|         Iterations | " << std::setw(15) << iterations << " |" << std::endl;
        std::cout << "+--------------------+-----------------+" << std::endl;
    }

    // освобождаем память
    delete[] r;
    delete[] m;
    delete[] z_k;
    delete[] p_k;
    delete[] q_k;
    delete[] debug_r;

    return time.count(); // возвращаем время
}