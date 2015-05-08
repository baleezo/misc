#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "prime.h"


int main(int argc, char **argv)
{
	int range = 0;
	if(argc < 2)
	{
		printf("uasge: %s <range>\n", argv[0]);
		return 0;
	}
	else
	{
		range = atoi(argv[1]);
	}
	//scanf(" %d", &range);
	int width = log10(range) + 1;

	prime_bitmap(range);
	#if 1
	int i, cnt = 0;
	for(i = 2; i <=range; i++)
		if(TESTBIT(table, i))
		{
			printf("%*d", width, i);	
			cnt++;
			if(cnt%10 == 0)
				puts("");
		}
	puts("");
	#endif
	//for(i = 2; i <= range; i++)
	//	if(!ctable[i])
	//	{
	//		printf(" %5d", i);	
	//		cnt++;
	//		if(cnt%10 == 0)
	//			puts("");
	//	}
	return 0;	
}
