#include <stdio.h>
#include <string.h>

void makeNext(const char P[],int next[])
{
    int q,k;
    int m = strlen(P);
    next[0] = 0;
    for (q = 1,k = 0; q < m; q++)
    {
        while(k > 0 && P[q] != P[k]) k = next[k-1];
        if (P[q] == P[k]) k++;
        next[q] = k;
    }
}

int main(int argc, char const *argv[])
{
	char a[] = "aaabcdabcd";
	int next[strlen(a)];
	makeNext(a, next);
	for (int i=0;i<strlen(a);i++)
	{
		printf("%d\n", next[i]);
	}
	return 0;
}