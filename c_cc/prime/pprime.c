#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * ctable;
int inline sqrt14(double n)
{
	__asm__ (	"fsqrt;": "+t"  (n));
	return (int)n;
} 


void prime(int n)
{
	ctable = (char *)calloc(n + 1, sizeof(char));
	int i, j, k;
	ctable[0] = 1;
	ctable[1] = 1;
	for(i = 2; i <= sqrt14(n); i++)
		if(!ctable[i])
			for(k = n/i, j = i * k; k >= i; k--, j-= i)
				if(!ctable[k])
					ctable[j] = 1;
}

int main() {
	long int minnum,maxnum, i;
	short int j, no = 0;
	char numstr[9];
	printf("input <lower bound> <upper bound>:");

	scanf("%ld %ld", &minnum, &maxnum);
	if(maxnum >= 100000000)
		maxnum = 9999999;
	prime(sqrt14(maxnum));
	for(i = minnum + 1 - minnum % 2; i <= maxnum; i = i + 2) 
	{
		sprintf(numstr, "%ld", i);
		int numlen = strlen(numstr);
		if(numlen % 2 != 0 || numlen == 2)
		{
			for(j = 0; j < numlen / 2; j++)//palindrome checking 
			{
				if(numstr[j] != numstr[numlen - j - 1]) 
				{
					no = 1;
					break;
				}
			}
			if(no == 0)//prime checking 
			{
				for(j = 3; j <= sqrt14(i); j = j + 2) 
				{	
					if(!ctable[j] && (i%j == 0)) 
					{
						no=1;
						break;
					}
				}
				if(no == 0) 
				{	
					printf("%ld\n",i);
				}
			}
			no = 0;
		}
	}
	return 0;
}
