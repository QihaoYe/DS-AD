#ifdef __HASHTABLE_H__
#else
#define __HASHTABLE_H__


#define FatalError(code) fprintf(stderr, code)
#define Error(code) fprintf(stderr, code)
#define MinTableSize 5000
#define ElementType char *


struct ListNode;
typedef struct ListNode *Position, *List;
struct HashTbl;
typedef struct HashTbl *HashTable;


struct ListNode
{
	int Frequency;
	ElementType Element;
	Position Next;
};


struct HashTbl
{
	int TableSize;
  	List *TheLists;
};


int NotPrime(int N);
int NextPrime(int N);
int Hash(int TableSize, ElementType Word);
HashTable InitializeTable(int TableSize);
void Insert(HashTable H, ElementType Word);


#endif