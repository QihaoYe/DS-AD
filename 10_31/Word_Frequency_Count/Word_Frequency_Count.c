#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <String.h>
#include "HashTable.h"

// #define _DEBUG
#ifdef _DEBUG
#define debug(code) code
#else
#define debug(code)
#endif


int GetAWord(FILE * fp, ElementType * Word) // Not valid -> 0; Valid -> 1
{
	char Buff[MAX_LENGTH];
	char Temp[MAX_LENGTH];
	int Counter = 0;
	fscanf(fp, "%s", Buff);
	if (strlen(Buff) == 1 && Buff[0] == ' ')
		return 0;
	for (int i=0; i < strlen(Buff); i++)
	{
		if (('a' <= Buff[i] && Buff[i] <= 'z') || ('A' <= Buff[i] && Buff[i] <= 'Z'))
			Temp[Counter++] = Buff[i] > 96 ? Buff[i] : Buff[i] + 32;
		// Get alpha only and change into lower cases
	}
	Temp[Counter] = '\0';
	if (strlen(Temp) == 0)
		return 0;
	*Word = (ElementType)malloc((strlen(Temp) + 1) * sizeof(char));
	strcpy(*Word, Temp);
	return 1;
}


int main(int argc, char const *argv[])
{
	int TableSize = 3000;
	int wordcount = 0;
	HashTable H;
	ElementType Word = NULL;

	char document[5 * MAX_LENGTH];
	strcpy(document, argv[0]);
	for (int i=strlen(document) - 1; i >= 0; i--)
	{
		if (document[i] == '/')
			break;
		document[i] = '\0';
	}
	strcat(document, "source.txt");
	// Get the absolute path of the source document

	FILE * fp;
	H = InitializeTable(TableSize);

	debug(printf("%s\n", document));

	if (NULL == (fp = fopen(document,"r")))
		FatalError("Can not open the file!\n");

	while (!feof(fp))
	{
		if (GetAWord(fp, &Word))
		{
			wordcount++;

			debug(printf("%s\n", Word));

			Insert(H, Word);
		}
	}

	fclose(fp);
	printf("%s\t%s\n", "Frequency", "Word");
	printf("-----------------------------\n");
	Show(H);
	printf("Valid words count: %d\n", wordcount);
	DestroyTable(H);
	return 0;
}
