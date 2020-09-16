#include <iostream>
#include <fstream>
#include <cstring>
#include "ArgumentParser.hpp"
#include "GraphGenerator.hpp"

using namespace std;

// вывод информационного сообщения
void Help() {
    cout << "Usage: ./generate path [debug] or ./generate Nx Ny k1 k2 [debug]" << endl;
    cout << "Args description:" << endl;
    cout << "path  - path to file for read for args" << endl;
    cout << "Nx    - number of columns in grid (natural)" << endl;
    cout << "Ny    - number of rows in grid (natural)" << endl;
    cout << "k1    - number of non divisible cells (natural)" << endl;
    cout << "k2    - number of divisible cells (natural)" << endl;
    cout << "debug - need print debug info or not (y/n)" << endl;
}

// генерация
void Generate(int nx, int ny, int k1, int k2, bool debug, int &n, int *&ia, int *&ja) {
    GraphGenerator generator(nx, ny, k1, k2, debug);
    generator.Generate(n, ia, ja);
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
        bool debug = parser.GetDebug();

        // выходные аргументы
        int n = 0;
        int *ia = NULL;
        int *ja = NULL;

        Generate(nx, ny, k1, k2, debug, n, ia, ja); // запускаем генерацию
    }
    catch (const char *error) {
        cout << "Error: " << error << endl;
        return -1;
    }
}