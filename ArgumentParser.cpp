#include "ArgumentParser.h"

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
    std::ifstream f(path); // открываем файл на чтение

    if (!f) // печаль, если файл не открылся
        throw "unable to open input file";

    if (!(f >> nx >> ny >> k1 >> k2 >> threads))
        throw "unable to read from file";

    if (nx < 1)
        throw "Nx parameter in file is invalid";

    if (ny < 1)
        throw "Ny parameter in file is invalid";

    if (k1 < 0)
        throw "k1 parameter in file is invalid";

    if (k2 < 0)
        throw "k2 parameter in file is invalid";

    if (k1 + k2 == 0)
        throw "k1 and k2 == 0";

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

    if (!IsInteger(argv[5]))
        throw "threads parameter is not integer";

    // парсим в настоящие аргументы
    nx = atoi(argv[1]);
    ny = atoi(argv[2]);
    k1 = atoi(argv[3]);
    k2 = atoi(argv[4]);
    threads = atoi(argv[5]);

    if (nx == 0 || ny == 0)
        throw "invalid value of Nx or Ny ";

    if (k1 + k2 == 0)
        throw "k1 and k2 == 0";

    if (threads == 0)
        throw "threads is zero";
}

ArgumentParser::ArgumentParser(int argc, char **argv) {
    if (argc < 2 || argc == 4 || argc == 5 || argc > 7) // если некорректное количество аргументов
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
    else if (argc == 7) {
        ParseDebug(argv[6]);
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

int ArgumentParser::GetThreads() const {
    return threads;
}

bool ArgumentParser::GetDebug() const {
    return debug;
}

// вывод аргументов
void ArgumentParser::PrintArguments() const {
    std::cout << "Parsed arguments:" << std::endl;
    std::cout << "Nx: " << nx << std::endl;
    std::cout << "Ny: " << ny << std::endl;
    std::cout << "k1: " << k1 << std::endl;
    std::cout << "k2: " << k2 << std::endl;
    std::cout << " T: " << threads << std::endl;
}