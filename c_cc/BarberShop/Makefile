CXXFLAGS += -Wall -std=c++0x -pthread

BarberShop: Getche.o BarberShop.o Barber.o main.o
	g++ $(CXXFLAGS) $^ -o BarberShop

clean:
	rm -f *.o BarberShop
