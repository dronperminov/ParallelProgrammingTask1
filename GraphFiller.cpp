#include "GraphFiller.h"

GraphFiller::GraphFiller(int n, int *ia, int *ja, int threads, bool debug) {
    this->n = n;
    this->ia = ia;
    this->ja = ja;

    this->threads = threads;
    this->debug = debug;
}

// вывод отладочных значений
void GraphFiller::PrintDebug(double *a, double *b) const {
    std::cout << "v: A b" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << i << ": ";

        for (int j = ia[i]; j < ia[i + 1]; j++)
            std::cout << std::left << std::setw(12) << a[ja[j]] << " ";

        std::cout << " = " << b[i] << "" << std::endl;
    }
}

// заполнение
void GraphFiller::Fill(double *&a, double *&b) const {
    TimePoint t0 = Time::now(); // запускаем замер времени

    a = new double[ia[n]];
    b = new double[n];

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++) {
        double sum = 0;
        int diagIndex = -1;

        for (int index = ia[i]; index < ia[i + 1]; index++) {
            int j = ja[index];

            if (i != j) {
                a[index] = cos(i*j + i + j); // a_ij
                sum += fabs(a[index]); // наразиваем сумму внедиагональных элементов
            }
            else {
                diagIndex = index;
            }
        }

        a[diagIndex] = DIAGONAL_DOMINANCE_COEFFICIENT * sum;
        b[i] = sin(i);
    }

    TimePoint t1 = Time::now(); // останавливаем замер времени
    ms time = std::chrono::duration_cast<ms>(t1 - t0); // вычисляем разницу времени

    std::cout << std::endl << "Graph filling is end" << std::endl;
    
    if (debug) {
        PrintDebug(a, b);
    }

    std::cout << "Elapsed time: " << time.count() << "ms" << std::endl;
}