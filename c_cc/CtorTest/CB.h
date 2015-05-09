#ifndef _CB_H
#define _CB_H
#include <cstdio>
class CB
{
public:
		
	CB(int a = 1)
	{
		
		printf("ctor %d\n", a);
	}

	CB(const CB &cb)
	{
		printf("cp ctor\n");
	}

	CB &operator=(const CB &cb)
	{
		printf("cp assignment\n");
		return *this;
	}

	static CB Q()
	{
		return CB();
	}

	void put()
	{
		puts("cctor");
	}
};

#endif
