#include <iostream>


using namespace std;
int main(int argc, char const *argv[])
{
    int n, x, y, _;
    int pos = 0, neg = 0;
    scanf("%d", &n);
    for (_ = 0; _ < n; _++)
    {
        scanf("%d%d", &x, &y);
        if (x > 0)
            pos++;
        if (x < 0)
            neg++;
        if (pos > 1 && neg > 1)
        {
            printf("NO\n");
            return 0;
        }
    }
    printf("Yes\n");
    return 0;
}
