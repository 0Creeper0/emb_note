#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

// init headnode
int init_headnode(head_t **head, const int size)
{
	head_t *h;
	h = malloc(sizeof(head_t));
	if (NULL == h)
		return 1;
	h->size = size;
	h->headnode.data = NULL;
	h->headnode.next = NULL;

	*head = h;

	return 0;
	
}

void *have_cricle(head_t *head)
{
	struct node_t *fast;
	struct node_t *slow;
	struct node_t *p;
	fast = slow = &head->headnode;
	while(fast != NULL && fast->next != NULL && fast->next->next != NULL)
	{
		slow = slow->next;
		if (slow->next != NULL)
			fast = fast->next->next;
		printf("s%p f%p\n", slow, fast);
		if (fast == slow)
		{
			p = slow;
			fast = &head->headnode;
			while (1)
			{
				printf("s%p f%p\n", slow, fast);
				fast = fast->next;
				slow = slow->next;
				while (slow != p)
				{
					slow = slow->next;
					if (slow == fast)
						return slow;
				}
			}
		}

	}
	return NULL;
}
// list insert
int list_insert(head_t *head, const void *data, int way)
{
	struct node_t *new;
	struct node_t *p;

	if (!(way == HEAD_INSERT || way == TAIL_INSERT))
		return 1;

	new = malloc(sizeof(struct node_t));
	if (NULL == new)
		return 1;
	new->data = calloc(1, head->size);
	memcpy(new->data, data, head->size);

	if (way == HEAD_INSERT)
	{
		new->next = head->headnode.next;
		head->headnode.next = new;
	}
	else
	{
		new->next = NULL;
		if (head->headnode.next == NULL)
			head->headnode.next = new;
		else
		{
			for (p = head->headnode.next; p->next != NULL; p = p->next)
				;
			p->next = new;
		}
	}
	return 0;
}

// list find
void *list_find(head_t *head, const void *key, comp_t comp)
{
	struct node_t *p;

	for (p = head->headnode.next; p != NULL; p = p->next)
	{
		if (comp(p->data, key) == 0)
			return p->data;
	}
}

static struct node_t *find_pre_cur(head_t *head, const void *key, comp_t comp)
{
	struct node_t *pre, *cur;
	pre = &head->headnode;
	cur = pre->next;

	while(cur != NULL)
	{
		if(comp(cur->data, key) == 0)
			return pre;
		pre = cur;
		cur = pre->next;
	}
	return NULL;
}

// list del
int list_del(head_t *head, const void *key, comp_t comp)
{
	struct node_t *pre, *del;
	pre = find_pre_cur(head, key, comp);
	if (NULL == pre)
		return 1;
	del = pre->next;

	pre->next = del->next;
	del->next = NULL;

	free(del->data);
	free(del);

	return 0;
}

// list update
int list_update(head_t *head, const void *key, comp_t comp, const void *newdata)
{
	struct node_t *update;
	update = find_pre_cur(head, key, comp);
	if(NULL == update)
		return 1;
	update = update->next;

	memcpy(update->data, newdata, head->size);
	return 0;
}

// list destroy
void list_destroy(head_t *head)
{
	struct node_t *next, *p;
	p = &head->headnode;
	while (p != NULL)
	{
		next = p->next;
		free(p->data);
		free(p);
		p = next;
	}
	free(head);
}

// list traval
void list_traval(head_t *head, void (pri)(const void *data))
{
	struct node_t *p;
	for (p = head->headnode.next; p != NULL; p = p->next)
	{
		pri(p->data);
		printf("%p\n", p);
	}
}
