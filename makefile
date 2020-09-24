COMPILER=g++
FLAGS=-O3 -fopenmp -pedantic -Wall
FILES=ArgumentParser.cpp GraphGenerator.cpp GraphFiller.cpp VectorMath.cpp ConjugateGradientSolver.cpp

all: main tests performance

main:
	$(COMPILER) $(FLAGS) $(FILES) main.cpp -o main

tests:
	$(COMPILER) $(FLAGS) $(FILES) tests.cpp -o tests

performance:
	$(COMPILER) $(FLAGS) $(FILES) performance.cpp -o performance

clean:
	rm main tests performance