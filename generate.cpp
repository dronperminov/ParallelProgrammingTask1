#include <iostream>
#include <fstream>
#include <cstring>
#include "ArgumentParser.hpp"

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
    int totalCells = nx * ny; // общее количество ячеек без деления
    int intPart = totalCells / (k1 + k2); // полноценно разбиваемая часть ячеек
    int modPart = totalCells % (k1 + k2); // сколько ячеек останется после целого разбиения

    n = intPart * (k1 + 2 * k2); // как минимум вот столько вершин

    if (debug)
        cout << "Total cells: " << totalCells << endl;

    // если ещё остались клетки
    if (modPart > 0) {
        int n1 = modPart > k1 ? k1 : modPart; // количество клеток без разбиения
        int n2 = modPart - n1; // количество клеток с разбиением

        n += n1 + n2 * 2; // добавляем оставшиеся клетки

        if (debug) {
            cout << "Normal vertices: " << n << " (" << intPart << " of k1 and " << intPart * 2 << " of k2)" << endl;
            cout << "Stay " << modPart << " cells" << endl;
            cout << "Addition vertices: " << n1 << " of k1 and " << n2*2 << " of k2" << endl;
        }
    }

    if (debug)
        cout << "Total vertices: " << n << endl;
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