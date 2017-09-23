# include <stdio.h>

int * merge_sort(int * A,int n1, int * B, int n2, int * C)
{
	int i = 0, j = 0, k = 0;
	while(i < n1 && j < n2)
	{
		if(A[i] < B[j]) C[k+1] = A[i+1];
		else C[k+1] = B[j+1];
		i++;
		j++;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}