#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


int binary_search_mid(ElementType * A, int N, ElementType value)
{
	int low = 0, high = N-1, mid;
	while (low <= high)
	{
		mid = low + ((high - low) >> 1);
		// In case of overbounded
		if (*(A + mid) == value) return mid;
		if (*(A + mid) > value) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}


int binary_search_left(ElementType * A, int N, ElementType value)
{
	int low = 0, high = N-1, mid;
	while (low <= high)
	{
		mid = low + ((high - low) >> 1);
		// In case of overbounded
		if (*(A + mid) >= value) high = mid;
		else low = mid + 1;
		if (*(A + low) == value) return low;
	}
	return -1;
}


int binary_search_right(ElementType * A, int N, ElementType value)
{
	int low = 0, high = N-1, mid;
	while (low <= high)
	{
		mid = low + ((high - low + 1) >> 1);
		// In case of overbounded
		if (*(A + mid) <= value) low = mid;
		else high = mid - 1;
		if (*(A + high) == value) return high;
	}
	return -1;
}


int main(int argc, char const *argv[])
{
	int N = 100000;
	ElementType a[N];
	FILE* f = fopen("source.txt","r");
	for (int i=0;i<N;i++)
	{
		fscanf(f, "%d", &a[i]);
	}
	fclose(f);
	for (int i=0;i<N;i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	// Read in the ordered array
	clock_t start, finish;
	srand(time(NULL));
	// Set a random seed
	start = clock();
	int find = 2345;
	printf("Any index in array:%d\n", binary_search_mid(a, N, find));
	printf("The lowest index  :%d\n", binary_search_left(a, N, find));
	printf("The highest index :%d\n", binary_search_right(a, N, find));
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	// Get the total time of searching
	printf( "%f seconds\n", duration);
	// Print out the time of sorting
	return 0;
}