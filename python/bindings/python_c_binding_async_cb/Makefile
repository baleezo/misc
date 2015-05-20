all: testc.so

CFLAGS += `pkg-config --cflags --libs python glib-2.0` -fPIC

CXXFLAGS += `pkg-config --cflags --libs python gio-2.0 glib-2.0` -pthread -fPIC

testc.so: testc.o cppm.o
		g++ -shared $^ $(CXXFLAGS) -o testc.so

clean:
		rm -f *.so *.o
