#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


void bubble_sort(ElementType * A, int N)
{
	for (int i=N-1;i>0;i--)
	{
		int flag = 1;
		for (int j=0;j<i;j++)
		{
			if (*(A+j) > *(A+j+1))
			{
				ElementType temp = *(A+j);
				*(A+j) = *(A+j+1);
				*(A+j+1) = temp;
				flag = 0;
			}
		}
		if (flag) break;
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
	bubble_sort(a, N);
	// Bubble Sort
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
