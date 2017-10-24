#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef struct Tree
{
	int key;
	int h;
	struct Tree* left;
	struct Tree* right;
	struct Tree* parent;
}Tree;

void init_tree(Tree * node)
{
	node->key = 0;
	node->h = -1;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
}

int calh(Tree * r)
{
	if (NULL == r)
		return -1;
	if (NULL == r->left && NULL == r->right)
	{
		(r->h) = 0;
		return 0;
	}
	else
	{
		r->h = max(calh(r->left), calh(r->right)) + 1;
		return r->h;
	}
}

int main(int argc, char const *argv[])
{
	Tree a;
	init_tree(&a);
	Tree b;
	init_tree(&b);
	Tree c;
	init_tree(&c);
	a.left = &b;
	a.right = &c;
	printf("%d\n", calh(&a));
	Tree* N = &a;
	printf("Loc   \t%p\n", N);
	printf("key   \t%d\n", N->key);
	printf("h     \t%d\n", N->h);
	printf("left  \t%p\n", N->left);
	printf("right \t%p\n", N->right);
	printf("parent\t%p\n", N->parent);
	printf("----------------------\n");
	N = &b;
	printf("Loc   \t%p\n", N);
	printf("key   \t%d\n", N->key);
	printf("h     \t%d\n", N->h);
	printf("left  \t%p\n", N->left);
	printf("right \t%p\n", N->right);
	printf("parent\t%p\n", N->parent);
	printf("----------------------\n");
	N = &c;
	printf("Loc   \t%p\n", N);
	printf("key   \t%d\n", N->key);
	printf("h     \t%d\n", N->h);
	printf("left  \t%p\n", N->left);
	printf("right \t%p\n", N->right);
	printf("parent\t%p\n", N->parent);
	printf("----------------------\n");
	return 0;
}
