#include <stdio.h>

int bin_search(int arr[], int n, int value)
{
	int low = 0, high = n - 1, mid;
	while (low <= high)
    {
        mid = (low + high) / 2;
        if (arr[mid] == value) return mid; 
        if (arr[mid] > value) high = mid - 1;
        else low = mid + 1;
    }
	return -1;
}

int binS_first(int arr[], int n, int value)
{
	return 1;
}

int main()
{
	int array[] = {1,2,3,4,5};
	int a = bin_search(array, 5, 3);
	printf("%d\n", a);
	return 0;
}
