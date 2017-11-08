#include <stdio.h>

#define ElementType char *
#define fatal_error(code) fprintf(stderr, code)
#define _DEBUG
#ifdef _DEBUG
#define debug(code) code
#else
#define debug(code)
#endif

typedef struct HashTable
{
	int TableSize;
	Cell TheCells;
}HashTable;

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
