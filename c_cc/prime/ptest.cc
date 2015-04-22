#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "prime_cc.h"

using namespace std;

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		puts("uasge:prime <range>");
		return 0;
	}
	int range = atoi(argv[1]);
	int width = log10(range) + 1;
	Prime_Bitmap table(range);
	for(int i = 2, cnt = 0; i <= range; i++)
	{
		if(table.isprime(i))
		{
			cout.width(width);
			cout<<i;
			cnt++;
			if(cnt % 10 == 0)
			{
				cout<<endl;
			}
		}

	}
	cout<<endl;
	return 0;
	
}
