#all:
#		python setup.py build
#
#clean:
#		rm -rf build

CFLAGS += `pkg-config --cflags --libs python` -fPIC
CXXFLAGS += `pkg-config --cflags --libs python` -fPIC

all: foo_wrapper.o foo.o
		g++ -shared -Wl,-soname,foo_wrapper.so $(CXXFLAGS) -o foo_wrapper.so foo_wrapper.o foo.o
		#g++ -shared foo_wrapper.o foo.o $(CXXFLAGS) -o foo_wrapper.so

clean:
		rm -f *.o *.so *.pyc
