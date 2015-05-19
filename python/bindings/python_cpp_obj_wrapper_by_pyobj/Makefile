#all:
#		python setup.py build

#clean:
#		rm -rf build

CFLAGS += `pkg-config --cflags --libs python` -fPIC

all: noddy.o
		gcc -shared -Wl,-soname,noddy.so $(CFLAGS) -o noddy.so  noddy.o

clean:
		rm -f *.o *.so *.pyc
