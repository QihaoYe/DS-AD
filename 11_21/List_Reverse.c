#include <stdio.h>
#include <stdlib.h>
#define ElementType int


typedef struct Node
{
	ElementType key;
	struct Node * next;
}Node;


void reverse(Node **head)
{
	if (NULL == *head || NULL == (*head)->next) return;
	Node * p1 = *head;
	Node * p2 = (*head)->next;
	Node * p3;
	p1->next = NULL;
	while (NULL != (p3 = p2->next))
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	p2->next = p1;
	*head = p2;
}


int main(int argc, char const *argv[])
{
	Node * p1 = (Node *)malloc(sizeof(Node));
	Node * p2 = (Node *)malloc(sizeof(Node));
	Node * p3 = (Node *)malloc(sizeof(Node));
	p1->next = p2;
	p2->next = p3;
	p3->next = NULL;
	printf("%p\n", p1);
	printf("%p\n", p2);
	printf("%p\n", p3);
	reverse(&p1);
	printf("\n");
	printf("%p\n", p1);
	printf("%p\n", p1->next);
	printf("%p\n", p1->next->next);
	printf("%p\n", p1->next->next->next);
	return 0;
}
