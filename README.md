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

`debug` - использование отладочной информации (`f` - полная отладка, `s` - вывод значений невязки на итерациях решателя, `n` - без отладки)

## Производительность
Система 1: Ubuntu 18, CPU: Intel Core I7-8700 3.2GHz, 6 cores
Ситсема 2: Polus, CPU: 4.023GHz, 160 cores
Параметры сетки: k1 = 29, k2 = 37

### Nx = 500, Ny = 500 (Intel Core I7-8700):
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |           8.6 |           47.3 |         159.5 |
|     2 |             5 |             24 |          96.5 |
|     4 |             3 |             12 |          80.2 |
|     8 |             2 |              8 |          79.6 |
|    16 |             2 |              8 |          89.2 |
|    32 |             2 |            6.4 |            97 |

### Nx = 500, Ny = 500 (Polus):
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |          10.1 |             96 |           266 |
|     2 |           6.1 |             48 |           128 |
|     4 |           4.2 |             25 |          84.7 |
|     8 |           3.1 |           12.1 |          42.2 |
|    16 |           3.1 |              7 |          29.5 |
|    32 |             3 |            3.5 |          19.9 |
|    64 |           3.1 |              3 |            22 |
|   128 |           3.5 |            2.2 |          27.3 |

### Nx = 1000, Ny = 1000 (Intel Core I7-8700):
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |          36.5 |          192.8 |         857.4 |
|     2 |          23.4 |             99 |         571.7 |
|     4 |            14 |             51 |         523.4 |
|     8 |          11.6 |             34 |         549.8 |
|    16 |          11.9 |           29.9 |         582.1 |
|    32 |          10.1 |             25 |         576.3 |

### Nx = 1000, Ny = 1000 (Polus:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |          44.4 |            387 |          1260 |
|     2 |            28 |            195 |           646 |
|     4 |            18 |             97 |           318 |
|     8 |          14.3 |           50.7 |           181 |
|    16 |            13 |           30.7 |           156 |
|    32 |          13.1 |           20.3 |           126 |
|    64 |          12.2 |           15.6 |           132 |
|   128 |          13.1 |           11.4 |         207.7 |

### Nx = 2000, Ny = 2000 (Intel Core I7-8700):
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |         167.2 |          778.1 |          3330 |
|     2 |          91.1 |          399.7 |        2337.2 |
|     4 |            52 |          206.8 |        2181.4 |
|     8 |            42 |            138 |        2200.4 |
|    16 |          41.6 |          105.2 |        2268.2 |
|    32 |            35 |           95.2 |        2255.6 |

### OpenMP ускорение (Nx = 1000, Ny = 1000, Intel Core I7-8700)
|      Этап \ T      |    2    |    4    |    8    |    16   |    32   |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|    Генерация графа |    2.01 |     3.5 |    3.89 |    4.27 |    4.38 |
| Заполнение матрицы |    1.95 |    3.76 |     5.7 |    6.45 |    7.47 |
|       Решение СЛАУ |    1.51 |    1.65 |    1.56 |    1.47 |    1.49 |

### OpenMP ускорение (Nx = 1000, Ny = 1000, Polus)
|      Этап \ T      |    2    |    4    |    8    |    16   |    32   |    64   |   128   |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|    Генерация графа |    1.53 |    2.48 |    3.14 |    3.48 |    3.77 |    3.42 |    3.32 |
| Заполнение матрицы |    1.95 |    3.97 |    7.46 |    12.5 |    24.8 |    23.8 |    33.3 |
|       Решение СЛАУ |       2 |    4.05 |    7.28 |    8.38 |    16.8 |    11.3 |      14 |

## Производительность математических ядер
### Скалярное произведение векторов (Intel Core I7-8700)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.009 |   0.088 |   0.998 |
|     2 |   0.001 |   0.005 |   0.045 |   0.535 |
|     4 |   0.001 |   0.003 |   0.024 |   0.277 |
|     8 |   0.001 |   0.002 |   0.012 |   0.225 |
|    16 |   0.029 |   0.032 |   0.046 |   0.287 |
|    32 |   0.057 |   0.058 |    0.07 |   0.298 |

