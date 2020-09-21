#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Time.h"

const int DIAGONAL_DOMINANCE_COEFFICIENT = 1.234; // коэффициент диагонального преобладания

class GraphFiller {
    int n; // количество вершин
    int *ia;
    int *ja;
    int threads; // количество потоков
    bool debug; // нужна ли отладка

    void PrintDebug(double *a, double *b) const; // вывод отладочных значений
public:
    GraphFiller(int n, int *ia, int *ja, int threads, bool debug);

    void Fill(double *&a, double *&b) const; // заполнение
};