COMPILER=g++
FLAGS=-O3 -fopenmp

all: generate tests

generate:
	$(COMPILER) $(FLAGS) ArgumentParser.cpp GraphGenerator.cpp generate.cpp -o generate

tests:
	$(COMPILER) $(FLAGS) GraphGenerator.cpp tests.cpp -o tests