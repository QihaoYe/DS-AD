#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ElementType int


typedef struct ListNode
{
	ElementType key;
	struct ListNode* next;
}ListNode;


ListNode * reverse(ListNode * A)
{
	if (NULL == A || NULL == A->next) return A;
	ListNode* temp_1 = A;
	ListNode* temp_2 = A->next;
	ListNode* temp_3;
	A->next = NULL;
	while ((temp_3 = temp_2->next) != NULL)
	{
		temp_2->next = temp_1;
		temp_1 = temp_2;
		temp_2 = temp_3;
	}
	temp_2->next = temp_1;
	return temp_2;
}
// Change the next pointer to reverse a linked list


void show(ListNode * A)
{
	if (NULL == A) return;
	ListNode* temp = A;
	printf("%d ", temp->key);
	while (NULL != (temp = temp->next))
		printf("%d ", temp->key);
	printf("\n");
}
// Show linked list as an array


int main(int argc, char const *argv[])
{
	ListNode tail = {10, NULL};
	ListNode p9 = {9, &tail};
	ListNode p8 = {8, &p9};
	ListNode p7 = {7, &p8};
	ListNode p6 = {6, &p7};
	ListNode p5 = {5, &p6};
	ListNode p4 = {4, &p5};
	ListNode p3 = {3, &p4};
	ListNode p2 = {2, &p3};
	ListNode p1 = {1, &p2};
	ListNode head = {0, &p1};
	// Test set
	show(&head);
	// Show the origin condition
	show(reverse(&head));
	// Show the reversed condition
	return 0;
}
