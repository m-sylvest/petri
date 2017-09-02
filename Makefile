all:
	g++ -std=c++14 -I. -o petri petri.cpp

clean:
	rm petri
