#include <iostream>
#include <fstream>
#include <cstring>
#include "ArgumentParser.h"
#include "GraphGenerator.h"
#include "GraphFiller.h"

using namespace std;

// вывод информационного сообщения
void Help() {
    cout << "Usage: ./generate path [debug] or ./generate Nx Ny k1 k2 T [debug]" << endl;
    cout << "Args description:" << endl;
    cout << "path  - path to file for read for args" << endl;
    cout << "Nx    - number of columns in grid (natural)" << endl;
    cout << "Ny    - number of rows in grid (natural)" << endl;
    cout << "k1    - number of non divisible cells (integer >= 0)" << endl;
    cout << "k2    - number of divisible cells (integer >= 0)" << endl;
    cout << "T     - number of threads (natural)" << endl;
    cout << "debug - need print debug info or not (y/n)" << endl;
}

int main(int argc, char **argv) {
    // если аргументов нет или запустили вызов сообщения
    if (argc == 1 || (argc == 2 && !strcmp(argv[1], "--help"))) {
        Help();
        return 0;
    }

    try {
        ArgumentParser parser(argc, argv);

        if (parser.GetDebug())
            parser.PrintArguments();

        // входные аргументы
        int nx = parser.GetNx();
        int ny = parser.GetNy();
        int k1 = parser.GetK1();
        int k2 = parser.GetK2();
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
        filler.Fill(a, b);
    }
    catch (const char *error) {
        cout << "Error: " << error << endl;
        return -1;
    }
}