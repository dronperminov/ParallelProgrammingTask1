#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::time_point<Time> TimePoint;
typedef std::chrono::milliseconds ms;

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

    bool IsTriangleVertex(int v) const; // проверка, что вершина треугольная
    bool IsUpVertex(int v) const; // проверка, что треугольная вершина сверху

    int Vertex2Index(int v) const; // получение индекса вершины на сетке
    int Index2Vertex(int index) const; // получение вершины по индексу

    int GetVerticesCount() const; // вычисление количества вершин

    void MakeTriangleEdges(int v, LinkInfo *edges);
    void MakeRectangleEdges(int v, LinkInfo *edges);
    LinkInfo* MakeEdges(int n); // формирование рёбер

    int* MakeIA(LinkInfo *edges, int n); // формирование массива IA
    int* MakeJA(LinkInfo *edges, int n, int edgesCount); // формирование массива JA
    int GetNotZeroCount(int *array, int n); // получение количества ненулевых элементов

    void PrintEdges(LinkInfo *edges, int n); // вывод рёбер
    void PrintArray(int *array, int n, const char *message); // вывод массива
    void PrintInfo(int n, int *ia, int *ja, const ms &time); // вывод сводной информации
public:
    GraphGenerator(int nx, int ny, int k1, int k2, bool debug);

    void Generate(int &n, int *&ia, int *&ja);
};
