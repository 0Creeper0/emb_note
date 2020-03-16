#include <stdio.h>
#include "list.h"

void pri_int(const void *data)
{
	const int *d = data;
	printf("%d\n", *d);
}

int comp_num(const void *data, const void *key)
{
	const int *d = data;
	const int *k = key;
	return *d - *k;
}


int main()
{

	int arr[] = {1, 5, 65, 3, 8};
	
	head_t *head = NULL;
	struct node_t *p;
	
	if (init_headnode(&head, sizeof(int)) != 0)
		return 1;

	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		list_insert(head, arr+i, TAIL_INSERT);
	}
	list_traval(head, pri_int);

	p = head->headnode.next;
	while (p->next != NULL)
		p = p->next;
	printf("p %p\n", p);
	p->next = head->headnode.next->next;

	printf("head %p\n", &head->headnode);
	printf("next %p\n", head->headnode.next->next);

	printf("entry:%p\n", have_cricle(head));

	
	return 0;
}
