#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"

#define _DEBUG
#ifdef _DEBUG
#define debug(code) code
#else
#define debug(code)
#endif

// #define ElementType char *
// #define FatalError(code) fprintf(stderr, code)
// #define Error(code) fprintf(stderr, code)
// #define Empty 0
// #define Legitimate 1


int main(int argc, char const *argv[])
{
	HashTable H = InitializeTable(6000);
	int a = H->TheLists[2]->Frequency;
	printf("%d\n", a);
	return 0;
}





// typedef struct Cell
// {
// 	int Info;
// 	int frequency;
// 	ElementType Element;
// }Cell;


// typedef struct HashTable
// {
// 	int TableSize;
// 	Cell TheCells;
// }HashTable;


// HashTable InitializeTable(int TableSize)
// {
// 	HashTable H;
// 	if (TableSize < MinTableSize)
// 	{
// 		Error("Too small Hash Table!");
// 		return NULL;
// 	}
// 	H = malloc(sizeof(HashTable));
// 	if (NULL == H)
// 		FatalError("No enough space!");
// 	H->TableSize = NextPrime(TableSize);
// 	H->TheCells = malloc(H->TableSize * sizeof(Cell));
// 	if (NULL == H->TheCells)
// 		FatalError("No enough space!");
// 	for (int i=0; i < H->TableSize; i++)
// 		H->TheCells[i].Info = Empty;
// 	return H;
// }


// int Find(ElementType Key, HashTable H)
// {
// 	int CurrentPos, NewPos;
// 	int CNum = 0;
// 	NewPos = CurrentPos = Hash(Key, H->TableSize);
// 	while (H->TheCells[NewPos].Info != Empty &&
// 		   H->TheCells[NewPos].Element != Key)
// 	{
// 		if (++CNum % 2)
// 		{
// 			NewPos = CurrentPos + ((CNum + 1) / 2) * ((CNum + 1) / 2);
// 			while (NewPos >= H->TableSize)
// 				NewPos -= H->TableSize;
// 		}
// 		else
// 		{
// 			NewPos = CurrentPos - (CNum / 2) * (CNum / 2);
// 			while (NewPos < 0)
// 				NewPos += H->TableSize;
// 		}
// 	}
// 	return NewPos;
// }


// void Insert(ElementType Key, HashTable H)
// {
// 	int Pos;
// 	Pos = Find(Key, H);
// 	if (H->TheCells[Pos].Info != Legitimate)
// 	{
// 		H->TheCells[Pos].Info = Legitimate;
// 		H->TheCells[Pos].Element = Key;
// 	}
// }


// int main(int argc, char const *argv[])
// {
// 	int TableSize = 10000;
// 	int wordcount = 0, length;
// 	HashTable H;
// 	ElementType word;
// 	FILE *fp;
// 	char document[] = "source.txt";
// 	H = InitializeTable(TableSize);
// 	if (NULL == (fp = fopen(document, "r")))
// 		FatalError("Can not open the file!\n");
// 	while (!feof(fp))
// 	{
// 		length = GetAWord(fp, word);
// 		if (length > 3)
// 		{
// 			wordcount++;
// 			InsertAndCount(word, H);
// 		}
// 	}
// 	fclose(fp);
// 	printf("Valid words count: %d\n", wordcount);
// 	Show(H, 10.0 / 100);
// 	DestroyTable(H);
// 	return 0;
// }
