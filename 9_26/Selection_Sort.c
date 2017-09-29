#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


void selection_sort(ElementType * A, int N)
{
	for (int i=0;i<N;i++)
	{
		ElementType min = *(A + i);
		int index = i;
		for (int j=i+1;j<N;j++)
		{
			if (*(A + j) < min)
			{
				min = *(A + j);
				index = j;
			}
		}
		*(A + index) = *(A + i);
		*(A + i) = min;
		// Moving ahead the minimum
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
		a[i] = rand() % 1000000 + 1;
	}
	// Initialize a random array
	start = clock();
	selection_sort(a, N);
	// Selection Sort
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
