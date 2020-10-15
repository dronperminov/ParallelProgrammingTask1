#include <iostream>
#include <iomanip>
#include <omp.h>
#include <cassert>
#include "GraphGenerator.h"
#include "GraphFiller.h"
#include "ConjugateGradientSolver.h"
#include "VectorMath.h"

void TestGenerator(int nx, int ny, int k1, int k2, int expectedN, int expectedEdges, int *expectedIA, int *expectedJA) {
    int n;
    int *ia;
    int *ja;

    std::cout << "Generator test for (" << nx << "x" << ny << " for k = " << k1 << " and " << k2 << "): ";
    GraphGenerator generator1(nx, ny, k1, k2, false, 32);
    generator1.Generate(n, ia, ja, false);

    assert(n == expectedN);
    assert(ia[n] == expectedEdges);

    for (int i = 0; i < expectedN; i++)
        assert(ia[i] == expectedIA[i]);

    for (int i = 0; i < expectedEdges; i++)
        assert(ja[i] == expectedJA[i]);

    delete[] ia;
    delete[] ja;

    std::cout << "OK" << std::endl;
}

void GeneratorTests() {
    int ia1[] = { 0, 2, 4 };
    int ja1[] = { 0, 1, 0, 1 };

    int ia2[] = { 0, 2, 5, 7 };
    int ja2[] = { 0, 1, 0, 1, 2, 1, 2 };

    int ia3[] = { 0, 3, 7, 10, 14, 16, 19, 22, 26, 29, 32};
    int ja3[] = { 0, 1, 5, 0, 1, 2, 7, 1, 2, 3, 2, 3, 4, 9, 3, 4, 0, 5, 6, 5, 6, 7, 1, 6, 7, 8, 7, 8, 9, 3, 8, 9 };

    int ia4[] = { 0, 3, 7, 11, 14, 18, 21, 23, 27, 31, 35, 38, 42, 45 };
    int ja4[] = { 0, 1, 7, 0, 1, 2, 8, 1, 2, 3, 9, 2, 3, 4, 3, 4, 5, 11, 4, 5, 12, 6, 7, 0, 6, 7, 8, 1, 7, 8, 9, 2, 8, 9, 10, 9, 10, 11, 4, 10, 11, 12, 5, 11, 12 };

    int ia5[] = { 0, 3, 7, 11, 15, 17, 20, 24, 29, 34, 38, 40, 44, 47, 51, 55, 58 };
    int ja5[] = { 0, 1, 6, 0, 1, 2, 7, 1, 2, 3, 8, 2, 3, 4, 9, 3, 4, 5, 6, 11, 0, 5, 6, 7, 1, 6, 7, 8, 13, 2, 7, 8, 9, 14, 3, 8, 9, 15, 10, 11, 5, 10, 11, 12, 11, 12, 13, 7, 12, 13, 14, 8, 13, 14, 15, 9, 14, 15 };

    int ia6[] = { 0, 3, 7, 10, 14, 19, 23, 27, 32, 36, 39, 43, 46 };
    int ja6[] = { 0, 1, 3, 0, 1, 2, 4, 1, 2, 5, 0, 3, 4, 6, 1, 3, 4, 5, 7, 2, 4, 5, 8, 3, 6, 7, 9, 4, 6, 7, 8, 10, 5, 7, 8, 11, 6, 9, 10, 7, 9, 10, 11, 8, 10, 11 };

    int ia7[] = { 0, 3, 6, 10, 13, 17, 19, 22, 26, 30, 34, 38, 41, 44, 48, 52, 56, 60, 63, 65, 69, 72, 76, 79, 82 };
    int ja7[] = { 0, 1, 7, 0, 1, 2, 1, 2, 3, 9, 2, 3, 4, 3, 4, 5, 11, 4, 5, 6, 7, 13, 0, 6, 7, 8, 7, 8, 9, 15, 2, 8, 9, 10, 9, 10, 11, 17, 4, 10, 11, 12, 13, 19, 6, 12, 13, 14, 13, 14, 15, 21, 8, 14, 15, 16, 15, 16, 17, 23, 10, 16, 17, 18, 19, 12, 18, 19, 20, 19, 20, 21, 14, 20, 21, 22, 21, 22, 23, 16, 22, 23 };

    int ia8[] = { 0, 3, 7, 11, 15, 19, 23, 26, 30, 35, 40, 45, 49, 53, 57, 61, 65, 68, 71, 75, 79, 83, 87, 91, 95, 99, 103, 107, 111, 115, 119, 122, 125, 129, 133, 137, 141, 145, 150, 155, 160, 164, 167, 171, 175, 179, 183, 187, 190 };
    int ja8[] = { 0, 1, 7, 0, 1, 2, 8, 1, 2, 3, 9, 2, 3, 4, 10, 3, 4, 5, 12, 4, 5, 6, 14, 5, 6, 16, 0, 7, 8, 18, 1, 7, 8, 9, 20, 2, 8, 9, 10, 22, 3, 9, 10, 11, 24, 10, 11, 12, 26, 4, 11, 12, 13, 12, 13, 14, 28, 5, 13, 14, 15, 14, 15, 16, 30, 6, 15, 16, 17, 18, 32, 7, 17, 18, 19, 18, 19, 20, 34, 8, 19, 20, 21, 20, 21, 22, 36, 9, 21, 22, 23, 22, 23, 24, 37, 10, 23, 24, 25, 24, 25, 26, 38, 11, 25, 26, 27, 26, 27, 28, 39, 13, 27, 28, 29, 28, 29, 30, 40, 15, 29, 30, 31, 32, 41, 17, 31, 32, 33, 32, 33, 34, 42, 19, 33, 34, 35, 34, 35, 36, 43, 21, 35, 36, 37, 23, 36, 37, 38, 44, 25, 37, 38, 39, 45, 27, 38, 39, 40, 46, 29, 39, 40, 47, 31, 41, 42, 33, 41, 42, 43, 35, 42, 43, 44, 37, 43, 44, 45, 38, 44, 45, 46, 39, 45, 46, 47, 40, 46, 47 };

    TestGenerator(1, 1, 0, 1, 2, 4, ia1, ja1);
    TestGenerator(2, 1, 1, 0, 2, 4, ia1, ja1);
    TestGenerator(2, 1, 1, 1, 3, 7, ia2, ja2);
    TestGenerator(3, 2, 1, 2, 10, 32, ia3, ja3);
    TestGenerator(5, 2, 2, 1, 13, 45, ia4, ja4);
    TestGenerator(4, 3, 3, 2, 16, 58, ia5, ja5);
    TestGenerator(3, 4, 1, 0, 12, 46, ia6, ja6);
    TestGenerator(3, 4, 0, 1, 24, 82, ia7, ja7);
    TestGenerator(7, 5, 11, 13, 48, 190, ia8, ja8);
}

