#all:
#		python setup.py build

#clean:
#		rm -rf build

CFLAGS += `pkg-config --cflags --libs python` -fPIC
CXXFLAGS += `pkg-config --cflags --libs python` -fPIC

all: foo_wrapper.o foo.o
		#g++ -shared -Wl,-soname,noddy.so $(CXXFLAGS) -o noddy.so noddy.o foo.o
		g++ -shared foo_wrapper.o foo.o $(CXXFLAGS) -o foo_wrapper.so

clean:
		rm -f *.o *.so *.pyc
