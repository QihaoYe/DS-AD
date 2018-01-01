#include <iostream>
#include <algorithm>


using namespace std;
int main(int argc, char const *argv[])
{
    int k[3];
    scanf("%d%d%d", k, k + 1, k + 2);
    sort(k, k + 3);
    if (k[0] == 1)
        printf("YES\n");
    else if (k[0] == 2)
    {
        if (k[1] == 2)
            printf("YES\n");
        else if (k[1] == 4 && k[2] == 4)
            printf("YES\n");
        else
            printf("NO\n");
    }
    else if (k[0] == 3 && k[1] == 3 && k[2] == 3)
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
