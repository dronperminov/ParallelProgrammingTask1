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
Система 2: Polus, CPU: 4.023GHz, 160 cores
Параметры сетки: k1 = 29, k2 = 37

## Производительность математических ядер (Intel Core I7-8700)
### Скалярное произведение векторов (время в миллисекундах)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.009 |   0.092 |   0.995 |
|     2 |   0.001 |   0.005 |   0.045 |    0.53 |
|     4 |   0.001 |   0.003 |   0.024 |   0.278 |
|     8 |   0.001 |   0.002 |   0.013 |   0.246 |
|    16 |   0.028 |   0.031 |   0.046 |   0.287 |
|    32 |   0.057 |   0.059 |   0.071 |   0.301 |

### Линейная комбинация векторов (время в миллисекундах)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |       0 |   0.003 |   0.032 |   0.592 |
|     2 |   0.001 |   0.002 |   0.017 |   0.342 |
|     4 |   0.001 |   0.001 |   0.009 |   0.284 |
|     8 |   0.001 |   0.001 |   0.008 |   0.298 |
|    16 |   0.031 |   0.031 |   0.037 |    0.37 |
|    32 |   0.058 |   0.058 |   0.064 |   0.378 |

### Матрично-векторное произведение (время в миллисекундах)
| T \ N |  1000   |  10000  | 100000  | 1000000 |
|   :-: |    :-:  |    :-:  |    :-:  |    :-:  |
|     1 |   0.003 |   0.029 |   0.295 |   3.818 |
|     2 |   0.002 |   0.015 |   0.154 |    2.39 |
|     4 |   0.001 |   0.008 |    0.08 |   2.125 |
|     8 |   0.001 |   0.008 |   0.078 |   2.127 |
|    16 |   0.028 |   0.036 |   0.098 |   2.291 |
|    32 |   0.058 |   0.063 |    0.12 |   2.256 |

### OpenMP ускорение (N = 1000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |       1 |    1.18 |       1 |  0.0448 |  0.0218 |
| axpby    |     0.6 |     0.6 |   0.545 |  0.0203 | 0.00976 |
| SpMV     |    1.43 |    2.06 |    2.06 |   0.111 |  0.0531 |

### OpenMP ускорение (N = 10000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |     1.8 |       3 |     4.5 |     0.3 |    0.15 |
| axpby    |     1.5 |       3 |       3 |   0.103 |  0.0517 |
| SpMV     |    1.88 |    3.75 |    3.75 |   0.857 |   0.469 |

### OpenMP ускорение (N = 100000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |    2.25 |     4.5 |       9 |     1.5 |    1.29 |
| axpby    |       3 |     inf |     inf |       1 |     0.5 |
| SpMV     |    1.93 |    4.14 |    3.62 |     2.9 |    2.42 |

### GFLOPS
| Ядро \ N |      1000 |     10000 |    100000 |   1000000 |
|      :-: |       :-: |       :-: |       :-: |       :-: |
| Dot      |   1.53846 |   2.22222 |   2.12766 |   2.00401 |
| axpby    |   4.28571 |        10 |   8.82353 |   5.02513 |
| SpMV     |   4.70588 |   5.16129 |   5.31561 |   4.19287 |

## Производительность решения (Intel Core I7-8700)
Параметры сетки: k1 = 29, k2 = 37
### Nx = 500, Ny = 500:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |           6.4 |           41.7 |          60.5 |
|     2 |             4 |             21 |            37 |
|     4 |             3 |             11 |            31 |
|     8 |             2 |              7 |            31 |
|    16 |             2 |            6.3 |          34.1 |
|    32 |             2 |            5.1 |            37 |

### Nx = 1000, Ny = 1000:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |            38 |            182 |           300 |
|     2 |          22.5 |           93.5 |           200 |
|     4 |            14 |           48.5 |           180 |
|     8 |          11.5 |           33.5 |           187 |
|    16 |          11.8 |           31.4 |           199 |
|    32 |           9.5 |           25.8 |           196 |

