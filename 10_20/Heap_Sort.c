#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int
#define swap(a,b) a=a^b;b=a^b;a=a^b


void heap_adjust(ElementType * A, int i, int N)
{
	ElementType child;
	while (2*i+1<N)
	{
		child = 2 * i + 1;
		if (child < N - 1 && *(A + child) < *(A + child + 1)) child++;
		// Get the larger child
		if (*(A + child) > *(A + i)) {swap(*(A + child), *(A + i));}
		// Let the largest be the parent
		else break;
		i = child;
	}
}


void heap_sort(ElementType * A, int N)
{
	for (int i=N/2-1;i>=0;i--)
		heap_adjust(A, i, N);
	// Inintial the heap
	while (N--)
	{
		swap(*A, *(A + N));
		heap_adjust(A, 0, N);
	}
	// Let the largest one move to the end
}


int main(int argc, char const *argv[])
{
	clock_t start, finish;
	int N = 100000;
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
	heap_sort(a, N);
	// Heap Sort
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
