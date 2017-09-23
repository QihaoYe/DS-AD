#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


void merge(ElementType * A, int low, int mid, int high)
{
	int i = low, j = mid + 1, k = 0;
	ElementType* result = (ElementType *)malloc((high - low + 1) * sizeof(ElementType));
	while (i <= mid  && j <= high)
		*(result+k++) = (*(A+i) <= *(A+j)) ? *(A+i++) : *(A+j++);
	while (i <= mid)
		*(result+k++) = *(A+i++);
	while (j <= high)
		*(result+k++) = *(A+j++);
	for (;k>0;k--)
		*(A+++low) = *(result++);
}


void merge_sort(ElementType * A, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		merge_sort(A, low, mid);
		merge_sort(A, mid+1, high);
		merge(A, low, mid, high);
	}
}


int main(int argc, char const *argv[])
{
	clock_t start, finish;
	int N = 10000;
	srand(time(NULL));
	int a[N];
	for (int i=0;i<N;i++)
	{
		a[i] = rand() % 100 + 1;
	}
	start = clock();
	merge_sort(a, 0, N-1);
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	for (int i=0;i<N;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	printf( "%f seconds\n", duration);
	return 0;
}
