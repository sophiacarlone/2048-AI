main: main.o ids.o tree.o tzfe.o
	g++ -g -o main main.o ids.o tree.o tzfe.o

main.o: main.cpp
	g++ -g -c main.cpp

test: test.o ids.o tree.o tzfe.o
	g++ -g -o test test.o ids.o tree.o tzfe.o

test.o: test.cpp
	g++ -g -c test.cpp

ids.o: ids.cpp
	g++ -g -c ids.cpp

tree.o: tree.cpp
	g++ -g -c tree.cpp

tzfe.o: tzfe.cpp
	g++ -g -c tzfe.cpp

clean:
	rm -f main test *.o *.output *.csv
