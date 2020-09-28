#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Types.h"

const int DIAGONAL_DOMINANCE_COEFFICIENT = 1.234; // коэффициент диагонального преобладания

// заполняющая функция для Aij
inline double Fa(int i, int j) {
    return cos(i*j + i + j);
}

// заполняющая функция для bi
inline double Fb(int i) {
    return sin(i);
}

class GraphFiller {
    int n; // количество вершин
    int *ia;
    int *ja;
    bool debug; // нужна ли отладка

    void PrintDebug(double *a, double *b) const; // вывод отладочных значений
public:
    GraphFiller(int n, int *ia, int *ja, bool debug);

    int Fill(double *&a, double *&b, bool showInfo = true) const; // заполнение
};