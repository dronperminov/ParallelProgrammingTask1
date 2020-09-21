COMPILER=g++
FLAGS=-O3 -fopenmp

all: main tests

main:
	$(COMPILER) $(FLAGS) ArgumentParser.cpp GraphGenerator.cpp main.cpp -o main

tests:
	$(COMPILER) $(FLAGS) GraphGenerator.cpp tests.cpp -o tests