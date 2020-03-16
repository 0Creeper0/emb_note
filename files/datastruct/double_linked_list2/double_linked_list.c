#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linked_list.h"

// head init
int dll_head_init(dll_node_t *head)
{
	head->next = head->pre = head;
	return 0;
}

static int insert_newnode(dll_node_t *newnode, dll_node_t *p, dll_node_t *n)
{
	newnode->pre = p;
	newnode->next = n;
	newnode->pre->next = newnode;
	newnode->next->pre = newnode;
	return 0;
}
// insert
int dll_insert_head(dll_node_t *head, dll_node_t *newnode)
{
	insert_newnode(newnode, head, head->next);
	return 0;
}

int dll_insert_tail(dll_node_t *head, dll_node_t *newnode)
{
	insert_newnode(newnode, head->pre, head);
	return 0;
}
// delete
int dll_del(dll_node_t *delnode)
{
	delnode->next->pre = delnode->pre;
	delnode->pre->next = delnode->next;
	delnode->pre = delnode->next = NULL;
	return 0;
}
