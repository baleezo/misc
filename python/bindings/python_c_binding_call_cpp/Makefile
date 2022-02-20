all: testc.so

CFLAGS += `pkg-config --cflags --libs python2` -fPIC
CXXFLAGS += `pkg-config --cflags python2` -fPIC
LDFLAGS += `pkg-config --libs python2`

testc.so: testc.o cppm.o
		g++ -shared $(CFLAGS) -o testc.so $^ $(LDFLAGS)

clean:
		rm -f *.so *.o
