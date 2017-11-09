#include <stdio.h>

#define _DEBUG
#ifdef _DEBUG
#define debug(code) code
#else
#define debug(code)
#endif

#define ElementType char *
#define fatal_error(code) fprintf(stderr, code)
#define error(code) fprintf(stderr, code)
#define MinTableSize 5000

typedef struct HashTable
{
	int TableSize;
	ElementType *Cell;
}HashTable;

HashTable initialize_table(int TableSize)
{
	HashTable H;
	if (TableSize < MinTableSize)
	{
		error("Too small Hash Table!");
		return NULL;
	}
	H = (HashTable *)malloc(sizeof(HashTable));
	if (NULL == H)
		fatal_error("No enough space!");
	H->TableSize = NextPrime(TableSize);
	H->Cell = (ElementType *)malloc(TableSize * sizeof(ElementType));
	if (NULL == H->Cell)
		fatal_error("No enough space!");
	for (int i=0; i < H->TableSize; i++)
		H->Cell[i] = NULL;
	return H;
}

int main(int argc, char const *argv[])
{
	int table_size = 10000;
	int wordcount = 0, length;
	HashTable H;
	ElementType word;
	FILE *fp;
	char document[] = "source.txt";
	H = initialize_table(table_size);
	if (NULL == (fp = fopen(document, "r")))
		fatal_error("Can not open the file!\n");
	while (!feof(fp))
	{
		length = get_word(fp, word);
		if (length > 3)
		{
			wordcount++;
			insert_and_count(word, H);
		}
	}
	fclose(fp);
	printf("Valid words count: %d\n", wordcount);
	show(H, 10.0 / 100);
	destroy_table(H);
	return 0;
}
