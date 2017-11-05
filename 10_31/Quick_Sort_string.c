#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType char *

#define LEN_FISRT
#ifdef LEN_FISRT
#include <string.h>
#define mode_1(code) code
#else
#define mode_1(code)
#endif

int string_cmp(char * A, char * B);

void quick_process(ElementType * A, int p, int q)
{
	if (p >= q) return;
	int index = p;
	ElementType* i = A + p;
	ElementType key = *(A + p);
	ElementType* sentinel = A + q;
	ElementType temp;
	while (i++ != sentinel)
	{
		if (string_cmp(*i, key))
		{
			temp = *i;
			*i = *(A + ++index);
			*(A + index) = temp;
		}
	}
	*(A + p) = *(A + index);
	*(A + index) = key;
	quick_process(A, p, index - 1);
	quick_process(A, index + 1, q);
}


void quick_sort(ElementType * A, int N)
{
	quick_process(A, 0, N-1);
}


char * random_string(int len)
{
	char *str = (char *)malloc((len + 1) * sizeof(char));
	str[len] = '\0';
	while (len-- + 1)
		str[len] = 'a' + rand() % 26;
	return str;
}


int string_cmp(char * A, char * B)
{
	mode_1(if (strlen(A) < strlen(B)) return 1);
	mode_1(if (strlen(A) > strlen(B)) return 0);
	int p = 0;
	while (A[p] != '\0' && B[p] != '\0')
	{
		if (A[p] < B[p]) return 1;
		if (A[p] > B[p]) return 0;
		p++;
	}
	if (A[p] == '\0') return 1;
	if (B[p] == '\0') return 0;
	return 0;
}


int main(int argc, char const *argv[])
{
	clock_t start, finish;
	int N = 100000;
	// Set a large N
	srand(time(NULL));
	// Set a random seed
	ElementType a[N];
	int len;
	for (int i=0;i<N;i++)
	{
		a[i] = random_string(rand() % 14 + 1);
	}
	// Initialize a random array
	start = clock();
	quick_sort(a, N);
	// Quick Sort
	// Order: small -> large
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	// Get the total time of sorting
	for (int i=0;i<N;i++)
	{
		printf("%s ", a[i]);
	}
	printf("\n");
	for (int i=0;i<N;i++)
	{
		free(a[i]);
	}
	// Print out the result
	printf( "%f seconds\n", duration);
	// Print out the time of sorting
	return 0;
}
