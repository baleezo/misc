#include "qsort.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#define SIZE 20000
#define TTIME 10
#define SWAP(x,y) {int t; t = x; x = y; y = t;} 
#include <omp.h>


void quickSort(int number[], int left, int right) { 
	if(left < right) { 
		int i = left; 
		int j = right + 1; 

		while(1) { 
			while(i + 1 < SIZE && number[++i] < number[left]) ;  
			while(j -1 > -1 && number[--j] > number[left]) ;  
			if(i >= j) 
				break; 
			SWAP(number[i], number[j]); 
		} 

		SWAP(number[left], number[j]); 

		quickSort(number, left, j-1);   
		quickSort(number, j+1, right); 
	} 
} 


void selectionSort(int number[]) { 
	int i; 
	for(i = 0; i < SIZE-1; i++) { 
		int m = i; 
		int j;
		for(j = i+1; j < SIZE; j++) 
			if(number[j] < number[m]) 
				m = j; 

		if(i != m) 
			SWAP(number[i], number[m]) 
	} 
} 

using namespace std;

int main()
{
	int a[SIZE] = {0};
	srand(time(NULL));

	for(int i = 0; i < SIZE; i++)
	{
		a[i] = (rand()%SIZE) + 1;
	}

	int mt = omp_get_max_threads();
	cout<<"max threads = "<<mt<<endl;

	omp_set_num_threads(mt);

	int i;
	#pragma omp parallel for
	for(i = 0; i < 4; i++)
	{
		int b[SIZE] = {0};
		memcpy(b, a, sizeof(int) *  SIZE);
		if(i%2)
		{
			cout <<"QSORT"<<endl;
			quickSort(a, 0, SIZE);
		}
		else
		{
			cout <<"SSORT"<<endl;
			selectionSort(a);
		}
	}

	//for(int i = 0; i < SIZE; i++)
	//	cout<<b[i]<<" ";
	return 0;
}
