#include <stdio.h>

int num_of_zero(int n)
{
	int result = 0;
	while (n >= 5)
	{
		n /= 5;
		result += n;
	}
	return result;
}

int main(int argc, char const *argv[])
{
	printf("%d\n", num_of_zero(40));
	return 0;
}