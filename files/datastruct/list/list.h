#ifndef __LIST_H

#define __LIST_H

// typedef
// node
struct node_t 
{
	void *data;
	// pointer to next
	struct node_t *next;
};

// headnode
typedef struct
{
	int size;
	// the same type to node
	struct node_t headnode;
} head_t;

// way
enum
{
	HEAD_INSERT,
	TAIL_INSERT
};

// interface func
typedef int (*comp_t)(const void *data, const void *key);

void *have_cricle(head_t *head);
// init headnode
int init_headnode(head_t **head, const int size);

// list insert
int list_insert(head_t *head, const void *data, int way);

// list find
void *list_find(head_t *head, const void *key, comp_t comp);

// list del
int list_del(head_t *head, const void *key, comp_t comp);

// list update
int list_update(head_t *head, const void *key, comp_t comp, const void *newdata);

// list destroy
void list_destroy(head_t *head);

// list traval
void list_traval(head_t *head, void (pri)(const void *data));
#endif
