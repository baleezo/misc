all: testc.so

CFLAGS += `pkg-config --cflags --libs python` -fPIC
CXXFLAGS += `pkg-config --cflags --libs python` -fPIC

testc.so: testc.o cppm.o
		g++ -shared $(CFLAGS) -o testc.so $^

clean:
		rm -f *.so *.o
