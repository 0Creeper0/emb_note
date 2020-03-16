# ifndef __DOUBLE_LINKED_LIST_H
# define __DOUBLE_LINKED_LIST_H

// typedef
typedef struct dll_node_st 
{
	struct dll_node_st *pre;
	struct dll_node_st *next;
} dll_node_t;

// functions
// head init
int dll_head_init(dll_node_t *head);
// insert
int dll_insert_head(dll_node_t *head, dll_node_t *newnode);

int dll_insert_tail(dll_node_t *head, dll_node_t *newnode);
// delete
int dll_del(dll_node_t *delnode);
# endif

