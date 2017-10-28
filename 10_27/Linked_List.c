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
// Debug switch


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
// Free all the spaces in the list and redirect the head to the NULL pointer


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
	// If we get NULL, then this program will abort
}


void print(ListNode * head)
{
	if (NULL != head)
	{
		printf("%d ", head->value);
		Debug(printf("%p %p\n", head, head->next);)
		print(head->next);
		// Recursion
	}
	else printf("\n");
}


void insert(ListNode ** head, int i, ElementType key)
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
		ListNode * node = create(1);
		node->value = key;
		ListNode * p1 = *(head);
		if (i == 0)
		{
			node->next = p1;
			*head = node;
			break;
		}
		ListNode * p2;
		while ((p2 = p1->next) && --i) p1 = p2;
		if (NULL == p2 && i > 1) // Allow to insert at the end fo the list
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
	ListNode * a, * b;
	a = create(10);
	b = create(5);
	test(a);
	// Initialize
	printf("%s", "a[] = ");
	print(a);
	printf("%s", "b[] = ");
	print(b);

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
	for (int i=0;i<calculate_length(a);i++)
		printf("a[%d] = %d\n", i, get_value(a, i));

	printf("\n");
	printf("%s\n", "---Insert 111 at a[0]---");
	insert(&a, 0, 111);
	print(a);
	printf("%s\n", "---Insert 222 at a[5]---");
	insert(&a, 5, 222);
	print(a);
	printf("%s\n", "---Insert 333 at a[11]---");
	insert(&a, 11, 333);
	print(a);

	printf("\n");
	printf("%s\n", "---Merge a[] and b[] as a[]---");
	a = merge(a, b);
	printf("%s", "a[] = ");
	print(a);

	printf("\n");
	printf("%s\n", "---Reverse a[]---");
	reverse(&a);
	printf("%s", "a[] = ");
	print(a);
	printf("%s\n", "---Reverse a[]---");
	a = reversed(a);
	printf("%s", "a[] = ");
	print(a);

	printf("\n");
	printf("%s\n", "---Destroy a[]---");
	destroy(&a);
	printf("%s", "a[] = ");
	print(a);
	return 0;
}

// -----[test result]-----
// a[] = 0 1 2 3 4 5 6 7 8 9 
// b[] = 0 0 0 0 0 

// a.length = 10

// ---Delete a[6]---
// a[] = 0 1 2 3 4 5 7 8 9 

// Search 3 in a: 1
// Search 6 in a: 0
// Search 123 in a: 0

// a[0] = 0
// a[1] = 1
// a[2] = 2
// a[3] = 3
// a[4] = 4
// a[5] = 5
// a[6] = 7
// a[7] = 8
// a[8] = 9

// ---Insert 111 at a[0]---
// 111 0 1 2 3 4 5 7 8 9 
// ---Insert 222 at a[5]---
// 111 0 1 2 3 222 4 5 7 8 9 
// ---Insert 333 at a[11]---
// 111 0 1 2 3 222 4 5 7 8 9 333 

// ---Merge a[] and b[] as a[]---
// a[] = 111 0 1 2 3 222 4 5 7 8 9 333 0 0 0 0 0 

// ---Reverse a[]---
// a[] = 0 0 0 0 0 333 9 8 7 5 4 222 3 2 1 0 111 
// ---Reverse a[]---
// a[] = 111 0 1 2 3 222 4 5 7 8 9 333 0 0 0 0 0 

// ---Destroy a[]---
// a[] = 
// -----[test result]-----
