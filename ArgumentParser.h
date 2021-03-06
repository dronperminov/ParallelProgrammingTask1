#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include "Types.h"

class ArgumentParser {
    int nx; // количество столбцов сетки
    int ny; // количество строк сетки
    int k1; // количество клеток без деления
    int k2; // количество клеток с делением
    double eps; // точность
    int threads; // количество потоков
    int debug; // режим отладки

    bool IsInteger(const char *s) const; // проверка, что строка является целым числом
    bool IsReal(const char *s) const; // проверка, что строка является вещественным числом

    bool ParseDebug(char *arg); // парсинг отладки
    bool ParseFromFile(const char *path); // парсинг из файла
    bool ParseFromArgv(int argc, char **argv); // парсинг из аргументов
public:
    bool ParseArgs(int argc, char **argv);

    // получение аргументов
    int GetNx() const;
    int GetNy() const;
    int GetK1() const;
    int GetK2() const;
    double GetEps() const;
    int GetThreads() const;
    int GetDebug() const;

    void PrintArguments() const; // вывод аргументов
};
