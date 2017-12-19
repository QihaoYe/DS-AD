#include <iostream>
#define Type int


Type Find(Type * D, int N)
{
	int ntimes = 0;
	Type candidate;
	for (int i = 0; i < N; i++)
	{
		if (ntimes == 0)
		{
			candidate = D[i];
			ntimes += 1;
		}
		else if (candidate == D[i])
			ntimes++;
		else
			ntimes--;
	}
	return candidate;
}


using namespace std;
int main(int argc, char const *argv[])
{
	int a[] = {1,2,3,4,5,1,2,1,2,3,1,2,3,5,1,2,5,4,1,4,6,2,1,1,1,1,1,1,1,1};
	int N = 30;
	printf("%d\n", Find(a, N));
	for (int i = 0; i < N - 1; i++)
	{
		index = 0;

	}
	return 0;
}
