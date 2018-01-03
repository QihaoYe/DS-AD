#include <iostream>
#include <string.h>


using namespace std;
int need_to_count(char a)
{
    if (a == '1' || a == '3' || a == '5' || a == '7' || a == '9')
        return 1;
    if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u')
        return 1;
    return 0;
}


int main(int argc, char const *argv[])
{
    char a;
    int count = 0;
    while (1)
    {
        scanf("%c", &a);
        if (a == '\n')
            break;
        if (need_to_count(a))
            count++;
    }
    printf("%d\n", count);
    return 0;
}
