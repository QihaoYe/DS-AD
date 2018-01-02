#include <iostream>


using namespace std;
int main(int argc, char const *argv[])
{
    int n, k, _, m = 1;
    scanf("%d%d", &n, &k);
    int * p = new int[k];
    int * stack = new int[k + 1];
    stack[0] = n + 1;
    int top = 0;
    for (_ = 0; _ < k; _++)
    {
        scanf("%d", &p[_]);
        stack[++top] = p[_];
        while (stack[top] == m)
        {
            m++;
            top--;
        }
        if (top > 0 && stack[top] > stack[top - 1])
        {
            printf("%d\n", -1);
            delete[] p;
            delete[] stack;
            return 0;
        }
    }
    for (_  = 0; _ < k; _++)
        printf("%d ", p[_]);
    int last = m - 1;
    while (top >= 0)
    {
        for (_ = stack[top] - 1; _ > last; _--)
            printf("%d ", _);
        last = stack[top];
        top--;
    }
    printf("\n");
    delete[] p;
    delete[] stack;
    return 0;
}