### Скалярное произведение векторов (Polus)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.015 |    0.15 |   1.511 |
|     2 |   0.002 |   0.008 |   0.076 |   0.771 |
|     4 |   0.002 |   0.005 |   0.039 |    0.39 |
|     8 |   0.005 |   0.006 |   0.023 |   0.193 |
|    16 |   0.007 |   0.007 |   0.015 |   0.104 |
|    32 |    0.02 |   0.019 |   0.022 |   0.077 |
|    64 |   0.041 |    0.04 |   0.036 |   0.087 |
|   128 |   0.997 |    0.08 |   0.081 |   0.099 |

### Линейная комбинация векторов (Intel Core I7-8700)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |       0 |   0.003 |   0.033 |   0.598 |
|     2 |   0.001 |   0.002 |   0.017 |   0.346 |
|     4 |   0.001 |   0.001 |   0.009 |    0.28 |
|     8 |   0.001 |   0.001 |   0.008 |   0.286 |
|    16 |   0.029 |   0.028 |   0.037 |   0.364 |
|    32 |   0.058 |   0.058 |   0.064 |   0.368 |

### Линейная комбинация векторов (Polus)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.006 |   0.057 |   0.743 |
|     2 |   0.001 |   0.004 |   0.029 |   0.336 |
|     4 |   0.002 |   0.003 |   0.016 |   0.148 |
|     8 |   0.003 |   0.004 |   0.016 |    0.13 |
|    16 |   0.004 |   0.005 |   0.014 |   0.072 |
|    32 |   0.019 |   0.019 |   0.023 |   0.053 |
|    64 |   0.039 |   0.039 |   0.041 |   0.079 |
|   128 |   0.109 |   0.082 |   0.084 |   0.106 |

### Матрично-векторное произведение (Intel Core I7-8700)
| T \ N |  250  |  500  |  1000 |  2000 |
|   :-: |   :-: |   :-: |   :-: |   :-: |
|     1 | 0.053 | 0.216 | 0.941 | 4.069 |
|     2 |  0.03 | 0.111 | 0.485 | 2.194 |
|     4 | 0.015 | 0.059 | 0.253 | 1.352 |
|     8 | 0.008 | 0.031 | 0.134 | 1.272 |
|    16 |  0.04 | 0.064 | 0.183 | 1.395 |
|    32 | 0.066 | 0.088 | 0.198 | 1.404 |

### Матрично-векторное произведение (Polus)
| T \ N |  250  |  500  |  1000 |  2000 |
|   :-: |   :-: |   :-: |   :-: |   :-: |
|     1 | 0.095 | 0.374 | 1.517 | 5.989 |
|     2 | 0.048 | 0.188 | 0.749 | 3.015 |
|     4 | 0.025 | 0.096 |  0.38 | 1.535 |
|     8 | 0.016 | 0.054 | 0.199 | 0.791 |
|    16 | 0.015 | 0.034 | 0.113 | 0.428 |
|    32 | 0.021 | 0.035 |   0.1 | 0.353 |
|    64 | 0.021 | 0.036 |  0.11 | 0.377 |
|   128 | 0.339 | 0.058 | 0.088 | 0.237 |

### OpenMP ускорение (Intel Core I7-8700)
|      Ядро \ T      |    2    |    4    |    8    |    16   |    32   |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|   Dot (N = 100000) |    2.02 |    3.88 |    7.75 |    2.07 |    1.31 |
| axpby (N = 100000) |    1.94 |    3.67 |    4.12 |   0.892 |   0.508 |
|    SpMV (N = 1000) |    1.95 |    3.75 |    7.06 |    5.11 |    4.59 |

