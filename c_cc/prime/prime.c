#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prime.h"


int Sqrt(double x) {
	  __asm__ ("fsqrt" : "+t" (x));
		  return (int)x;
}

void prime_bitmap(int n)
{
	table = (unsigned long *)malloc(sizeof(unsigned long)* ((n >> 5) + 1));
	memset(table, 0xffff, sizeof(unsigned long) * ((n >> 5) + 1));
	int i, j, k;
	RESETBIT(table, 0);
	RESETBIT(table, 1);
	for(i = 2; i <= Sqrt(n); i++)
		if(TESTBIT(table, i))
			for(k = n/i, j = i * k; k >= i; k--, j-= i)
				if(TESTBIT(table, k))
					RESETBIT(table, j);
}


void prime(int n)
{
	ctable = (char *)calloc(n + 1, sizeof(char));
	int i, j, k;
	ctable[0] = 1;
	ctable[1] = 1;
	for(i = 2; i <= Sqrt(n); i++)
		if(!ctable[i])
			for(k = n/i, j = i * k; k >= i; k--, j-= i)
				if(!ctable[k])
					ctable[j] = 1;
}

