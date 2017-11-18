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


int GetAPhoneNum(FILE * fp, ElementType * PhoneNum) // Not valid -> 0; Valid -> 1
{
	char Buff[MAX_LENGTH];
	fscanf(fp, "%s", Buff);
	if (strlen(Buff) == 11)
	{
		*PhoneNum = (ElementType)malloc((12) * sizeof(char));
		strcpy(*PhoneNum, Buff);
		return 1;
	}
	return 0;
}


int main(int argc, char const *argv[])
{
	int TableSize = 50000;
	int wordcount = 0;
	HashTable H;
	ElementType PhoneNum = NULL;

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
		if (GetAPhoneNum(fp, &PhoneNum))
		{
			wordcount++;

			debug(printf("%s\n", PhoneNum));

			Insert(H, PhoneNum);
		}
	}

	fclose(fp);
	printf("%s\t%s\n", "Frequency", "Phone Number");
	printf("-----------------------------\n");
	Show(H);
	printf("Valid phone numbers count: %d\n", wordcount);
	DestroyTable(H);
	return 0;
}
