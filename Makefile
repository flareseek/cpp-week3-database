main: main.o
	g++ -o ./main ./main.cpp

main.o : main.cpp database.h
	g++ -Werror -std=c++11 -c ./main.cpp
