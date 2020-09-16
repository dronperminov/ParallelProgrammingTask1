COMPILER=g++
FLAGS=-O3
NAME=generate

all:
	$(COMPILER) $(FLAGS) generate.cpp -o $(NAME)