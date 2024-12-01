# Makes the executable

CC = g++
FLAGS = -std=c++20 -g
src = $(DAYPATH)
default:
	$(CC) $(FLAGS) AOC.cpp -o AOC
