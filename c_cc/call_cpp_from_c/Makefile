all: test

test: main.o cppm.o
		g++ $^ -o test

clean:
		rm -f *.o test
