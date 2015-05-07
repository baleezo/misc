CXXFLAGS += `pkg-config --cflags --libs python` -fPIC

all: foo.o
		g++ -shared -Wl,-soname,libfoo.so $(CXXFLAGS) -o libfoo.so  foo.o

clean:
		@rm *.o *.so *.pyc
