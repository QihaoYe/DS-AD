#include <stdio.h>
#define bool int
#define NOW 37

bool checklanding(int A[], int n, int t, int k)
{
	if (t < NOW) return 0;
	int index = n;
	int before = A[0], after;
	for (int i=0;i<n;i++)
	{
		if (A[i] > t)
		{
			index = i;
			after = A[index];
			break;
		}
	}
	if (index == 0) after = A[1];
	if (abs(t - before) >= k && abs(after - t) >= k) return 1;
	return 0;
}

int main(int argc, char const *argv[])
{
	
	return 0;
}