test: test.o tzfe.o
	g++ -g -o test test.o tzfe.o

test.o: test.cpp
	g++ -g -c test.cpp

tzfe.o: tzfe.cpp
	g++ -g -c tzfe.cpp

clean:
	rm -f test *.o
