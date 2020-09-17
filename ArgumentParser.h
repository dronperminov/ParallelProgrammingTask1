#pragma once

#include <iostream>
#include <fstream>
#include <cstring>

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