### Nx = 2000, Ny = 2000:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |           173 |            737 |          1310 |
|     2 |          98.4 |            380 |           892 |
|     4 |          61.5 |            197 |           817 |
|     8 |          49.6 |            136 |           821 |
|    16 |          49.8 |            103 |           846 |
|    32 |            40 |           96.4 |           839 |

### OpenMP ускорение (Nx = 1000, Ny = 1000)
|      Этап \ T      |       2 |       4 |       8 |      16 |      32 |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|    Генерация графа |     1.6 |    2.62 |    3.07 |    3.12 |    3.77 |
| Заполнение матрицы |    1.95 |    3.76 |    5.42 |    5.91 |    7.17 |
|       Решение СЛАУ |    1.51 |    1.67 |     1.6 |    1.51 |    1.53 |


## Производительность математических ядер (Polus, g++)
### Скалярное произведение векторов (время в миллисекундах)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.015 |    0.15 |    1.51 |
|     2 |   0.002 |   0.009 |   0.076 |   0.779 |
|     4 |   0.002 |   0.005 |   0.039 |   0.398 |
|     8 |   0.005 |   0.006 |   0.023 |   0.197 |
|    16 |   0.006 |   0.006 |   0.015 |   0.104 |
|    32 |   0.021 |    0.02 |   0.023 |    0.08 |
|    64 |   0.043 |   0.042 |   0.039 |   0.088 |
|   128 |   0.167 |    0.08 |   0.082 |   0.098 |

### Линейная комбинация векторов (время в миллисекундах)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.006 |   0.057 |   0.739 |
|     2 |   0.002 |   0.004 |    0.03 |   0.334 |
|     4 |   0.003 |   0.004 |   0.017 |   0.156 |
|     8 |   0.003 |   0.004 |   0.015 |   0.129 |
|    16 |   0.005 |   0.006 |   0.014 |   0.073 |
|    32 |   0.008 |   0.008 |   0.014 |   0.071 |
|    64 |   0.033 |   0.031 |   0.034 |   0.087 |
|   128 |   0.224 |   0.046 |   0.046 |   0.072 |

### Матрично-векторное произведение (время в миллисекундах)
| T \ N |  1000   |  10000  | 100000  | 1000000 |
|   :-: |    :-:  |    :-:  |    :-:  |    :-:  |
|     1 |   0.008 |   0.071 |     0.7 |   7.032 |
|     2 |   0.005 |   0.036 |    0.35 |    3.74 |
|     4 |   0.003 |   0.019 |   0.178 |   1.792 |
|     8 |   0.003 |   0.015 |   0.107 |   0.947 |
|    16 |   0.005 |   0.011 |   0.074 |   0.713 |
|    32 |   0.008 |   0.012 |   0.066 |   0.604 |
|    64 |   0.019 |   0.019 |   0.074 |   0.655 |
|   128 |   1.568 |    0.05 |   0.074 |   0.374 |

### OpenMP ускорение (N = 1000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |       1 |       1 |   0.333 |   0.286 |   0.143 |  0.0571 |  0.0022 |
| axpby    |       1 |     0.5 |     0.2 |     0.2 |   0.125 |  0.0556 |  0.0213 |
| SpMV     |    1.75 |    1.75 |    1.17 |     1.4 |   0.875 |   0.389 |   0.146 |

### OpenMP ускорение (N = 10000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |    1.88 |     2.5 |       3 |    1.36 |    0.75 |   0.294 |  0.0475 |
| axpby    |     1.5 |     1.5 |     1.5 |     0.6 |   0.375 |   0.182 |    0.13 |
| SpMV     |    1.97 |    3.55 |    4.73 |    3.94 |    3.38 |    1.97 |    1.45 |

### OpenMP ускорение (N = 100000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |    1.95 |    3.85 |    6.82 |    9.38 |    9.38 |    3.57 |   0.685 |
| axpby    |     1.9 |    3.56 |     3.8 |    4.38 |    4.07 |     1.5 |    1.33 |
| SpMV     |    2.01 |    3.97 |    5.36 |    9.68 |    10.9 |    8.32 |    9.68 |

