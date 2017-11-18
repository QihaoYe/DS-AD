#ifdef __HASHTABLE_H__
#else
#define __HASHTABLE_H__


#define FatalError(code) fprintf(stderr, code)
#define Error(code) fprintf(stderr, code)
#define MinTableSize 2000
#define MAX_LENGTH 64
#define MAX_SIZE 100000
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
int Hash(int TableSize, ElementType PhoneNum);
HashTable InitializeTable(int TableSize);
Position Find(HashTable H, ElementType PhoneNum);
void Insert(HashTable H, ElementType PhoneNum);
void quick_process(List * A, int p, int q);
void Show(HashTable H);
void destroy(List * head);
void DestroyTable(HashTable H);


#endif