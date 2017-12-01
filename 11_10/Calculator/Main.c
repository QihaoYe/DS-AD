#include <stdio.h>
#include <stdlib.h>
#include "stack_char.h"
#include "stack_float.h"

#define is_in(sub, group, n) char_is_in(sub, group, 0, n)
int state = 0;
// 0->float, 1->operation


int cal_priority(char operation)
{
	switch (operation)
	{
		case '+':
		case '-':return 1;
		case '*':
		case '/':return 2;
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
                fprintf(stderr, "Invalid value detected!\n");
                *value = '?';
                index = 1;
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
    value[index] = '\0';
}


void get_float(float * value, char * temp,const char * command, int * n)
{
    get_float_char(temp, command, n);
    if ('?' == *temp)
        return;
    else
        *value = strtof(temp, NULL);
}


void get_operation(char * operation, const char * command, int * n)
{
    while (' ' == (*operation = *(command + *n)))
        (*n)++;
    if (is_in(*operation, OPERATIONS, 6))
        return;
    else if ('\n' == *operation)
        return;
    else
    {
        fprintf(stderr, "Invalid operation detected!\n");
        *operation = '?';
    }
}


char get_next_char(const char * command, int * n)
{
    while (' ' == *(command + *n))
        (*n)++;
    return *(command + *n);
}

void calculate(stack_char * s_c,
               stack_float * s_f,
               char * line,
               char * operation,
               char * temp,
               float * value,
               int *n)
{
    char next = ' ';
    char last = ' ';
    float f1 = 0.0;
    float f2 = 0.0;
    while (1)
    {
        if (0 == state)
        {
            get_float(value, temp, line, n);
            if ('?' == *temp)
                break;
            stack_float_push(s_f, *value);
            state = 1;
        }
        else if (1 == state)
        {
            get_operation(operation, line, n);
            (*n)++;
            if (!stack_char_null(s_c))
                last = stack_char_top(s_c);
            if ('\n' == *operation)
            {
                while (!stack_char_null(s_c))
                {
                    last = stack_char_top(s_c);
                    f2 = stack_float_top(s_f);
                    stack_float_pop(s_f);
                    if (stack_float_null(s_f))
                    {
                        fprintf(stderr, "Not a valid formula!\n");
                        state = -1;
                        break;
                    }
                    f1 = stack_float_top(s_f);
                    stack_float_pop(s_f);
                    switch (last) {
                        case '+':
                            stack_float_push(s_f, f1 + f2);
                            break;
                        case '-':
                            stack_float_push(s_f, f1 - f2);
                            break;
                        case '*':
                            stack_float_push(s_f, f1 * f2);
                            break;
                        case '/':
                            stack_float_push(s_f, f1 / f2);
                            break;
                        default:
                            break;
                    }
                    stack_char_pop(s_c);
                }
                state = 0;
                if (1 == s_f->stacksize)
                {
                    printf("= %g\n", stack_float_top(s_f));
                    stack_float_pop(s_f);
                }
                else
                {
                    stack_char_destroy(s_c);
                    stack_float_destroy(s_f);
                    stack_char_init(s_c);
                    stack_float_init(s_f);
                }
                break;
            }
            if ('?' == *operation)
                break;
            if (stack_char_null(s_c) || cal_priority(last) < cal_priority(*operation))
                stack_char_push(s_c, *operation);
            else
            {
                while (cal_priority(last) >= cal_priority(*operation))
                {
                    f2 = stack_float_top(s_f);
                    stack_float_pop(s_f);
                    f1 = stack_float_top(s_f);
                    stack_float_pop(s_f);
                    switch (last)
                    {
                        case '+':
                            stack_float_push(s_f, f1 + f2);
                            break;
                        case '-':
                            stack_float_push(s_f, f1 - f2);
                            break;
                        case '*':
                            stack_float_push(s_f, f1 * f2);
                            break;
                        case '/':
                            stack_float_push(s_f, f1 / f2);
                            break;
                        default:
                            break;
                    }
                    stack_char_pop(s_c);
                    if (stack_char_null(s_c))
                        break;
                    else
                        last = stack_char_top(s_c);
                }
                stack_char_push(s_c, *operation);
            }
            state = 2;
        }
        else if (2 == state)
        {
            next = get_next_char(line, n);
            if (next < '9' && next > '0')
                state = 0;
            else
                state = 1;
        }
    }
}


int main(int argc, char const *argv[])
{
    stack_char * s_c = (stack_char *)malloc(sizeof(stack_char));
    stack_float * s_f = (stack_float *)malloc(sizeof(stack_float));
    char * line = (char *)malloc(MAX_BUFF * sizeof(char));
    char * operation = (char *)malloc(sizeof(char));
    char * temp = (char *)malloc(MAX_FLOAT_SIZE * sizeof(char));
    float value = 0.0;
    int n = 0;
    stack_char_init(s_c);
    stack_float_init(s_f);
    while (NULL != fgets(line, MAX_BUFF, stdin))
    {
        if ('\n' == *line)
            break;
        n = 0;
        calculate(s_c, s_f, line, operation,temp, &value, &n);
    }
    stack_char_destroy(s_c);
    stack_float_destroy(s_f);
    free(s_c);
    free(s_f);
    free(line);
    free(operation);
    free(temp);
    return 0;
}
