# Практическое задание 1. Параллельная реализация операций с сеточными данными на неструктурированной смешанной сетке 

Первое задание по курсу "параллельные вычисления" на ВМК МГУ в 2020.
### Вариант B2

## Сборка
Сборка осуществляется с помощью make файла, так что достаточно выполнить в терминале команду `make main`. При этом на Вашей системе должен быть установлен компилятор языка C++.

## Запуск
Приложение использует обработку аргументов командной строки. Для работы допускается два варианта запуска: `./main path [debug]` и `./main Nx Ny k1 k2 T [debug]`
В первом случае аргументы Nx, Ny, k1, k2 и T будут считаны из файла, находящегося по пути `path`.

### Аргументы
`path` - путь к файлу с аргументами. Ожидается, что в файле записаны 4 числа: Nx, Ny, k1, k2

`Nx` - количество ячеек сетки по горизонтали

`Ny` - количество ячеек сетки по вертикали

`k1` - количество прямоугольных ячеек сетки

`k2` - количество треугольных ячеек сетки

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
>./main 3 2 1 2
Graph generation is end
+--------------------+-----------------+
|      Feature       |      Value      |
+--------------------+-----------------+
|           vertices |              10 |
|              edges |              32 |
| portrait non zeros |              29 |
|   elapsed time, ms |               0 |
+--------------------+-----------------+

Graph filling is end
Elapsed time: 0ms
```

### То же самое, но с отладочной информацией
```bash
./main 3 2 1 2 1 y
Parsed arguments:
Nx: 3
Ny: 2
k1: 1
k2: 2
 T: 1

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
+--------------------+-----------------+
|      Feature       |      Value      |
+--------------------+-----------------+
|           vertices |              10 |
|              edges |              32 |
| portrait non zeros |              29 |
|   elapsed time, ms |               0 |
+--------------------+-----------------+

Graph filling is end
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
Elapsed time: 0ms
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