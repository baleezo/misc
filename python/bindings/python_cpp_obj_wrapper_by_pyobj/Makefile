#all:
#		python setup.py build

CFLAGS += `pkg-config --cflags --libs python` -fPIC
CXXFLAGS += `pkg-config --cflags --libs python` -fPIC

all: foo_wrapper.so

foo_wrapper.so: foo_wrapper.o foo.o
		g++ -shared -Wl,-soname,foo_wrapper.so $(CXXFLAGS) -o foo_wrapper.so $^
		@#g++ -shared $^ $(CXXFLAGS) -o foo_wrapper.so

clean:
		rm -rf *.o *.so *.pyc build
