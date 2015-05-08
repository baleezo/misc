all: testc.so

CFLAGS += `pkg-config --cflags --libs python` -fPIC

cppm.o:
		g++ -c cppm.cc -fPIC -o cppm.o

testc.o:
		gcc -c testc.c $(CFLAGS) -o testc.o

testc.so: testc.o cppm.o
		g++ -shared testc.o cppm.o $(CFLAGS) -o testc.so

clean:
		rm -f *.so *.o
