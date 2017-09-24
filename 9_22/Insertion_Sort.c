#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


void insertion_sort(ElementType * A, int N)
{
	for (int i=1;i<N;i++)
	{
		ElementType temp = *(A+i);
		int j;
		for (j=i;j>0 && temp < *(A+j-1);j--)
		{
			*(A+j) = *(A+j-1);
		}
		*(A+j) = temp;
	}
}


int main(int argc, char const *argv[])
{
	clock_t start, finish;
	int N = 10000;
	// Set a large N
	srand(time(NULL));
	// Set a random seed
	int a[N];
	for (int i=0;i<N;i++)
	{
		a[i] = rand() % 10000 + 1;
	}
	// Initialize a random array
	start = clock();
	insertion_sort(a,N);
	// Insertion Sort
	// Order: small -> large
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	// Get the total time of sorting
	for (int i=0;i<N;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	// Print out the result
	printf( "%f seconds\n", duration);
	// Print out the time of sorting
	return 0;
}
