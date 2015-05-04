all: testc.so

CFLAGS += `pkg-config --cflags --libs python gio-2.0 glib-2.0` -fPIC

CFLAGS += -I/usr/include -Lpthread

cppm.o:
		g++ -c cppm.cc $(CFLAGS) -o cppm.o

testc.o:
		gcc -c testc.c $(CFLAGS) -o testc.o

testc.so: testc.o cppm.o
		g++ -shared testc.o cppm.o $(CFLAGS) -o testc.so

clean:
		@rm *.so *.o
