
all: prime_cc.o ptest_c.o ptest_cc.o prime.o
	$(CXX) -o prime_cc ptest_cc.o prime_cc.o
	$(CC) -o prime_c ptest_c.o prime.o -lm

clean:
	rm -f *.o prime_c prime_cc
