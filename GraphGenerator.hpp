#pragma once

#include <iostream>

class GraphGenerator {
    int nx;
    int ny;
    int k1;
    int k2;

    bool IsTriangleVertex(int v) const;
    bool IsUpVertex(int v) const;

    int Vertex2Index(int v) const;
    int Index2Vertex(int index) const;
public:
    GraphGenerator(int nx, int ny, int k1, int k2);
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

GraphGenerator::GraphGenerator(int nx, int ny, int k1, int k2) {
    this->nx = nx;
    this->ny = ny;
    this->k1 = k1;
    this->k2 = k2;
}
