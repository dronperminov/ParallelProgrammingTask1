#pragma once

#include <iostream>
#include <iomanip>
#include <omp.h>
#include "Types.h"

struct LinkInfo {
    int count; // количество элементов
    int vertices[5]; // связные вершины
};

class GraphGenerator {
    int nx;
    int ny;
    int k1;
    int k2;
    bool debug;
    int threads;

    bool IsTriangleVertex(int v) const; // проверка, что вершина треугольная
    bool IsUpVertex(int v) const; // проверка, что треугольная вершина сверху
    bool IsDownVertex(int v) const; // проверка, что треугольная вершина снизу

    int Vertex2Index(int v) const; // получение индекса вершины на сетке
    int Index2Vertex(int index) const; // получение вершины по индексу

    int GetVerticesCount() const; // вычисление количества вершин

    LinkInfo* MakeEdges(int n) const; // формирование рёбер
    int* MakeIA(LinkInfo *edges, int n) const; // формирование массива IA
    int* MakeJA(LinkInfo *edges, int n, int *ia) const; // формирование массива JA
    int GetNotZeroCount(int *array, int n) const; // получение количества ненулевых элементов

    void PrintEdges(LinkInfo *edges, int n) const; // вывод рёбер
    void PrintArray(int *array, int n, const char *message) const; // вывод массива
    void PrintInfo(int n, int *ia, int *ja, const ms &time) const; // вывод сводной информации
public:
    GraphGenerator(int nx, int ny, int k1, int k2, bool debug, int threads);

    int Generate(int &n, int *&ia, int *&ja, bool showInfo = true);
};
