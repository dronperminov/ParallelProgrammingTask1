# Практическое задание 1. Параллельная реализация операций с сеточными данными на неструктурированной смешанной сетке 

Первое задание по курсу "параллельные вычисления" на ВМК МГУ в 2020.
### Вариант B2

## Сборка
Сборка осуществляется с помощью make файла, так что достаточно выполнить в терминале команду `make main`. При этом на Вашей системе должен быть установлен компилятор языка C++.

## Запуск
Приложение использует обработку аргументов командной строки. Для работы допускается два варианта запуска: `./main path [debug]` и `./main Nx Ny k1 k2 eps T [debug]`
В первом случае аргументы Nx, Ny, k1, k2, eps и T будут считаны из файла, находящегося по пути `path`.

### Аргументы
`path` - путь к файлу с аргументами. Ожидается, что в файле записаны 6 чисел: Nx, Ny, k1, k2, eps, T

`Nx` - количество ячеек сетки по горизонтали

`Ny` - количество ячеек сетки по вертикали

`k1` - количество прямоугольных ячеек сетки

`k2` - количество треугольных ячеек сетки

`eps` - относительная точность решения

`T` - количество потоков

`debug` - использование отладочной информации

## Производительность
Система: Windows 10, CPU: Intel Core I7-9750H 2.6GHz
Параметры сетки: k1 = 29, k2 = 37

### Nx = 1000, Ny = 1000
|  T  | Generation time, ms | Fill time, ms |
| --- |                 :-: |           :-: |
|  1  |                  52 |           284 |
|  2  |                  33 |           144 |
|  4  |                  22 |            79 |
|  8  |                  22 |            42 |
| 16  |                  22 |            37 |
| 32  |                  23 |            32 |

### Nx = 4000, Ny = 4000
|  T  | Generation time, ms | Fill time, ms |
| --- |                 :-: |           :-: |
|  1  |                 875 |          4691 |
|  2  |                 496 |          2434 |
|  4  |                 359 |          1342 |
|  8  |                 303 |           764 |
| 16  |                 272 |           600 |
| 32  |                 278 |           287 |

### Nx = 8000, Ny = 8000
|  T  | Generation time, ms | Fill time, ms |
| --- |                 :-: |           :-: |
|  1  |                3544 |         18977 |
|  2  |                2109 |          9974 |
|  4  |                1462 |          5487 |
|  8  |                1167 |          3093 |
| 16  |                1116 |          2537 |
| 32  |                1090 |          2329 |

## Примеры запуска
```bash
>./main 3 2 1 2 1e-5 32
+--------------------------------------+
|             Generate part            |
+--------------------+-----------------+
|           Vertices |              10 |
|              Edges |              32 |
| Portrait non zeros |              29 |
|   Elapsed time, ms |               5 |
+--------------------+-----------------+

+--------------------------------------+
|               Fill part              |
+--------------------+-----------------+
|   Elapsed time, ms |               0 |
+--------------------+-----------------+

+--------------------------------------+
|              Solve part              |
+--------------------+-----------------+
|   Elapsed time, ms |              20 |
|           |b - Ax| |     1.28804e-14 |
|         Iterations |              11 |
+--------------------+-----------------+
```

### То же самое, но с отладочной информацией
```bash
./main 3 2 1 2 1e-5 32 y
Parsed arguments:
Nx: 3
Ny: 2
k1: 1
k2: 2
eps: 1e-05
T: 32

Rectangles count: 2
Triangles count: 8
Vertices count: 10
Graph generation is end
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
+--------------------------------------+
|             Generate part            |
+--------------------+-----------------+
|           Vertices |              10 |
|              Edges |              32 |
| Portrait non zeros |              29 |
|   Elapsed time, ms |              25 |
+--------------------+-----------------+

v: A b
0: 0.823964     0.540302     0.283662      = 0
1: 0.823964     0.540302     0.283662     0.283662      = 0.841471
2: 0.540302     0.283662     0.540302      = 0.909297
3: 0.283662     0.540302     1.58365      0.0044257     = 0.14112
4: 0.540302     1.58365       = -0.756802
5: 0.823964     0.283662     -0.759688     = -0.958924
6: 0.283662     -0.759688    0.283662      = -0.279415
7: 0.540302     -0.759688    0.283662     0.288088      = 0.656987
8: 0.283662     0.288088     0.0044257     = 0.989358
9: 0.540302     0.288088     0.0044257     = 0.412118
+--------------------------------------+
|               Fill part              |
+--------------------+-----------------+
|   Elapsed time, ms | 0               |
+--------------------+-----------------+

Iteration 1, |b - Ax|: 2.16921, rho: 6.52225
Iteration 2, |b - Ax|: 1.48805, rho: 2.16368
Iteration 3, |b - Ax|: 1.65721, rho: 2.80552
Iteration 4, |b - Ax|: 1.32175, rho: 1.73748
Iteration 5, |b - Ax|: 0.975793, rho: 0.815536
Iteration 6, |b - Ax|: 1.05219, rho: 1.31795
Iteration 7, |b - Ax|: 0.709653, rho: 0.505578
Iteration 8, |b - Ax|: 0.458254, rho: 0.17466
Iteration 9, |b - Ax|: 1.2365, rho: 1.73587
Iteration 10, |b - Ax|: 1.55488, rho: 2.2069
Iteration 11, |b - Ax|: 1.75275e-14, rho: 3.09621e-28
x: [ -9.97411 13.0304 -10.039 23.7634 -24.5289 4.15264 3.45135 15.2134 19.7905 -20.6237 ]

+--------------------------------------+
|              Solve part              |
+--------------------+-----------------+
|   Elapsed time, ms |              77 |
|           |b - Ax| |     1.28804e-14 |
|         Iterations |              11 |
+--------------------+-----------------+
```

## Тесты
Для сборки самопроверки выполните команду `make tests && ./tests`. Если всё корректно, в консоли должен быть следующий вывод
```bash
>make tests && ./tests
Generator test for (1x1 for k = 0 and 1): OK
Generator test for (2x1 for k = 1 and 0): OK
Generator test for (2x1 for k = 1 and 1): OK
Generator test for (3x2 for k = 1 and 2): OK
Generator test for (5x2 for k = 2 and 1): OK
Generator test for (4x3 for k = 3 and 2): OK
Generator test for (3x4 for k = 1 and 0): OK
Generator test for (3x4 for k = 0 and 1): OK
Generator test for (7x5 for k = 11 and 13): OK

Fill test for n = 3: OK
Fill test for n = 5: OK
Fill test for n = 27: OK

Dot test for n = 3: OK
Dot test for n = 1: OK
Dot test for n = 2: OK
Dot test for n = 5: OK
Dot test for n = 10: OK

Linear combination test for n = 3 and a = 2, b = -3: OK
Linear combination test for n = 10 and a = -5, b = 0.5: OK

Test matrix to vector multiplication for n = 3: OK
Test matrix to vector multiplication for n = 5: OK
```

## Визуализатор
Для того, чтобы результат работы генератора был более наглядным, имеется html визуализатор. Визуализатор позволяет задавать входные аргументы и отображает сетку и полученные рёбра на ней.
Визуализатор доступен по адресу: <a href="https://programforyou.ru/tests/parallel-visualizer">programforyou.ru/tests/parallel-visualizer</a>

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