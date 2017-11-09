#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
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
	char Temp[MAX_LENGTH];
	int Counter = 0;
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
	for (int i=0; i < strlen(Buff); i++)
	{
		if (('a'<=Buff[i] && Buff[i]<='z') || ('A'<=Buff[i] && Buff[i]<='Z'))
			Temp[Counter++] = Buff[i] > 96 ? Buff[i] : Buff[i] + 32;
		// Get alpha only and ignore cases
	}
	Temp[Counter] = '\0';
	if (strlen(Temp) == 0)
		return NULL;
	Word = (ElementType)malloc((strlen(Temp) + 1) * sizeof(char));
	Word[strlen(Temp)] = '\0';
	strcpy(Word, Temp);
	return Word;
}


int main(int argc, char const *argv[])
{
	int TableSize = 5000;
	int wordcount = 0;
	HashTable H;
	ElementType Word;
	char document[5 * MAX_LENGTH];
	strcpy(document, argv[0]);
	for (int i=strlen(document) - 1; i >= 0; i--)
	{
		if (document[i] == '/')
			break;
		document[i] = '\0';
	}
	strcat(document, "source.txt");
	FILE * fp;
	H = InitializeTable(TableSize);
	debug(printf("%s\n", document));
	if (NULL == (fp = fopen(document,"r")))
		FatalError("Can not open the file!\n");
	while (!feof(fp))
	{
		Word = GetAWord(fp);
		if (NULL != Word)
		{
			wordcount++;
			printf("%s\n", Word);
			Insert(H, Word);
		}
	}
	fclose(fp);
	printf("Valid words count: %d\n", wordcount);
	for (int i=0;i<H->TableSize;i++)
	{
		printf("%s\n", H->TheLists[i]->Element);
	}
	DestroyTable(H);
	return 0;
}
