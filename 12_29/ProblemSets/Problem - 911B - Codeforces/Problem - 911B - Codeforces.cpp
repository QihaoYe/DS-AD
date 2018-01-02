#include <iostream>


using namespace std;
int main(int argc, char const *argv[])
{
    int n, a, b, m;
    scanf("%d%d%d", &n, &a, &b);
    for (m = (a + b) / n; m > 0; m--)
    {
    	if (a / m + b / m >= n)
    		break;
    }
    if (a < m)
    	m = a;
    if (b < m)
    	m = b;
    printf("%d\n", m);
    return 0;
}
