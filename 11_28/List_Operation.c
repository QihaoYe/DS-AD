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


int hasloop(Node * head)
{
	if (NULL == head)
		return 0;
	Node * p1 = head;
	Node * p2 = head;
	while (NULL != p2->next && NULL != (p2 = p2->next->next))
	{
		p1 = p1->next;
		if (p1 == p2)
			return 1;
	}
	return 0;
}


int isintersect(Node * head1, Node * head2)
{
	if (!head1 || !head2)
		return 0;
	Node * p1 = head1;
	Node * p2 = head2;
	while (NULL != p1->next)
		p1 = p1->next;
	while (NULL != p2->next)
		p2 = p2->next;
	return p1 == p2;
}


Node * last_kth(Node * head, int k)
{
	Node *p, *q;
	p = q = head;
	int count = 0;
	while (p && count < k)
	{
		p = p->next;
		count++;
	}
	if (p == NULL && count != k)
	{
		fprintf(stderr, "Too big k!\n");
		return NULL;
	}
	while (p)
	{
		p = p->next;
		q = q->next;
	}
	return q;
}