### OpenMP ускорение (Polus)
|      Ядро \ T      |    2    |    4    |    8    |    16   |    32   |    64   |   128   |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|   Dot (N = 100000) |    1.97 |    3.85 |    6.25 |    9.38 |    5.77 |    5.17 |   0.556 |
| axpby (N = 100000) |    1.97 |    2.19 |    4.38 |    5.18 |    2.38 |    2.71 |   0.695 |
|    SpMV (N = 1000) |    1.98 |    3.88 |    7.65 |    13.8 |      15 |    13.8 |    12.3 |

## Примеры запуска
```bash
>./main 4 4 1 2 1e-5 32 y
+--------------------------------------+
|             Generate part            |
+--------------------+-----------------+
|           Vertices |              26 |
|              Edges |              94 |
| Portrait non zeros |              91 |
|   Elapsed time, ms |               0 |
+--------------------+-----------------+

+--------------------------------------+
|               Fill part              |
+--------------------+-----------------+
|   Elapsed time, ms |               0 |
+--------------------+-----------------+

+--------------------------------------+
|              Solve part              |
+--------------------+-----------------+
|   Elapsed time, ms |               0 |
|           |b - Ax| |      0.00215439 |
|         Iterations |              23 |
+--------------------+-----------------+
```

### То же самое, но с отладочной информацией
```bash
./main 4 4 1 2 1e-5 32 y
Parsed arguments:
Nx: 4
Ny: 4
k1: 1
k2: 2
eps: 1e-05
T: 1

Rectangles count: 6
Triangles count: 20
Vertices count: 26
Edges count: 94

Edges list:
0 -> [ 0 1 7 ]
1 -> [ 0 1 2 9 ]
2 -> [ 1 2 3 ]
3 -> [ 2 3 4 10 ]
4 -> [ 3 4 5 ]
5 -> [ 4 5 12 ]
6 -> [ 6 7 14 ]
7 -> [ 0 6 7 8 ]
8 -> [ 7 8 9 15 ]
9 -> [ 1 8 9 10 ]
10 -> [ 3 9 10 11 17 ]
11 -> [ 10 11 12 19 ]
12 -> [ 5 11 12 ]
13 -> [ 13 14 20 ]
14 -> [ 6 13 14 15 ]
15 -> [ 8 14 15 16 22 ]
16 -> [ 15 16 17 24 ]
17 -> [ 10 16 17 18 ]
18 -> [ 17 18 19 25 ]
19 -> [ 11 18 19 ]
20 -> [ 13 20 21 ]
21 -> [ 20 21 22 ]
22 -> [ 15 21 22 23 ]
23 -> [ 22 23 24 ]
24 -> [ 16 23 24 25 ]
25 -> [ 18 24 25 ]
N: 26
IA: [ 0 3 7 10 14 17 20 23 27 31 35 40 44 47 50 54 59 63 67 71 74 77 80 84 87 91 94 ]
JA: [ 0 1 7 0 1 2 9 1 2 3 2 3 4 10 3 4 5 4 5 12 6 7 14 0 6 7 8 7 8 9 15 1 8 9 10 3 9 10 11 17 10 11 12 19 5 11 12 13 14 20 6 13 14 15 8 14 15 16 22 15 16 17 24 10 16 17 18 17 18 19 25 11 18 19 13 20 21 20 21 22 15 21 22 23 22 23 24 16 23 24 25 18 24 25 ]
+--------------------------------------+
|             Generate part            |
+--------------------+-----------------+
|           Vertices |              26 |
|              Edges |              94 |
| Portrait non zeros |              91 |
|   Elapsed time, ms |               0 |
+--------------------+-----------------+

v: A b
0: 1.2942       0.540302     0.283662      = 0
1: 1.2942       0.540302     0.753902     0.0044257     = 0.841471
2: 0.540302     0.753902     0.540302      = 0.909297
3: 0.753902     0.540302     1.81267      0.0044257     = 0.14112
4: 0.540302     1.81267      0.283662      = -0.756802
5: 1.81267      0.283662     0.988705      = -0.958924
6: 0.988705     0.283662     0.988705      = -0.279415
7: 1.2942       0.988705     0.283662     0.288088      = 0.656987
8: 0.283662     0.288088     0.0044257    1.73676       = 0.989358
9: 0.540302     0.288088     0.0044257    0.0044257     = 0.412118
10: 0.540302     0.0044257    0.0044257    1.54824      -0.748058     = -0.544021
11: 0.0044257    1.54824      0.988705     -0.030975     = -0.99999
12: 0.283662     1.54824      0.988705      = -0.536573
13: 0.555113     0.988705     0.968995      = 0.420167
14: 0.988705     0.555113     0.988705     1.73676       = 0.990607
15: 0.288088     0.988705     1.73676      -0.748058    -0.946868     = 0.650288
16: 1.73676      -0.748058    -0.748058    0.0221268     = -0.287903
17: 0.0044257    -0.748058    -0.748058    0.779033      = -0.961397
18: -0.748058    0.779033     -0.030975    1.08505       = -0.750987
19: 1.54824      0.779033     -0.030975     = 0.149877
20: 0.555113     0.968995     0.0221268     = 0.912945
21: 0.968995     0.0221268    -0.946868     = 0.836656
22: 1.73676      0.0221268    -0.946868    0.753902      = -0.00885131
23: -0.946868    0.753902     0.0221268     = -0.84622
24: -0.748058    0.753902     0.0221268    1.08505       = -0.905578
25: 0.779033     0.0221268    1.08505       = -0.132352
+--------------------------------------+
|               Fill part              |
+--------------------+-----------------+
|   Elapsed time, ms | 0               |
+--------------------+-----------------+

Iteration 1, |b - Ax|: 3.54272, rho: 11.9252
Iteration 2, |b - Ax|: 3.64587, rho: 8.13757
Iteration 3, |b - Ax|: 2.57296, rho: 4.91272
Iteration 4, |b - Ax|: 2.1353, rho: 2.87278
Iteration 5, |b - Ax|: 2.27338, rho: 3.02943
Iteration 6, |b - Ax|: 2.30135, rho: 3.67445
Iteration 7, |b - Ax|: 1.73054, rho: 2.3192
Iteration 8, |b - Ax|: 1.27477, rho: 1.27084
Iteration 9, |b - Ax|: 1.40154, rho: 1.5219
Iteration 10, |b - Ax|: 1.42666, rho: 1.36751
Iteration 11, |b - Ax|: 1.0942, rho: 0.757648
Iteration 12, |b - Ax|: 0.615341, rho: 0.211599
Iteration 13, |b - Ax|: 0.343309, rho: 0.0707409
Iteration 14, |b - Ax|: 0.237946, rho: 0.0378749
Iteration 15, |b - Ax|: 0.219492, rho: 0.026921
Iteration 16, |b - Ax|: 0.166017, rho: 0.0155849
Iteration 17, |b - Ax|: 0.0924228, rho: 0.00643842
Iteration 18, |b - Ax|: 0.0417177, rho: 0.00121485
Iteration 19, |b - Ax|: 0.0279739, rho: 0.000500765
Iteration 20, |b - Ax|: 0.0227914, rho: 0.000404203
Iteration 21, |b - Ax|: 0.009535, rho: 6.70745e-05
Iteration 22, |b - Ax|: 0.00495491, rho: 1.69704e-05
Iteration 23, |b - Ax|: 0.00335537, rho: 8.06896e-06
x: [ -9.69817 9.09318 -5.96146 10.742 -11.9758 -12.5942 -2.49031 10.1325 9.61521 -8.81002 -8.3272 5.56462 3.44375 5.49452 -2.01619 3.22228 -5.86714 -7.42062 -7.33762 -5.99622 5.80692 4.78422 2.58445 -3.45041 -5.87828 -7.13931 ]

+--------------------------------------+
|              Solve part              |
+--------------------+-----------------+
|   Elapsed time, ms |               0 |
|           |b - Ax| |      0.00215439 |
|         Iterations |              23 |
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