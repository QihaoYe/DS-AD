#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define bool int
#define true 1
#define false 0


bool IsPalindrome(const char *s)
{
	int n = strlen(s);
	if (!n) return false;
	// In case put in nothing
	const char *p = s + n - 1;
	int i = 0;
	while(i < n / 2)
	{
		if (*(p - i) != *(s + i)) return false;
		i++;
	}
	return true;
}

int main()
{
	clock_t start, finish;
	int N = 3;
	// Set a valid N
	char* str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	// List all the characters in alphabet
	int lstr = strlen(str);
	// Get the length of alphabet
	char* word = (char *)malloc((N+1) * sizeof(char));
	srand(time(NULL));
	// Set a random seed
	for (int i=0;i<N;i++)
	{
		*(word+i) = str[(rand() % lstr)];
	}
	// Get a random string
	start = clock();
	int judge = IsPalindrome(word);
	// Judge if word is palindrome
	finish = clock();
	double duration = (double)(finish - start) / CLOCKS_PER_SEC;
	// Get the total time of sorting
	printf("Word: %s\n", word);
	// Print the word
	judge ? printf("%s is palindrome\n", word) : printf("%s is NOT palindrome\n", word);
	// Print the judgement
	printf( "%f seconds\n", duration);
	// Print out the time of sorting
	free(word);
	return 0;
}
