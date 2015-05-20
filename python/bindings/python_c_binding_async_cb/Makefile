CFLAGS += `pkg-config --cflags python` -fPIC
CXXFLAGS += `pkg-config --cflags python gio-2.0 glib-2.0` -pthread -fPIC
LDFLAGS += `pkg-config --libs python gio-2.0 glib-2.0`

all: testc.so

testc.so: testc.o cppm.o
		g++ -shared $(CXXFLAGS) -o testc.so $^ $(LDFLAGS)

clean:
		rm -f *.so *.o
