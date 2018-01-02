#include <iostream>
#include <string.h>


using namespace std;
int main(int argc, char const *argv[])
{
    char first_name[10];
    char last_name[10];
    scanf("%s%s", first_name, last_name);
    int last = (int)last_name[0];
    printf("%c", first_name[0]);
    for (int _ = 1; _ < strlen(first_name); _++)
        if (first_name[_] < last)
            printf("%c", first_name[_]);
        else
            break;
    printf("%c\n", last);
    return 0;
}
