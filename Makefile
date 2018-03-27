a.out: drzewo.o main.o
	g++ drzewo.o main.o

drzewo.o: drzewo.cpp drzewo.hh
	g++ -Wall -pedantic -c drzewo.hh
	g++ -Wall -pedantic -c drzewo.cpp

main.o: main.cpp
	g++ -Wall -pedantic -c main.cpp

clean:
	rm -f *.o test
