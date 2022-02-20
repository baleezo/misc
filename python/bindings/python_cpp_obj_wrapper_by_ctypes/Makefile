CXXFLAGS += `pkg-config --cflags --libs python2` -fPIC

all: libfoo.so

libfoo.so: foo.o
		g++ -shared -Wl,-soname,libfoo.so $(CXXFLAGS) -o libfoo.so $^

clean:
		rm -f *.o *.so *.pyc
