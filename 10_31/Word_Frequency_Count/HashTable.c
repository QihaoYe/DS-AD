#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"


int NotPrime(int N)
{
	if (N == 2 || N == 3)
		return 0;
	if (N % 2 == 0 || N % 3 == 0)
		return 1;
	for (int i=5; i * i <= N; i += 6)
		if (N % i == 0 || N % (i + 2) == 0)
			return 1;
	return 0;
}


int NextPrime(int N)
{
	N = N % 2 ? N : N - 1;
	while (NotPrime(N = N + 2));
	return N;
}


int Hash(int TableSize, ElementType Word)
{
	int shift = 0;
	unsigned long long value = 0;
	while (*Word != '\0')
	{
		value += *Word << shift;
		shift += 5;
		Word++;
	}
	return (int)value % TableSize;
}


HashTable InitializeTable(int TableSize)
{
	HashTable H;
	if (TableSize < MinTableSize)
	{
		Error("Too small Hash Table!");
		return NULL;
	}
	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (NULL == H)
		FatalError("No enough space!");
	H->TableSize = NextPrime(TableSize);
	H->TheLists = (List *)malloc(H->TableSize * sizeof(struct ListNode));
	if (NULL == H->TheLists)
		FatalError("No enough space!");
	for (int i=0; i < TableSize; i++)
		H->TheLists[i] = NULL;
	return H;
}


void Insert(HashTable H, ElementType Word)
{
	int HashValue;
	if (NULL == H)
	{
		FatalError("The Hash Table is not established yet!");
		return;
	}
	HashValue = Hash(H->TableSize, Word);
	// if (NULL == H->TheLists[HashValue])
}

