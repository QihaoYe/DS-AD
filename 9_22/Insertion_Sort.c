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
	srand(time(NULL));
	int a[N];
	for (int i=0;i<N;i++)
	{
		a[i] = rand() % 100 + 1;
	}
	start = clock();
	insertion_sort(a,N);
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
