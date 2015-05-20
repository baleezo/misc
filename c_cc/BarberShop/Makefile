CXXFLAGS += -Wall -std=c++0x -pthread

BarberShop: main.o Getche.o BarberShop.o Barber.o
	g++ $(CXXFLAGS) Getche.o BarberShop.o Barber.o main.o -o BarberShop

clean:
	rm -f *.o BarberShop
