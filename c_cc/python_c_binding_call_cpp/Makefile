all: testc.so

CFLAGS += `pkg-config --cflags --libs python` -fPIC

cppm.o:
		g++ -c cppm.cc -fPIC -o cppm.o

main.o:
		gcc -c main.c $(CFLAGS) -o main.o

testc.so: main.o cppm.o
		g++ -shared main.o cppm.o $(CFLAGS) -o testc.so

clean:
		@rm *.so *.o
