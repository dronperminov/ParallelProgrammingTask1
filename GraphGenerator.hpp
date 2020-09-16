#pragma once

#include <iostream>

struct LinkInfo {
    int count; // количество элементов
    int vertices[4]; // связные вершины
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

    void PrintEdges(LinkInfo *edges, int n); // вывод рёбер
    void PrintArray(int *array, int n, const char *message); // вывод массива
public:
    GraphGenerator(int nx, int ny, int k1, int k2, bool debug);

    void Generate(int &n, int *&ia, int *&ja);
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

// формирование рёбер для треугольных вершин
void GraphGenerator::MakeTriangleEdges(int v, LinkInfo *edges) {
    int index = Vertex2Index(v);
    int vx = index % nx;
    int vy = index / nx;

    if (vy > 0 && IsUpVertex(v))
        edges[v].vertices[edges[v].count++] = Index2Vertex((vy - 1) * nx + vx);

    if (vx > 0 || (vx == 0 && IsUpVertex(v)))
        edges[v].vertices[edges[v].count++] = v - 1;

    if (vx < nx - 1 || (vx == nx - 1 && !IsUpVertex(v)))
        edges[v].vertices[edges[v].count++] = v + 1;


    if (vy < ny - 1 && !IsUpVertex(v)) {
        int vertex = Index2Vertex((vy + 1) * nx + vx);

        if (IsTriangleVertex(vertex))
            vertex++;

        edges[v].vertices[edges[v].count++] = vertex;
    }
}

// формирование рёбер для прямоугольных вершин
void GraphGenerator::MakeRectangleEdges(int v, LinkInfo *edges) {
    int dx[4] = { 0, -1, 1, 0 };
    int dy[4] = { -1, 0, 0, 1 };

    int index = Vertex2Index(v);
    int vx = index % nx;
    int vy = index / nx;

    for (int k = 0; k < 4; k++) {
        int x = vx + dx[k];
        int y = vy + dy[k];

        if (x < 0 || x >= nx || y < 0 || y >= ny)
            continue;

        int index2 = y * nx + x;
        int vertex = Index2Vertex(index2);

        if ((dx[k] == -1 || dy[k] == 1) && IsTriangleVertex(vertex))
            vertex++;

        edges[v].vertices[edges[v].count++] = vertex;
    }
}

// формирование рёбер
LinkInfo* GraphGenerator::MakeEdges(int n) {
    LinkInfo *edges = new LinkInfo[n]; // создаём список смежности

    for (int v = 0; v < n; v++) {
        edges[v].count = 0;

        if (IsTriangleVertex(v)) {
            MakeTriangleEdges(v, edges);
        }
        else {
            MakeRectangleEdges(v, edges);
        }
    }

    return edges;
}

// вывод рёбер
void GraphGenerator::PrintEdges(LinkInfo *edges, int n) {
    std::cout << std::endl;
    std::cout << "Edges list: " << std::endl;

    for (int i = 0; i < n; i++) {
        std::cout << i << " -> [ ";

        for (int j = 0; j < edges[i].count; j++)
            std::cout << edges[i].vertices[j] << " ";

        std::cout << "]" << std::endl;
    }
}

// вывод массива
void GraphGenerator::PrintArray(int *array, int n, const char *message) {
    std::cout << message << ": [ ";

    for (int i = 0; i < n; i++)
        std::cout << array[i] << " ";

    std::cout << "]" << std::endl;
}

// формирование массива IA
int* GraphGenerator::MakeIA(LinkInfo *edges, int n) {
    int *ia = new int[n + 1];

    ia[0] = 0;

    for (int i = 0; i < n; i++)
        ia[i + 1] = ia[i] + edges[i].count;

    return ia;
}

// формирование массива JA
int* GraphGenerator::MakeJA(LinkInfo *edges, int n, int edgesCount) {
    int *ja = new int[edgesCount];
    int index = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < edges[i].count; j++)
            ja[index++] = edges[i].vertices[j];

    return ja;
}

GraphGenerator::GraphGenerator(int nx, int ny, int k1, int k2, bool debug) {
    this->nx = nx;
    this->ny = ny;

    this->k1 = k1;
    this->k2 = k2;

    this->debug = debug;
}

void GraphGenerator::Generate(int &n, int *&ia, int *&ja) {
    n = GetVerticesCount(); // получаем количество вершин
    LinkInfo *edges = MakeEdges(n); // формируем рёбра
    ia = MakeIA(edges, n); // заполняем массив IA
    ja = MakeJA(edges, n, ia[n]); // заполняем массив JA

    if (debug) {
        std::cout << "Edges count: " << ia[n] << std::endl;
        PrintEdges(edges, n); // выводим рёбра
    }

    std::cout << "N: " << n << std::endl;
    PrintArray(ia, n + 1, "IA"); // выводим массив IA
    PrintArray(ja, ia[n], "JA"); // выводим массив JA

    delete[] edges; // освобождаем память
}