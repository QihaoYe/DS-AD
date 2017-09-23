#include <stdio.h>
#include <string.h>
#define bool int
#define true 1
#define false 0


bool IsPalindrome(const char *s)
{
	int n = strlen(s);
	if (!n) return false;
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
	int c = IsPalindrome("adsda");
	printf("%d\n", c);
	return 0;
}
