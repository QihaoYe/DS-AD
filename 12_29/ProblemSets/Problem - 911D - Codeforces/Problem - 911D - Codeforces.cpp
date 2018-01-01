#include <iostream>


using namespace std;
void output(int p)
{
	if (1 == p)
		printf("odd\n");
	if (0 == p)
		printf("even\n");
}


int main(int argc, char const *argv[])
{
	int N, i, j, p = 0;
	scanf("%d", &N);
	int * A = new int[N];
	for (i = 0; i < N; i++)
		scanf("%d", A + i);
	for (i = 0; i < N - 1; i++)
		for (j = i + 1; j < N; j++)
			if (A[j] < A[i])
				p = (p + 1) % 2;
	delete[] A;
	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		int x, y, d;
		scanf("%d%d", &x, &y);
		d = (y - x) % 4;
		if (d == 0 or d == 3)
			output(p);
		else
		{
			p = (p + 1) % 2;
			output(p);
		}
	}
	return 0;
}
