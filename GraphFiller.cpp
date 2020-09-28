#include "GraphFiller.h"

GraphFiller::GraphFiller(int n, int *ia, int *ja, bool debug) {
    this->n = n;
    this->ia = ia;
    this->ja = ja;

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
int GraphFiller::Fill(double *&a, double *&b, bool showInfo) const {
    TimePoint t0 = Time::now(); // запускаем замер времени

    a = new double[ia[n]];
    b = new double[n];

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        double sum = 0;
        int diagIndex = -1;

        for (int index = ia[i]; index < ia[i + 1]; index++) {
            int j = ja[index];

            if (i != j) {
                a[index] = Fa(i, j); // a_ij
                sum += fabs(a[index]); // наразиваем сумму внедиагональных элементов
            }
            else {
                diagIndex = index;
            }
        }

        a[diagIndex] = DIAGONAL_DOMINANCE_COEFFICIENT * sum;
        b[i] = Fb(i);
    }

    TimePoint t1 = Time::now(); // останавливаем замер времени
    ms time = std::chrono::duration_cast<ms>(t1 - t0); // вычисляем разницу времени
    
    if (debug) {
        PrintDebug(a, b);
    }

    if (showInfo) {
        std::cout << "+--------------------------------------+" << std::endl;
        std::cout << "|               Fill part              |" << std::endl;
        std::cout << "+--------------------+-----------------+" << std::endl;
        std::cout << "|   Elapsed time, ms | " << std::setw(15) << time.count() << " |" << std::endl;
        std::cout << "+--------------------+-----------------+" << std::endl;
        std::cout << std::endl;
    }

    return time.count(); // возвращаем время
}