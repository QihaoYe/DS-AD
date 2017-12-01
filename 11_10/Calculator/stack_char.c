#include <stdio.h>
#include <stdlib.h>
#include "stack_char.h"


void stack_char_init(stack_char *s)
{
    s->base = (char *)malloc(maxsize * sizeof(char));
    if(NULL == s->base)
    {
        fprintf(stderr, "No enough space!\n");
        return;
    }
    s->top = s->base;
    s->stacksize = 0;
    stack_char_push(s, '(');
}


int stack_char_null(stack_char *s)
{
    return s->top == s->base;
}


int stack_char_full(stack_char *s)
{
    return s->stacksize == maxsize;
}


void stack_char_push(stack_char *s,char operation)
{
    if(stack_char_full(s))
    {
        fprintf(stderr, "Stack is full, push failed!\n");
        return;
    }
    *((s->top)++) = operation;
    s->stacksize++;
}


void stack_char_pop(stack_char *s)
{
    if(stack_char_null(s))
    {
        fprintf(stderr, "Stack is null, pop failed!\n");
        return;
    }
    s->top--;
    s->stacksize--;
}


char stack_char_top(stack_char *s)
{
    if(stack_char_null(s))
    {
        fprintf(stderr, "Stack is null, top failed!\n");
        return '\0';
    }
    return *(s->top-1);
}


void stack_char_destroy(stack_char *s)
{
    free(s->base);
}

