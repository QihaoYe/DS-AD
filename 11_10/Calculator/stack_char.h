#ifdef __STACK_CHAR__
#else
#define __STACK_CHAR__
#include "initial_value.h"

typedef struct
{
	char *base;
	char *top;
	int stacksize;
}stack_char;

void stack_char_init(stack_char *s);
int stack_char_null(stack_char *s);
int stack_char_full(stack_char *s);
void stack_char_push(stack_char *s,char operation);
void stack_char_pop(stack_char *s);
char stack_char_top(stack_char *s);
void stack_char_destroy(stack_char *s);

#endif
