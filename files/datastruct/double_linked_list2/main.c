#include <stdio.h>

#include "double_linked_list.h"

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
	dll_head_t *head;
	int arr[] = {1,4,2,5,7,4,3,9};
	if (dll_head_init(&head, sizeof(dll_head_t)) != 0)
		return 1;
	
	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
		dll_insert(head, arr+i, HEAD_INSERT);
	int data = 232;
	
	printf("*******\n");
	data = 343;
	dll_insert(head, &data, HEAD_INSERT);
	dll_traval(head, pri_int);
	printf("*******\n");
	int key = 343;
	dll_del(head, &key, comp_num);
	dll_traval(head, pri_int);
	printf("*******\n");
	int newdata = 12345;
	key = 9;
	dll_update(head, &key, comp_num, &newdata);
	dll_traval(head, pri_int);

	return 0;
}
