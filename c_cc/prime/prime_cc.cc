#include <cstdlib>
#include <cstring>
#include "prime_cc.h"
#include <iostream>

using std::cout;

int Sqrt(double x) {
	  __asm__ ("fsqrt" : "+t" (x));
		  return (int)x;
}


Prime::Prime(int n)
{
	range = n;
	ctable = (char *)calloc(n + 1, sizeof(char));
	ctable[0] = 1;
	ctable[1] = 1;
	for(int i = 2; i <= Sqrt(n); i++)
		if(!ctable[i])
			for(int k = n/i, j = i * k; k >= i; k--, j-= i)
				if(!ctable[k])
					ctable[j] = 1;
}

bool Prime::isprime(int n)const
{
	if(n > range)
	{
		cout<<"out of range"<<std::endl;
		return false;
	}
	if(!ctable[n])
		return true;
	return false;
}

Prime_Bitmap::Prime_Bitmap(int n)
{
	range = n;
	table = (unsigned long *)malloc(sizeof(unsigned long)* ((n >> 5) + 1));
	memset(table, 0xffff, sizeof(unsigned long) * ((n >> 5) + 1));
	RESETBIT(table, 0);
	RESETBIT(table, 1);
	for(int i = 2; i <= Sqrt(n); i++)
		if(TESTBIT(table, i))
			for(int k = n/i, j = i * k; k >= i; k--, j-= i)
				if(TESTBIT(table, k))
					RESETBIT(table, j);
}

bool Prime_Bitmap::isprime(int n)const
{
	if(n > range)
	{
		cout<<"out of range"<<std::endl;
		return false;
	}
	if(TESTBIT(table, n))
		return true;
	return false;
}


