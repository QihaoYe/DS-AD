#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


int binary_search(static Table *Tb1, ElementType k)
{
	int left, right, mid, NoFound = -1;
	left = 1;
	right = Tb1->length;
	while (left <= right)
	{
		mid = left + (right - left) >> 1;
		// In case out of memory
		if (k <  Tb1->Element[mid]) right = mid - 1;
		else if (k > Tb1->Element[mid]) left = mid + 1;
		else return mid;
	}
	return NoFound;
}



int main(int argc, char const *argv[])
{
	return 0;
}
