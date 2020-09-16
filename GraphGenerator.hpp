#pragma once

#include <iostream>

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
public:
    GraphGenerator(int nx, int ny, int k1, int k2, bool debug);

    void Generate();
};

// проверка, что вершина треугольная
bool GraphGenerator::IsTriangleVertex(int v) const {
    return v % (k1 + 2 * k2) >= k1;
}

// проверка, что треугольная вершина сверху
bool GraphGenerator::IsUpVertex(int v) const {
    return (v % (k1 + 2 * k2) - k1) % 2 == 1;
}

// получение индекса вершины на сетке
int GraphGenerator::Vertex2Index(int v) const {
    int div = v / (k1 + 2 * k2);
    int mod = v % (k1 + 2 * k2);
    int pos = div * (k1 + k2);

    if (mod < k1) {
        pos += mod;
    }
    else {
        pos += (mod + k1) / 2;
    }

    return pos;
}

// получение вершины по индексу
int GraphGenerator::Index2Vertex(int index) const {
    int div = index / (k1 + k2);
    int mod = index % (k1 + k2);
    int vertex = div * (k1 + 2 * k2);

    if (mod < k1)
        vertex += mod;
    else
        vertex += mod * 2 - k1;

    return vertex;
}

// вычисление количества вершин
int GraphGenerator::GetVerticesCount() const {
    int totalCells = nx * ny; // общее количество ячеек без деления
    int intPart = totalCells / (k1 + k2); // полноценно разбиваемая часть ячеек
    int modPart = totalCells % (k1 + k2); // сколько ячеек останется после целого разбиения

    int n = intPart * (k1 + 2 * k2); // как минимум вот столько вершин
    int rectangles = intPart * k1; // количество прямоугольников
    int triangles = intPart * 2 * k2; // количество треугольников

    // если ещё остались клетки
    if (modPart > 0) {
        int n1 = modPart > k1 ? k1 : modPart; // количество клеток без разбиения
        int n2 = modPart - n1; // количество клеток с разбиением

        n += n1 + n2 * 2; // добавляем оставшиеся клетки
        rectangles += n1;
        triangles += n2 * 2;
    }

    if (debug) {
        std::cout << std::endl;
        std::cout << "Rectangles count: " << rectangles << std::endl;
        std::cout << "Triangles count: " << triangles << std::endl;
        std::cout << "Vertices count: " << n << std::endl;
    }

    return n;
}

GraphGenerator::GraphGenerator(int nx, int ny, int k1, int k2, bool debug) {
    this->nx = nx;
    this->ny = ny;

    this->k1 = k1;
    this->k2 = k2;

    this->debug = debug;
}

void GraphGenerator::Generate() {
    int n = GetVerticesCount();
}