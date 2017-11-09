#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include "HashTable.h"

#define _DEBUG
#ifdef _DEBUG
#define debug(code) code
#else
#define debug(code)
#endif

#define MAX_LENGTH 64


ElementType GetAWord(FILE * fp)
{
	char Buff[MAX_LENGTH];
	ElementType Word;
	while (!feof(fp))
	{
		fscanf(fp, "%s", Buff);
		if (strlen(Buff) == 1 && Buff[0] == ' ')
			continue;
		else
			break;
	}
	if (strlen(Buff) == 1 && Buff[0] == ' ')
		return NULL;
	Word = (ElementType)malloc((strlen(Buff) + 1) * sizeof(char));
	fscanf(Buff, "%s", Word);
	return Word;
}


int main(int argc, char const *argv[])
{
	int TableSize = 10000;
	int wordcount = 0, length;
	HashTable H;
	ElementType Word;
	FILE * fp;
	char document[] = "source.txt";
	H = InitializeTable(TableSize);
	if (NULL == (fp = fopen(document,"r")))
		FatalError("Can not open the file!\n");
	while (!feof(fp))
	{
		Word = GetAWord(fp);
		printf("%s\n", Word);
	}
	fclose(fp);
	// HashTable H = InitializeTable(6000);
	// Insert(H, "abcd");
	// Insert(H, "abcd");
	// Insert(H, "abcd");
	// int a = Hash(H->TableSize, "abcd");
	// printf("%d\n", a);
	// printf("%d\n", H->TheLists[a]->Frequency);
	// printf("%s\n", H->TheLists[a]->Element);
	return 0;
}

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
