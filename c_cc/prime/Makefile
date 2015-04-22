SHELL=/bin/bash

prime: prime_cc.o ptest.o ptestc.o prime.o
	$(CXX) -o prime ptest.o prime_cc.o
	$(CC) -o primec ptestc.o prime.o -lm
#primec: ptestc.o prime.o
#	$(CC) -o primec ptestc.o prime.o -lm

ptestc.o: ptest.c
	$(CC) -c ptest.c -o ptestc.o

ptest.o: ptest.cc
	$(CXX) -c ptest.cc #-o ptest.o

clean:
	@rm *.o primec prime
