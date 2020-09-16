# Практическое задание 1. Параллельная реализация операций с сеточными данными на неструктурированной смешанной сетке 

Первое задание по курсу "параллельные вычисления" на ВМК МГУ в 2020.
### Вариант B2

## Сборка
Сборка осуществляется с помощью make файла, так что достаточно выполнить в терминале команду `make`. При этом на Вашей системе должен быть установлен компилятор языка C++.

## Запуск
Приложение использует обработку аргументов командной строки. Для работы допускается два варианта запуска: `./generate path [debug]` и `./generate Nx Ny k1 k2 [debug]`
В первом случае аргументы Nx, Ny, k1 и k2 будут считаны из файла, находящегося по пути `path`.

### Аргументы
`path` - путь к файлу с аргументами. Ожидается, что в файле записаны 4 числа: Nx, Ny, k1, k2

`Nx` - количество ячеек сетки по горизонтали

`Ny` - количество ячеек сетки по вертикали

`k1` - количество прямоугольных ячеек сетки

`k2` - количество треугольных ячеек сетки

`debug` - использование отладочной информации

## Примеры запуска
```bash
>./generate 3 2 1 2
N: 10
IA: [ 0 3 7 10 14 16 19 22 26 29 32 ]
JA: [ 0 1 5 0 1 2 7 1 2 3 2 3 4 9 3 4 0 5 6 5 6 7 1 6 7 8 7 8 9 3 8 9 ]
```

### То же самое, но с отладочной информацией
```bash
generate.exe 3 2 1 2 y
Parsed arguments:
Nx: 3
Ny: 2
k1: 1
k2: 2

Rectangles count: 2
Triangles count: 8
Vertices count: 10
Edges count: 32

Edges list:
0 -> [ 0 1 5 ]
1 -> [ 0 1 2 7 ]
2 -> [ 1 2 3 ]
3 -> [ 2 3 4 9 ]
4 -> [ 3 4 ]
5 -> [ 0 5 6 ]
6 -> [ 5 6 7 ]
7 -> [ 1 6 7 8 ]
8 -> [ 7 8 9 ]
9 -> [ 3 8 9 ]
N: 10
IA: [ 0 3 7 10 14 16 19 22 26 29 32 ]
JA: [ 0 1 5 0 1 2 7 1 2 3 2 3 4 9 3 4 0 5 6 5 6 7 1 6 7 8 7 8 9 3 8 9 ]
```

## Визуализатор
Для того, чтобы результат работы генератора был более наглядным, имеется html визуализатор. Визуализатор позволяет задавать входные аргументы и отображает сетку и полученные рёбра на ней.

<img src='https://github.com/dronperminov/ParallelProgrammingTask1/blob/master/examples/visualizer.png' />

## Примеры сеток (результат работы визуализатора)

<table>
  <tr>
    <td width='50%'><img src='https://github.com/dronperminov/ParallelProgrammingTask1/blob/master/examples/example1.png' /></td>
    <td width='50%'><img src='https://github.com/dronperminov/ParallelProgrammingTask1/blob/master/examples/example2.png' /></td>
  </tr>
  
  <tr>
    <td width='50%'><img src='https://github.com/dronperminov/ParallelProgrammingTask1/blob/master/examples/example3.png' /></td>
    <td width='50%'><img src='https://github.com/dronperminov/ParallelProgrammingTask1/blob/master/examples/example4.png' /></td>
  </tr>
</table>