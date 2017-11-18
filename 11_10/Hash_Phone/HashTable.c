#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"


int NotPrime(int N) // Not prime -> 1; Prime -> 0
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


int Hash(int TableSize, ElementType PhoneNum)
{
	unsigned int value = atoi(PhoneNum);
	return value % TableSize;
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
	H->TheLists = (List *)malloc(H->TableSize * sizeof(List));
	if (NULL == H->TheLists)
		FatalError("No enough space!");
	for (int i=0; i < TableSize; i++)
		H->TheLists[i] = NULL;
	return H;
}


Position Find(HashTable H, ElementType PhoneNum)
{
	int HashValue;
	Position Node;
	if (NULL == H)
	{
		FatalError("The Hash Table is not established yet!");
		return NULL;
	}
	HashValue = Hash(H->TableSize, PhoneNum);
	if (NULL == (Node = H->TheLists[HashValue]))
		return NULL;
	while (NULL != Node)
	{
		if (!strcmp(Node->Element, PhoneNum))
			return Node;
		Node = Node->Next;
	}
	return NULL;
}


void Insert(HashTable H, ElementType PhoneNum)
{
	int HashValue;
	List Node;
	List NewPosition;
	if (NULL == H)
	{
		FatalError("The Hash Table is not established yet!");
		return;
	}
	HashValue = Hash(H->TableSize, PhoneNum);
	if (NULL == H->TheLists[HashValue])
	{
		Node = (List)malloc(sizeof(struct ListNode));
		if (NULL == Node)
			FatalError("No enough space!");
		Node->Frequency = 1;
		Node->Element = PhoneNum;
		Node->Next = NULL;
		H->TheLists[HashValue] = Node;
		return;
	}
	if (NULL != (Node = Find(H, PhoneNum)))
	{
		Node->Frequency++;
		return;
	}
	Node = H->TheLists[HashValue];
	while (NULL != Node->Next)
		Node = Node->Next;
	NewPosition = (List)malloc(sizeof(struct ListNode));
	if (NULL == NewPosition)
		FatalError("No enough space!");
	NewPosition->Frequency = 1;
	NewPosition->Element = PhoneNum;
	NewPosition->Next = NULL;
	Node->Next = NewPosition;
}


void quick_process(List * A, int p, int q)
{
	if (p >= q) return;
	int index = p;
	List* i = A + p;
	List key = *(A + p);
	List* sentinel = A + q;
	List temp;
	while (i++ != sentinel)
	{
		if ((*i)->Frequency >= key->Frequency)
		{
			temp = *i;
			*i = *(A + ++index);
			*(A + index) = temp;
		}
	}
	*(A + p) = *(A + index);
	*(A + index) = key;
	quick_process(A, p, index - 1);
	quick_process(A, index + 1, q);
}


void Show(HashTable H)
{
	int index = 0;
	List Node;
	List array[MAX_SIZE];
	for (int i=0; i < H->TableSize; i++)
	{
		if (NULL != (Node = H->TheLists[i]))
			while (NULL != Node)
			{
				array[index++] = Node;
				Node = Node->Next;
			}
	}
	quick_process(array, 0, index - 1);
	// Order the words by their frequency
	// Large -> Small
	for (int i=0; i < index; i++)
		printf("%d\t\t%s\n", array[i]->Frequency, array[i]->Element);
}


void destroy(List * head)
{
	if (NULL == *head || NULL == head) return;
	List p;
	while ((p = (*head)->Next))
	{
		free(*head);
		*head = p;
	}
	free(*head);
	*head = NULL;
}


void DestroyTable(HashTable H)
{
	for (int i=0; i < H->TableSize; i++)
		destroy(&H->TheLists[i]);
	free(H);
}
