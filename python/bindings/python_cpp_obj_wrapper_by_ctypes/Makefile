CXXFLAGS += `pkg-config --cflags --libs python` -fPIC

all: foo.o
		g++ -shared -Wl,-soname,libfoo.so $(CXXFLAGS) -o libfoo.so $^

clean:
		rm -f *.o *.so *.pyc
