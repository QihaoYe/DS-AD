#include <stdio.h>

#define ElementType char *

int main(int argc, char const *argv[])
{
	int N, i;
	ElementType key;
	HashTable H;
	scanf("%d", &N);
	H = CreatTable(N * 2);
	for (int i=0; i<N; i++)
	{
		scanf("%s", key);
		Insert(H, key);
	}
	ScanAndOutput(H);
	DestroyTable(H);
	return 0;
}