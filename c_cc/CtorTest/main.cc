#include "CB.h"

int main()
{
	//CB (*a)() = NULL;
	//CB a = CB::Q();
	CB a = []{return CB::Q();}();


	//CB b = a;
	//a.put();
	/*CB a()
	{
		return CB();
	}*/
	
	//CB a = CB();
	//CB c();
	//CB a = CB::Q();
	return 0;
}
