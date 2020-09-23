COMPILER=g++
FLAGS=-O3 -fopenmp -pedantic -Wall
FILES=ArgumentParser.cpp GraphGenerator.cpp GraphFiller.cpp VectorMath.cpp

all: main tests

main:
	$(COMPILER) $(FLAGS) $(FILES) main.cpp -o main

tests:
	$(COMPILER) $(FLAGS) $(FILES) tests.cpp -o tests