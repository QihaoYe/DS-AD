#ifdef __STACK_CHAR__
#else
#define __STACK_CHAR__
#define maxsize 128

typedef struct
{
	float *base;
	float *top;
	int stacksize;
}stack_float;

void stack_float_init(stack_float *s);
int stack_float_null(stack_float *s);
int stack_float_full(stack_float *s);
void stack_float_push(stack_float *s,float operation);
void stack_float_pop(stack_float *s);
float stack_float_top(stack_float *s);
void stack_float_destroy(stack_float *s);

#endif
