FLAGS = -O2

a.out : main.cpp
	g++ -Wall -Wextra -Wshadow $(FLAGS) -o $@ $<
