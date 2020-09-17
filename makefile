COMPILER=g++
FLAGS=-O3 -fopenmp
NAME=generate

all:
	$(COMPILER) $(FLAGS) ArgumentParser.cpp GraphGenerator.cpp generate.cpp -o $(NAME)