# include <stdio.h>

void insertion_sort(int * unsorted, int n)
{
	int i = 0, j = 1, key = 0;
	for(j=1;j<n;++j)
	{
		i = j - 1;
		key = unsorted[j];
		while(i >= 0 && key < unsorted[i])
		{
			unsorted[i+1] = unsorted[i];
			i--;
		}
		unsorted[i+1] = key;
	}
}

int main()
{
	int a[] = {3, 1, 2, 6, 4, 8, 9, 2, 7};
	insertion_sort(a, 9);
	for (int i=0;i<9;i++)
	{
		printf("%d ", *(a+i));
	}
	printf("\n");
	return 0;
}