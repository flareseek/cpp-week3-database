main: main.o database.o
	g++ -o ./main ./*.o

main.o : main.cpp database.cpp database.h
	g++ -Werror -std=c++11 -c ./*.cpp
