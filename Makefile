all:
	g++ -Wall -std=c++11 dia.cpp -c -o dia.o
	g++ -Wall -std=c++11 agenda.cpp -c -o agenda.o
	g++ -Wall -std=c++11 main.cpp -c -o main.o
	g++ -Wall -std=c++11 -o tp1 main.o dia.o agenda.o
	rm *.o

run:
	./tp1

clean:
	rm *.o
