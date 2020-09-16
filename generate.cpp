#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class ArgumentParser {
    int nx; // количество столбцов сетки
    int ny; // количество строк сетки
    int k1; // количество клеток без деления
    int k2; // количество клеток с делением
    bool debug; // нужна ли отладка

    bool IsInteger(const char *s) const; // проверка, что строка является целым числом

    void ParseDebug(char *arg); // парсинг отладки
    void ParseFromFile(const char *path); // парсинг из файла
    void ParseFromArgv(int argc, char **argv); // парсинг из аргументов
public:
    ArgumentParser(int argc, char **argv);

    // получение аргументов
    int GetNx() const;
    int GetNy() const;
    int GetK1() const;
    int GetK2() const;
    bool GetDebug() const;

    void PrintArguments() const; // вывод аргументов
};

// проверка, что строка является целым числом
bool ArgumentParser::IsInteger(const char *s) const {
    for (int i = 0; s[i]; i++)
        if (s[i] < '0' || s[i] > '9')
            return false;

    return s[0] != '\0'; // целое число, если строка не пуста
}

// парсинг отладки
void ArgumentParser::ParseDebug(char *arg) {
    if (strcmp(arg, "y") && strcmp(arg, "n"))
        throw "debug parameter is invalid";

    debug = !strcmp(arg, "y");
}

// парсинг из файла
void ArgumentParser::ParseFromFile(const char *path) {
    ifstream f(path); // открываем файл на чтение

    if (!f) // печаль, если файл не открылся
        throw "unable to open input file";

    f >> nx >> ny >> k1 >> k2;

    if (nx < 1)
        throw "Nx parameter in file is invalid";

    if (ny < 1)
        throw "Ny parameter in file is invalid";

    if (k1 < 1)
        throw "k1 parameter in file is invalid";

    if (k2 < 1)
        throw "k2 parameter in file is invalid";

    f.close(); // закрываем файл
}

// парсинг из аргументов
void ArgumentParser::ParseFromArgv(int argc, char **argv) {
    if (!IsInteger(argv[1]))
        throw "Nx parameter is not integer";

    if (!IsInteger(argv[2]))
        throw "Ny parameter is not integer";

    if (!IsInteger(argv[3]))
        throw "k1 parameter is not integer";

    if (!IsInteger(argv[4]))
        throw "k2 parameter is not integer";

    // парсим в настоящие аргументы
    nx = atoi(argv[1]);
    ny = atoi(argv[2]);
    k1 = atoi(argv[3]);
    k2 = atoi(argv[4]);
}

ArgumentParser::ArgumentParser(int argc, char **argv) {
    if (argc < 2 || argc > 6) // если некорректное количество аргументов
        throw "invalid arguments. Try ./generate --help for usage";

    // если запуск вида ./generate path [debug]
    if (argc == 2 || argc == 3) {
        ParseFromFile(argv[1]);
    }
    else {
        ParseFromArgv(argc, argv);
    }

    if (argc == 3) {
        ParseDebug(argv[2]);
    }
    else if (argc == 6) {
        ParseDebug(argv[5]);
    }
    else {
        debug = false;
    }
}

int ArgumentParser::GetNx() const {
    return nx;
}

int ArgumentParser::GetNy() const {
    return ny;
}

int ArgumentParser::GetK1() const {
    return k1;
}

int ArgumentParser::GetK2() const {
    return k2;
}

bool ArgumentParser::GetDebug() const {
    return debug;
}

// вывод аргументов
void ArgumentParser::PrintArguments() const {
    cout << "Parsed arguments:" << endl;
    cout << "Nx: " << nx << endl;
    cout << "Ny: " << ny << endl;
    cout << "k1: " << k1 << endl;
    cout << "k2: " << k2 << endl;
}

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
void Generate(int nx, int ny, int k1, int k2, bool debug) {

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

        int nx = parser.GetNx();
        int ny = parser.GetNy();
        int k1 = parser.GetK1();
        int k2 = parser.GetK2();
        bool debug = parser.GetDebug();

        Generate(nx, ny, k1, k2, debug); // запускаем генерацию
    }
    catch (const char *error) {
        cout << "Error: " << error << endl;
        return -1;
    }
}