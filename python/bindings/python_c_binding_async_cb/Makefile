CFLAGS += `pkg-config --cflags python2` -fPIC
CXXFLAGS += `pkg-config --cflags python2 gio-2.0 glib-2.0` -pthread -fPIC
LDFLAGS += `pkg-config --libs python2 gio-2.0 glib-2.0`

all: testc.so

testc.so: testc.o cppm.o
		g++ -shared $(CXXFLAGS) -o testc.so $^ $(LDFLAGS)

clean:
		rm -f *.so *.o
