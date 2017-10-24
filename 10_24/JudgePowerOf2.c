#include <stdio.h>

int judge(int n)
{
	if ((n & (n - 1)) == 0) return 1;
	return 0;
}

int main(int argc, char const *argv[])
{
	printf("%d\n", judge(16));
	return 0;
}
