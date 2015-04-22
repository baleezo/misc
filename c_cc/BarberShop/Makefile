BarberShop: main.o Getche.o BarberShop.o Barber.o
	g++ -Wall -std=c++0x -pthread Getche.o BarberShop.o Barber.o main.o -o BarberShop
	rm *.o

main.o: main.cc
	g++ -Wall -std=c++0x -c main.cc -o main.o

BarberShop.o: BarberShop.cc
	g++ -Wall -std=c++0x -c BarberShop.cc -o BarberShop.o

Barber.o:
	g++ -Wall -std=c++0x -c Barber.cc -o Barber.o

Getche.o: Getche.cc
	g++ -Wall -std=c++0x -c Getche.cc -o Getche.o

clean:
	rm BarberShop
