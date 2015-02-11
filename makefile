all:
	g++ -c grafo.cpp
	g++ -o pr pushrelabel.cpp grafo.o -std=gnu++0x

clean:
	rm *.o
	rm pr
