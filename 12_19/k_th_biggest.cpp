#include <iostream>


using namespace std;


void adjustHeap (int *pArray, int rootIndex, int heapSize)
{
    int minIndex = rootIndex;
    int leftIndex = 2 * rootIndex + 1;
    int rightIndex = leftIndex + 1;
    if ((leftIndex < heapSize) && (rightIndex < heapSize) && (pArray[leftIndex] < pArray[rootIndex]))
        minIndex = leftIndex;
    if ((leftIndex < heapSize) && (rightIndex >= heapSize) && (pArray[leftIndex] < pArray[rootIndex]))
        minIndex = leftIndex;
    if ((rightIndex < heapSize) && (pArray[rightIndex] < pArray[leftIndex]) && (pArray[rightIndex] < pArray[rootIndex]))
        minIndex = rightIndex;
    if (minIndex != rootIndex) 
    {
        swap(pArray[rootIndex], pArray[minIndex]);
        adjustHeap(pArray, minIndex, heapSize);
    }
}

void update_heap(...)
{
	if (x > h[0])
	{
		h[0] = x;
		p = 0;
		while (p < k)
		{
			q = 2 * p + 1;
			if (q >= k)
				break;
			if (q < k - 1 && h[q + 1] < h[q])
				q++;
			if (h[q] < h[p])
			{
				swap(h[p], h[q]);
				p = q;
			}
			else
				break;
		}
	}
}


int main(int argc, char const *argv[])
{
	
	return 0;
}

