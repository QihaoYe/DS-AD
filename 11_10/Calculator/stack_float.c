#include <stdio.h>
#include <stdlib.h>
#include "stack_float.h"


void stack_float_init(stack_float *s)
{
    s->base = (float *)malloc(maxsize * sizeof(float));
    if(NULL == s->base)
    {
        fprintf(stderr, "No enough space!\n");
        return;
    }
    s->top = s->base;
    s->stacksize = 0;
}


int stack_float_null(stack_float *s)
{
    return s->top == s->base;
}


int stack_float_full(stack_float *s)
{
    return s->stacksize == maxsize;
}


void stack_float_push(stack_float *s,float operation)
{
    if(stack_float_full(s))
    {
        fprintf(stderr, "Stack is full, push failed!\n");
        return;
    }
    *((s->top)++) = operation;
}


void stack_float_pop(stack_float *s)
{
    if(stack_float_null(s))
    {
        fprintf(stderr, "Stack is null, pop failed!\n");
        return;
    }
    --s->top;
}


float stack_float_top(stack_float *s)
{
    if(stack_float_null(s))
    {
        fprintf(stderr, "Stack is null, top failed!\n");
        return '\0';
    }
    return *(s->top-1);
}


void stack_float_destroy(stack_float *s)
{
    free(s->base);
    free(s);
}

