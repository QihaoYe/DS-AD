#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include "stack_char.h"
#include "stack_float.h"

#define is_in(sub, group, n) char_is_in(sub, group, 0, n)
int state = 0;
// 0->float, 1->operation
stack_char * s_c;
stack_float * s_f;


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


void get_float_char(char * value, const char * command, int * n)
{
    int dot_num = 0;
    int index = 0;
    char temp;
    while ((*(command + *n) < '9' && *(command + *n) > '0')
           || '.' == *(command + *n)
           || ' ' == *(command + *n))
    {
        temp = *(command + *n);
        if (' ' == temp)
        {
            (*n)++;
            continue;
        }
        if ('.' == temp)
        {
            dot_num++;
            if (dot_num > 2)
            {
//                fprintf(stderr, "Invalid value detected!\n");
                *value = '?';
                break;
            }
            value[index++] = temp;
            (*n)++;
        }
        else
        {
            value[index++] = temp;
            (*n)++;
        }
    }
}


void get_float(float * value, char * temp,const char * command, int * n)
{
    get_float_char(temp, command, n);
    if ('?' == *temp)
        return;
    else
        sscanf(temp, "%f", value);
}


void get_operation(char * operation, const char * command, int * n)
{
    while (' ' == (*operation = *(command + *n)))
        (*n)++;
    if (is_in(*operation, OPERATIONS, 6))
        return;
    else if ('\n' == *operation)
        *operation = 'E';
    else
    {
//        fprintf(stderr, "Invalid operation detected!\n");
        *operation = '?';
    }
}


void set_stack(stack_char * s_c, stack_float * s_f)
{
    float value;
    char operation;
    while (1)
    {
        if (0 == state)
        {
            value = scanf("%f", &value);
            stack_float_push(s_f, value);
            state = 1;
        }
        else if (1 == state)
        {
            get_operation(&operation);
            stack_char_push(s_c, operation);
        }
    }
}

void calculate(stack_char * s_c,
               stack_float s_f,
               char * line,
               char * operation,
               char * temp,
               float * value,
               int *n)
{
    return;
}


int main(int argc, char const *argv[])
{
//    char b = ' ';
    int n = 0;
    float num = 0.0;
    char *buff = (char *)malloc(1000 * sizeof(char));
//    while(NULL != fgets(buff, 1000, stdin))
//    {
//        if (buff[0] == '\n')
//            break;
//        n = 0;
//        while ('E' != b)
//        {
//            scanf(buff + n, "%f", &num);
//            get_operation(&b, buff, &n);
//            n++;
//            printf("%c\n", b);
//            printf("%f\n", num);
//        }
//    }
    buff = "213.2+234.5";
    char * t = (char *)malloc(MAX_FLOAT_SIZE * sizeof(char));
    get_float(&num, t, buff, &n);
    printf("%g\n", num);
    printf("%s\n", t);


//    free(buff);

//    for (int i=0;i<3;i++)
//    {
//        get_operation(&b);
//        printf("%c\n", b);
//    }
//	float a = 0.0;
//	scanf("%f", &a);
//	printf("%.5f\n", a);
//    scanf("%f", &a);
//    printf("%.5f\n", a);
	return 0;
}