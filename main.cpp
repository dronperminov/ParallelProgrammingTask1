#include <iostream>
#include <fstream>
#include <cstring>
#include "ArgumentParser.h"
#include "GraphGenerator.h"
#include "GraphFiller.h"
#include "ConjugateGradientSolver.h"

using namespace std;

// вывод информационного сообщения
void Help() {
    cout << "Usage: ./main path [debug] or ./main Nx Ny k1 k2 eps T [debug]" << endl;
    cout << endl;
    cout << "Arguments description:" << endl;
    cout << "path  - path to file with arguments" << endl;
    cout << "Nx    - number of columns in grid (natural)" << endl;
    cout << "Ny    - number of rows in grid (natural)" << endl;
    cout << "k1    - number of non divisible cells (integer >= 0)" << endl;
    cout << "k2    - number of divisible cells (integer >= 0)" << endl;
    cout << "eps   - relative solution accuracy (real)" << endl;
    cout << "T     - number of threads (natural)" << endl;
    cout << "debug - need print debug info or not (y/n)" << endl;
}

void Solve(const ArgumentParser& parser) {
    // входные аргументы
    int nx = parser.GetNx();
    int ny = parser.GetNy();
    int k1 = parser.GetK1();
    int k2 = parser.GetK2();
    double eps = parser.GetEps();
    int threads = parser.GetThreads();
    bool debug = parser.GetDebug();

    // выходные аргументы
    int n = 0;
    int *ia = NULL;
    int *ja = NULL;

    GraphGenerator generator(nx, ny, k1, k2, threads, debug);
    generator.Generate(n, ia, ja); // запускаем генерацию

    double *a = NULL;
    double *b = NULL;

    GraphFiller filler(n, ia, ja, threads, debug);
    filler.Fill(a, b); // заполняем массив

    double *x = NULL;
    int iterations;
    double res;

    ConjugateGradientSolver solver(n, ia, ja, a, b, eps, threads, debug);
    solver.Solve(x, iterations, res);

    // освобождаем выделенную память
    delete[] ia;
    delete[] ja;
    delete[] a;
    delete[] b;
    delete[] x;
}

int main(int argc, char **argv) {
    // если аргументов нет или запустили вызов сообщения
    if (argc == 1 || (argc == 2 && !strcmp(argv[1], "--help"))) {
        Help();
        return 0;
    }

    ArgumentParser parser;

    if (!parser.ParseArgs(argc, argv))
        return -1;

    if (parser.GetDebug())
        parser.PrintArguments();

    Solve(parser);
}