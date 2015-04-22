#ifndef OBJECTORIENTED_H
#define OBJECTORIENTED_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <time.h>
#include <unistd.h>

using namespace std;

class ObjectOriented
{
	public:
		static void Sort(int* array, int length);
	protected:
	private:
		static vector<int> Sort(vector<int> list);
};

#endif // OBJECTORIENTED_H
