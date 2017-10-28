#include <stdio.h>
#include <stdlib.h>

#define ElementType int
#define bool int
#define True 1
#define False 0

// #define _DEBUG
#ifdef _DEBUG
#define Debug(code) code
#else
#define Debug(code) 
#endif


typedef struct ListNode
{
	ElementType value;
	struct ListNode* next;
}ListNode;


ListNode * create(int N)
{
	if (1 > N)
	{
		fprintf(stderr, "%s\n", "Invalid length of linked list!");
		return NULL;
	}

	ListNode * head = NULL;
	ListNode * p1   = NULL;
	ListNode * p2   = NULL;

	p1 = (ListNode *)malloc(sizeof(ListNode));
	if (NULL == p1)
	{
		fprintf(stderr, "%s\n", "Allocate space fail!");
		return NULL;
	}
	else
	{
		p1->value = 0;
		head = p2 = p1;
	}
	
	while (--N)
	{
		p1 = (ListNode *)malloc(sizeof(ListNode));
		if (NULL == p1)
		{
			fprintf(stderr, "%s\n", "Allocate space fail!");
			return NULL;
		}
		else
		{
			p1->value = 0;
			p2->next = p1;
			p2 = p1;
		}
	}
	p2->next = NULL;
	return head;
}


void destroy(ListNode ** head)
{
	if (NULL == *head || NULL == head) return;
	ListNode * p;
	while ((p = (*head)->next))
	{
		free(*head);
		*head = p;
	}
	free(*head);
	*head = NULL;
}


int calculate_length(ListNode * head)
{
	if (NULL == head) return 0;
	int n = 1;
	while ((head = head->next)) n++;
	return n;
}


void delete(ListNode ** head, int i)
{
	do
	{
		if (NULL == *head)
		{
			fprintf(stderr, "%s\n", "Invalid head selected!");
			break;
		}
		if (0 > i)
		{
			fprintf(stderr, "%s\n", "Invalid index selected!");
			break;
		}
		ListNode * p1 = *(head);
		if (i == 0)
		{
			*head = (*head)->next;
			free(p1);
			break;
		}
		ListNode * p2;
		while ((p2 = p1->next) && --i) p1 = p2;
		if (NULL == p2)
		{
			fprintf(stderr, "%s\n", "Index out of bound!");
			break;
		}
		p1->next = p2->next;
		free(p2);
	} while (0);
}


bool search(ListNode * head, ElementType key)
{
	while (head)
	{
		if (key == head->value) return True;
		head = head->next;
	}
	return False;
}


ElementType * get_value_pointer(ListNode * head, int i)
{
	do
	{
		if (NULL == head)
		{
			fprintf(stderr, "%s\n", "Invalid head selected!");
			break;
		}
		if (0 > i)
		{
			fprintf(stderr, "%s\n", "Invalid index selected!");
			break;
		}
		while (i-- && (head = head->next));
		if (NULL == head)
		{
			fprintf(stderr, "%s\n", "Index out of bound!");
			break;
		}
		return &(head->value);
	} while (0);
	return NULL;
}


ElementType get_value(ListNode * head, int i)
{
	return *get_value_pointer(head, i);
}


void print(ListNode * head)
{
	if (NULL != head)
	{
		printf("%d ", head->value);
		Debug(printf("%p %p\n", head, head->next);)
		print(head->next);
	}
	else printf("\n");
}


void insert(ListNode ** head, int i, ListNode * node)
{
	do
	{
		if (NULL == *head)
		{
			fprintf(stderr, "%s\n", "Invalid head selected!");
			break;
		}
		if (0 > i)
		{
			fprintf(stderr, "%s\n", "Invalid index selected!");
			break;
		}
		ListNode * p1 = *(head);
		if (i == 0)
		{
			node->next = p1;
			*head = node;
			break;
		}
		ListNode * p2;
		while ((p2 = p1->next) && --i) p1 = p2;
		if (NULL == p2 && i > 1)
		{
			printf("%d\n", i);
			fprintf(stderr, "%s\n", "Index out of bound!");
			break;
		}
		p1->next = node;
		node->next = p2;
	} while(0);
}


ListNode * merge(ListNode * A, ListNode * B)
{
	if (NULL == A) return B;
	ListNode * p1 = A;
	ListNode * p2;
	while ((p2 = p1->next)) p1 = p2;
	p1->next = B;
	return A;
}


void reverse(ListNode ** head)
{
	ListNode* p1;
	ListNode* p2;
	if (NULL == (p1 = *head) || NULL == (p2 = (*head)->next)) return;
	ListNode* p3;
	(*head)->next = NULL;
	while ((p3 = p2->next))
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	p2->next = p1;
	*head = p2;
}


ListNode * reversed(ListNode * head)
{
	if (NULL == head || NULL == head->next) return head;
	ListNode* p1 = head;
	ListNode* p2 = head->next;
	ListNode* p3;
	head->next = NULL;
	while ((p3 = p2->next))
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
	}
	p2->next = p1;
	return p2;
}


// ---[test zone]---
void test(ListNode * head)
{
	int n = 0;
	while ((head = head->next)) head->value = ++n;
}


int main(int argc, char const *argv[])
{
	ListNode * a, * b, * c = (ListNode *)malloc(sizeof(ListNode));
	a = create(10);
	b = create(5);
	// c = create(1);
	c->value = 999;
	c->next = NULL;
	test(a);
	// Initialize
	printf("%s", "a[] = ");
	print(a);
	printf("%s", "b[] = ");
	print(b);
	printf("%s", "c[] = ");
	print(c);

	printf("\n");
	printf("a.length = %d\n", calculate_length(a));

	printf("\n");
	delete(&a, 6);
	printf("%s\n", "---Delete a[6]---");
	printf("%s", "a[] = ");
	print(a);

	printf("\n");
	printf("Search 3 in a: %d\n", search(a, 3));
	printf("Search 6 in a: %d\n", search(a, 6));
	printf("Search 123 in a: %d\n", search(a, 123));

	printf("\n");
	printf("a[5] = %d\n", get_value(a, 5));

	printf("\n");
	printf("%s\n", "---Insert c at a[9]---");
	insert(&a, 9, c);
	print(a);
	print(c);
	// printf("%s\n", "---Insert c at a[4]---");
	// insert(&a, 4, c);
	// print(a);
	// printf("%s\n", "---Insert c at a[0]---");
	// insert(&a, 0, c);
	// print(a);

	a = merge(a, b);
	print(a);
	reverse(&a);
	print(a);
	a = reversed(a);
	print(a);
	destroy(&a);
	print(a);
	printf("Length: %d\n", calculate_length(a));
	return 0;
}
