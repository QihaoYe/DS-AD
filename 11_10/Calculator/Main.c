#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_char.h"
#include "stack_float.h"
#define is_in(sub, group, n) char_is_in(sub, group, 0, n)
static char * OPERATION = "+-*/()";


int cal_priority(char operation)
{
	switch (operation)
	{
		case '+':
		case '-':return 1;
		case '*':
		case '/':return 2;
//        case '^':return 3;
		default:return -1;
	}
}


int char_is_in(char sub, char * group,int start, int length)
{
    for (int i=start; i < length; i++)
        if (sub == group[i])
            return 1;
    return 0;
}


void get_operation(char * operation)
{
    scanf("%c", operation);
    while (' ' == *operation)
        scanf("%c", operation);
    if (is_in(*operation, OPERATION, 6))
        return;
    else
    {
        fprintf(stderr, "Invalid operation detected!\n");
        *operation = '?';
    }
}


void calculate()
{
    return;
}


int main(int argc, char const *argv[])
{
    char b;
    for (int i=0;i<3;i++)
    {
        get_operation(&b);
        printf("%c\n", b);
    }
//	float a = 0.0;
//	scanf("%f", &a);
//	printf("%.5f\n", a);
//    scanf("%f", &a);
//    printf("%.5f\n", a);
	return 0;
}