void TestFiller(int n, int *ia, int *ja, double *expectedA, double eps = 1e-15) {
    double *a;
    double *b;

    std::cout << "Fill test for n = " << n << ": ";
    GraphFiller filler(n, ia, ja, false);
    filler.Fill(a, b, false);

    for (int i = 0; i < ia[n]; i++)
        assert(fabs(a[i] - expectedA[i]) < eps);

    for (int i = 0; i < n; i++)
        assert(fabs(b[i] - Fb(i)) < eps);

    std::cout << "OK" << std::endl;
}

void FillerTests() {
    int ia1[] = { 0, 2, 4, 7 };
    int ja1[] = { 0, 2, 1, 2, 0, 1, 2 };

    double a1[] = {
        fabs(Fa(0, 2)) * DIAGONAL_DOMINANCE_COEFFICIENT, Fa(0, 2),
        fabs(Fa(1, 2)) * DIAGONAL_DOMINANCE_COEFFICIENT, Fa(1, 2),
        Fa(2, 0), Fa(2, 1), (fabs(Fa(2, 0)) + fabs(Fa(2, 1))) * DIAGONAL_DOMINANCE_COEFFICIENT
    };

    int ia2[] = { 0, 2, 4, 7, 11, 13 };
    int ja2[] = { 0, 2, 1, 3, 0, 2, 3, 1, 2, 3, 4, 3, 4 };

    double a2[] = {
        fabs(Fa(0, 2)) * DIAGONAL_DOMINANCE_COEFFICIENT, Fa(0, 2),
        fabs(Fa(1, 3)) * DIAGONAL_DOMINANCE_COEFFICIENT, Fa(1, 3),
        Fa(2, 0), (fabs(Fa(2, 0)) + fabs(Fa(2, 3))) * DIAGONAL_DOMINANCE_COEFFICIENT, Fa(2, 3),
        Fa(3, 1), Fa(3, 2), (fabs(Fa(3, 1)) + fabs(Fa(3, 2)) + fabs(Fa(3, 4))) * DIAGONAL_DOMINANCE_COEFFICIENT, Fa(3, 4),
        Fa(4, 3), fabs(Fa(4, 3)) * DIAGONAL_DOMINANCE_COEFFICIENT
    };

    const int n = 27;
    int ia3[n + 1];
    int ja3[n*n];
    double a3[n*n];

    ia3[0] = 0;

    for (int i = 0; i < n; i++) {
        ia3[i + 1] = ia3[i] + n;
        double sum = 0;

        for (int j = 0; j < n; j++) {
            ja3[i * n + j] = j;

            if (i != j) {
                a3[i * n + j] = Fa(i, j);
                sum += fabs(a3[i * n + j]);
            }
        }

        a3[i * n + i] = sum * DIAGONAL_DOMINANCE_COEFFICIENT;
    }

    std::cout << std::endl;
    TestFiller(3, ia1, ja1, a1);
    TestFiller(5, ia2, ja2, a2);
    TestFiller(n, ia3, ja3, a3);
}

