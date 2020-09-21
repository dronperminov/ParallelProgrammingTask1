#include "GraphGenerator.h"

// проверка, что вершина треугольная
bool GraphGenerator::IsTriangleVertex(int v) const {
    return v % (k1 + 2 * k2) >= k1;
}

// проверка, что треугольная вершина сверху
bool GraphGenerator::IsUpVertex(int v) const {
    int pos = v % (k1 + 2 * k2);
    return pos >= k1 && (pos - k1) & 1;
}

// проверка, что треугольная вершина снизу
bool GraphGenerator::IsDownVertex(int v) const {
    int pos = v % (k1 + 2 * k2);
    return pos >= k1 && !((pos - k1) & 1);
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

    if (mod < k1) {
        vertex += mod;
    }
    else {
        vertex += mod * 2 - k1;
    }

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

// формирование рёбер
LinkInfo* GraphGenerator::MakeEdges(int n) const {
    LinkInfo *edges = new LinkInfo[n]; // создаём список смежности

    #pragma omp parallel for num_threads(threads)
    for (int v = 0; v < n; v++) {
        int index = Vertex2Index(v);
        int x = index % nx;
        int y = index / nx;

        edges[v].count = 0;

        // соседняя сверху, если не нижнетреугольная ячейка
        if (y > 0 && !IsDownVertex(v))
            edges[v].vertices[edges[v].count++] = Index2Vertex((y - 1) * nx + x);

        // соседняя слева
        if (x > 0 || (x == 0 && IsUpVertex(v)))
            edges[v].vertices[edges[v].count++] = v - 1;

        edges[v].vertices[edges[v].count++] = v;

        // соседняя справа
        if (x < nx - 1 || (x == nx - 1 && IsDownVertex(v)))
            edges[v].vertices[edges[v].count++] = v + 1;

        // соседняя снизу, если не верхнетреугольная ячейка
        if (y < ny - 1 && !IsUpVertex(v)) {
            int vertex = Index2Vertex((y + 1) * nx + x);

            if (IsTriangleVertex(vertex))
                vertex++;

            edges[v].vertices[edges[v].count++] = vertex;
        }
    }

    return edges;
}

// вывод рёбер
void GraphGenerator::PrintEdges(LinkInfo *edges, int n) const {
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
void GraphGenerator::PrintArray(int *array, int n, const char *message) const {
    std::cout << message << ": [ ";

    for (int i = 0; i < n; i++)
        std::cout << array[i] << " ";

    std::cout << "]" << std::endl;
}

// вывод сводной информации
void GraphGenerator::PrintInfo(int n, int *ia, int *ja, const ms &time) const {
    std::cout << "+--------------------+-----------------+" << std::endl;
    std::cout << "|      Feature       |      Value      |" << std::endl;
    std::cout << "+--------------------+-----------------+" << std::endl;
    std::cout << "|           vertices | " << std::setw(15) << n << " |" << std::endl;
    std::cout << "|              edges | " << std::setw(15) << ia[n] << " |" << std::endl;
    std::cout << "| portrait non zeros | " << std::setw(15) << GetNotZeroCount(ja, ia[n]) << " |" << std::endl;
    std::cout << "|   elapsed time, ms | " << std::setw(15) << time.count() << " |" << std::endl;
    std::cout << "+--------------------+-----------------+" << std::endl;
}

// формирование массива IA
int* GraphGenerator::MakeIA(LinkInfo *edges, int n) const {
    int *ia = new int[n + 1];

    ia[0] = 0;

    for (int i = 0; i < n; i++)
        ia[i + 1] = ia[i] + edges[i].count;

    return ia;
}

// формирование массива JA
int* GraphGenerator::MakeJA(LinkInfo *edges, int n, int *ia) const {
    int *ja = new int[ia[n]];

    #pragma omp parallel for num_threads(threads)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < edges[i].count; j++)
            ja[ia[i] + j] = edges[i].vertices[j];

    return ja;
}

// получение количества ненулевых элементов
int GraphGenerator::GetNotZeroCount(int *array, int n) const {
    int count = 0;

    for (int i = 0; i < n; i++)
        if (array[i])
            count++;

    return count;
}

GraphGenerator::GraphGenerator(int nx, int ny, int k1, int k2, int threads, bool debug) {
    this->nx = nx;
    this->ny = ny;

    this->k1 = k1;
    this->k2 = k2;

    this->threads = threads;
    this->debug = debug;
}

void GraphGenerator::Generate(int &n, int *&ia, int *&ja, bool showInfo) {
    TimePoint t0 = Time::now(); // запускаем замер времени

    n = GetVerticesCount(); // получаем количество вершин
    LinkInfo *edges = MakeEdges(n); // формируем рёбра
    ia = MakeIA(edges, n); // заполняем массив IA
    ja = MakeJA(edges, n, ia); // заполняем массив JA

    TimePoint t1 = Time::now(); // останавливаем замер времени
    ms time = std::chrono::duration_cast<ms>(t1 - t0); // вычисляем разницу времени

    std::cout << "Graph generation is end" << std::endl;

    if (debug) {
        std::cout << "Edges count: " << ia[n] << std::endl;
        PrintEdges(edges, n); // выводим рёбра

        std::cout << "N: " << n << std::endl;
        PrintArray(ia, n + 1, "IA"); // выводим массив IA
        PrintArray(ja, ia[n], "JA"); // выводим массив JA
    }

    if (showInfo) {
        PrintInfo(n, ia, ja, time); // выводим сводную информацию
    }

    delete[] edges; // освобождаем память
}