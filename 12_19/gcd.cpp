#include <iostream>


using namespace std;


int gcd(int a, int b)
{
	return (!b) ? a : gcd(b, a % b);
}

int gcd2(int a, int b)
{
	if (a < b)
		swap(a, b);
	return a == b ? a : gcd2(a - b, b);
}


int main(int argc, char const *argv[])
{
	printf("%d\n", gcd2(3121312, 1231384));
	return 0;
}
