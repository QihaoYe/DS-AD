#include <stdio.h>

int BitCount(unsigned int n)
{
	int result = 0;
	while(n)
	{
		if (n % 2) result++;
		n = n >> 1;
	}
	return result;
}

int main()
{
	int a = BitCount(5);
	printf("%d\n", a);
	return 0;
}
