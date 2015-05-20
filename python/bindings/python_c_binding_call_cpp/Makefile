all: testc.so

CFLAGS += `pkg-config --cflags --libs python` -fPIC
CXXFLAGS += `pkg-config --cflags python` -fPIC
LDFLAGS += `pkg-config --libs python`

testc.so: testc.o cppm.o
		g++ -shared $(CFLAGS) -o testc.so $^ $(LDFLAGS)

clean:
		rm -f *.so *.o
