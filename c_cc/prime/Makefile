all: prime_cc prime_c

prime_cc: ptest_cc.o prime_cc.o
		$(CXX) -o prime_cc ptest_cc.o prime_cc.o

prime_c: ptest_c.o prime.o
		$(CC) -o prime_c prime.o ptest_c.o -lm

clean:
		rm -f *.o prime_c prime_cc
