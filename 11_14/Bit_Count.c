#include <stdio.h>


int BitCount3(unsigned int n)
{
	unsigned char BitsSetTable256[256] = {0};

	for (int i=0; i < 256; i++)
		BitsSetTable256[i] = (i & 1) + BitsSetTable256[i >> 1];

	unsigned int c = 0;

	unsigned char *p = (unsigned char *) & n;

	c = BitsSetTable256[p[0]] +
		BitsSetTable256[p[1]] +
		BitsSetTable256[p[2]] +
		BitsSetTable256[p[3]];

	return c;
}


int BitCount4(unsigned int n)
{
	unsigned int table[16] = 
	{
		0, 1, 1, 2,
		1, 2, 2, 3,
		1, 2, 2, 3,
		2, 3, 3, 4
	};

	unsigned int count = 0;
	while (n)
	{
		count += table[n & 0xf];
		n >>= 4;
	}

	return count;
}


 int main(int argc, char const *argv[])
 {
 	int a = BitCount4(134523);
 	printf("%d\n", a);
 	return 0;
 }