## Производительность решения (Polus, g++)
Параметры сетки: k1 = 29, k2 = 37
### Nx = 500, Ny = 500:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |          13.6 |            100 |           105 |
|     2 |           6.1 |           47.9 |          49.5 |
|     4 |             4 |             24 |          30.1 |
|     8 |           5.9 |             12 |            15 |
|    16 |             1 |              7 |            11 |
|    32 |           3.1 |              5 |             8 |
|    64 |           4.1 |              4 |             9 |
|   128 |           6.4 |            3.5 |           100 |

### Nx = 1000, Ny = 1000:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |          53.6 |            386 |           426 |
|     2 |          30.9 |            193 |           217 |
|     4 |          35.8 |           97.2 |           108 |
|     8 |             9 |           51.4 |          62.1 |
|    16 |           6.6 |           30.5 |          54.6 |
|    32 |            16 |           21.5 |          49.8 |
|    64 |          15.1 |           17.6 |          50.3 |
|   128 |          11.9 |             10 |          32.5 |

### Nx = 2000, Ny = 2000:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |           221 |           1550 |          1890 |
|     2 |           117 |            777 |          1150 |
|     4 |          67.5 |            389 |           590 |
|     8 |          44.2 |            202 |           321 |
|    16 |          28.5 |            123 |           286 |
|    32 |          71.8 |           81.1 |           229 |
|    64 |          52.6 |           61.6 |           251 |
|   128 |          42.2 |             38 |           173 |

### OpenMP ускорение (Nx = 1000, Ny = 1000)
|      Этап \ T      |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|    Генерация графа |    1.92 |    3.36 |    4.72 |    5.17 |    2.54 |    3.96 |    4.27 |
| Заполнение матрицы |    1.99 |       4 |    7.28 |    12.6 |      18 |    21.4 |    39.4 |
|       Решение СЛАУ |    1.94 |    3.94 |    6.91 |    8.21 |    9.13 |    8.68 |      13 |

### GFLOPS
| Ядро \ N |      1000 |     10000 |    100000 |   1000000 |
|      :-: |       :-: |       :-: |       :-: |       :-: |
| Dot      |         1 |   1.33333 |   1.31579 |   1.31839 |
| axpby    |         3 |         5 |   5.26316 |   3.95257 |
| SpMV     |   2.28571 |   2.25352 |    2.2695 |   2.26148 |

## Производительность математических ядер (Polus, xlc++\_r)
### Скалярное произведение векторов (время в миллисекундах)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.001 |   0.003 |   0.044 |   0.514 |
|     2 |   0.002 |   0.004 |   0.018 |   0.209 |
|     4 |   0.003 |   0.004 |   0.014 |   0.083 |
|     8 |   0.003 |   0.004 |   0.009 |   0.063 |
|    16 |   0.004 |   0.004 |   0.008 |   0.055 |
|    32 |   0.005 |   0.005 |   0.009 |   0.049 |
|    64 |   0.009 |   0.007 |    0.01 |    0.04 |
|   128 |   0.062 |   0.035 |   0.057 |    0.16 |

### Линейная комбинация векторов (время в миллисекундах)
| T \ N |   1000  |  10000  |  100000 | 1000000 |
|   :-: |     :-: |     :-: |     :-: |     :-: |
|     1 |   0.005 |   0.039 |   0.382 |   3.783 |
|     2 |   0.006 |   0.024 |   0.194 |    1.91 |
|     4 |   0.006 |   0.016 |   0.109 |   0.993 |
|     8 |   0.007 |   0.011 |    0.06 |     0.5 |
|    16 |   0.016 |   0.009 |   0.034 |   0.269 |
|    32 |   0.017 |   0.019 |   0.025 |   0.262 |
|    64 |   0.024 |   0.031 |   0.056 |   0.242 |
|   128 |   0.041 |   0.057 |   0.045 |     0.2 |

### Матрично-векторное произведение (время в миллисекундах)
| T \ N |  1000   |  10000  | 100000  | 1000000 |
|   :-: |    :-:  |    :-:  |    :-:  |    :-:  |
|     1 |   0.046 |   0.452 |    4.34 |   40.74 |
|     2 |   0.026 |   0.211 |   2.047 |  19.505 |
|     4 |   0.014 |   0.098 |   0.948 |   9.662 |
|     8 |    0.01 |   0.058 |   0.491 |   4.918 |
|    16 |   0.007 |   0.033 |   0.253 |   2.475 |
|    32 |   0.007 |    0.02 |   0.132 |   1.271 |
|    64 |   0.006 |   0.012 |   0.076 |    0.63 |
|   128 |   0.008 |    0.01 |   0.037 |    0.32 |

