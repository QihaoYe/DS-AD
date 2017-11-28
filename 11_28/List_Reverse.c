#include <stdio.h>

void reverse(Node ** head)
{
	if (NULL == *head || NULL == (*head)->next)
		return;
	Node * p1 = *head;
	Node * p2 = p1->next;
	Node * p3;
	head->next = NULL
	while (NULL != (p3 = p2->next))
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	p2->next = p1;
	*head = p2;
}