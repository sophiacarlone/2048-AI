test: main.o ids.o tree.o tzfe.o
	g++ -g -o test main.o ids.o tree.o tzfe.o

main.o: main.cpp
	g++ -g -c main.cpp

ids.o: ids.cpp
	g++ -g -c ids.cpp

tree.o: tree.cpp
	g++ -g -c tree.cpp

tzfe.o: tzfe.cpp
	g++ -g -c tzfe.cpp

clean:
	rm -f test *.o *.txt
