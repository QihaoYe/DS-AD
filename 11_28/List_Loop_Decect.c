#include <stdio.h>

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