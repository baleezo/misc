all: ctor dctor

ctor: main.cc
	g++ -std=c++0x main.cc -o ctor

dctor: main.cc
	g++ -std=c++0x -fno-elide-constructors main.cc -o dctor

clean:
	rm -f ctor dctor
