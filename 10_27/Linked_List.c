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
		int n = 0;
		while ((p2 = p1->next) && ++n < i) p1 = p2;
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


ElementType get_value(ListNode * head, int i)
{

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


void insert(ListNode * head, int i, ElementType key)
{

}


ListNode * merge(ListNode * A, ListNode * B)
{

}


void test(ListNode * head)
{
	int n = 0;
	while ((head = head->next)) head->value = ++n;
}


int main(int argc, char const *argv[])
{
	ListNode * a;
	a = create(10);
	test(a);
	print(a);
	printf("Length: %d\n", calculate_length(a));
	delete(&a, 6);
	print(a);
	printf("Length: %d\n", calculate_length(a));
	printf("Search [3]: %d\n", search(a, 3));
	destroy(&a);
	print(a);
	printf("Length: %d\n", calculate_length(a));
	return 0;
}
