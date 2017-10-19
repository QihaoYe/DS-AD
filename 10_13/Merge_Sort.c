#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


void merge(ElementType *A, int low, int mid, int high)
{
	ElementType* B = (ElementType *)malloc((high - low + 1) * sizeof(ElementType));
	ElementType* i = A + low;
	ElementType* j = A + mid +1;
	int k = 0;
	while (i != A + mid + 1 && j != A + high + 1)
		*(B + k++) = *i <= *j ? *(i++) : *(j++);
	while (i != A + mid + 1)
		*(B + k++) = *(i++);
	while (j != A + high + 1)
		*(B + k++) = *(j++);
	for (k--;k>=0;k--)
		*(A-- + high) = *(B + k);
	free(B);
}


void merge_process(ElementType *A, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		merge_process(A, low, mid);
		merge_process(A, mid + 1, high);
		merge(A, low, mid, high);
	}
}


void merge_sort(ElementType *A, int N)
{
	merge_process(A, 0, N-1);
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
	merge_sort(a, N);
	// Merge Sort
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