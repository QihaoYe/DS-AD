#include <iostream>
#define MAX_N 100001


using namespace std;
int main(int argc, char const *argv[])
{
	int N, i, index, num, min = INT_MAX;
	scanf("%d", &N);
	int A[MAX_N];
	for (i = 0; i < N; i++)
	{
		scanf("%d", &num);
		if (num < min)
		{
			min = num;
			index = 0;
		}
		if (num == min)
		{
			A[index] = i;
			A[++index] = -1;
		}
	}
	min = INT_MAX;
	for (i = 1; i < N; i++)
	{
		if (A[i] < 0)
			break;
		if (A[i] - A[i - 1] < min)
			min = A[i] - A[i - 1];
		if (min == 1)
			break;
	}
	printf("%d\n", min);
	return 0;
}