### OpenMP ускорение (N = 1000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |     0.6 |     0.6 |     0.6 |     0.5 |     0.5 |   0.375 |   0.231 |
| axpby    |     0.6 |     0.6 |     0.6 |     0.6 |     0.6 |     0.5 |   0.429 |
| SpMV     |    1.59 |    2.45 |       3 |    3.86 |     4.5 |     4.5 |    3.86 |

### OpenMP ускорение (N = 10000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |     1.3 |    1.62 |    1.86 |    1.86 |    1.86 |    1.44 |    1.08 |
| axpby    |     1.4 |     2.1 |    2.62 |       3 |     3.5 |     3.5 |    2.62 |
| SpMV     |    1.91 |    3.64 |    4.94 |    8.45 |    13.8 |    21.8 |    26.2 |

### OpenMP ускорение (N = 100000)
| Ядро \ T |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|      :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
| Dot      |    1.76 |    3.26 |    4.27 |    6.53 |    8.54 |    10.1 |    8.54 |
| axpby    |    1.86 |    3.44 |    4.51 |    7.52 |    10.7 |    16.9 |    20.3 |
| SpMV     |    1.96 |    3.81 |    5.24 |    10.7 |    20.4 |    35.6 |    71.2 |

### GFLOPS
| Ядро \ N |      1000 |     10000 |    100000 |   1000000 |
|      :-: |       :-: |       :-: |       :-: |       :-: |
| Dot      |     0.667 |      1.54 |      1.79 |      1.77 |
| axpby    |         1 |      1.43 |      1.49 |      1.46 |
| SpMV     |     0.593 |     0.613 |     0.605 |     0.594 |

## Производительность решения (Polus, xlc++\_r)
Параметры сетки: k1 = 29, k2 = 37
### Nx = 500, Ny = 500:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |          35.3 |           89.5 |           277 |
|     2 |          19.1 |           45.1 |           139 |
|     4 |            11 |           24.4 |          77.1 |
|     8 |             6 |             12 |          38.1 |
|    16 |             4 |              7 |          24.2 |
|    32 |             3 |            3.1 |            13 |
|    64 |             2 |            1.6 |           7.1 |
|   128 |             2 |              1 |             4 |

### Nx = 1000, Ny = 1000:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |           147 |            363 |          1170 |
|     2 |            79 |            182 |           601 |
|     4 |            52 |            115 |           380 |
|     8 |          31.8 |           63.7 |           207 |
|    16 |            20 |             32 |           119 |
|    32 |          13.8 |           15.7 |          58.8 |
|    64 |          11.3 |              8 |          37.1 |
|   128 |            10 |            4.5 |          21.7 |

### Nx = 2000, Ny = 2000:
|   T   | Генерация, мс | Заполнение, мс |  Решение, мс  |
|   :-: |           :-: |            :-: |           :-: |
|     1 |           567 |           1380 |          4931 |
|     2 |           336 |            788 |          3224 |
|     4 |           210 |            474 |          1912 |
|     8 |           122 |            244 |          1073 |
|    16 |          81.3 |            130 |           578 |
|    32 |          56.4 |           63.7 |           297 |
|    64 |          44.1 |           33.2 |           170 |
|   128 |          39.3 |             17 |           166 |

### OpenMP ускорение (Nx = 1000, Ny = 1000)
|      Этап \ T      |       2 |       4 |       8 |      16 |      32 |      64 |     128 |
|                :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |     :-: |
|    Генерация графа |    1.73 |    3.03 |    5.37 |    8.32 |    11.6 |    14.6 |    16.3 |
| Заполнение матрицы |    1.75 |    3.22 |    6.45 |    12.7 |    25.3 |    49.4 |      92 |
|       Решение СЛАУ |    1.89 |    3.41 |    6.79 |    12.2 |    23.8 |    39.5 |      64 |

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