void TestDot(double *x, double *y, int n, double expectedDot, double eps = 1e-15) {
    std::cout << "Dot test for n = " << n << ": ";
    assert(fabs(Dot(x, y, n) - expectedDot) < eps);
    std::cout << "OK" << std::endl;
}

void TestLinearCombination(double *x, double *y, double a, double b, int n, double *expectedVector, double eps = 1e-15) {
    std::cout << "Linear combination test for n = " << n << " and a = " << a << ", b = " << b << ": ";
    LinearCombination(a, x, b, y, n);

    for (int i = 0; i < n; i++)
        assert(fabs(x[i] - expectedVector[i]) < eps);

    std::cout << "OK" << std::endl;
}

void TestMatrixVectorMultiplication(int *ia, int *ja, double *a, int n, double *x, double *expectedVector, double eps = 1e-15) {
    std::cout << "Test matrix to vector multiplication for n = " << n << ": ";

    double *y = new double[n];
    MatrixVectorMultiplication(ia, ja, a, n, x, y);

    for (int i = 0; i < n; i++)
        assert(fabs(y[i] - expectedVector[i]) < eps);

    std::cout << "OK" << std::endl;
}

void VectorMathTests(double eps = 1e-15) {
    double x1[3] = { 1, -0.5, 2 };
    double y1[3] = { 5, 8, -0.5 };
    double xy1[3] = { -13, -25, 5.5 };

    double x2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    double y2[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    double xy2[10] = { 0, -5.5, -11, -16.5, -22, -27.5, -33, -38.5, -44, -49.5 };

    std::cout << std::endl;
    TestDot(x1, y1, 3, 0);
    TestDot(x2, y2, 1, 10);
    TestDot(x2, y2, 2, 28);
    TestDot(x2, y2, 5, 110);
    TestDot(x2, y2, 10, 220);

    std::cout << std::endl;
    TestLinearCombination(x1, y1, 2, -3, 3, xy1);
    TestLinearCombination(x2, y2, -5, 0.5, 10, xy2);

    int ia1[4] = { 0, 2, 3, 4 };
    int ja1[4] = { 1, 2, 0, 2 };
    double a1[4] = { -5, 2, 1, -2 };
    double vx1[3] = { 1, 2, 3 };
    double vy1[3] = { -4, 1, -6 };

    int ia2[6] = { 0, 1, 2, 3, 4, 5 };
    int ja2[5] = { 0, 1, 2, 3, 4 };
    double a2[5] = { 1, 0.5, 3, -4.5, 5 };
    double vx2[5] = { -2, 2, -2, 2, -2 };
    double vy2[5] = { -2, 1, -6, -9, -10 };

    std::cout << std::endl;
    TestMatrixVectorMultiplication(ia1, ja1, a1, 3, vx1, vy1);
    TestMatrixVectorMultiplication(ia2, ja2, a2, 5, vx2, vy2);
}

int main() {
    omp_set_num_threads(32);

    GeneratorTests();
    FillerTests();
    VectorMathTests();
}