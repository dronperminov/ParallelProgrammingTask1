COMPILER=g++
FLAGS=-O3 -fopenmp -pedantic -Wall

all: main tests

main:
	$(COMPILER) $(FLAGS) ArgumentParser.cpp GraphGenerator.cpp GraphFiller.cpp main.cpp -o main

tests:
	$(COMPILER) $(FLAGS) GraphGenerator.cpp GraphFiller.cpp tests.cpp -o tests