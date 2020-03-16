#include <stdio.h>
#include "lq.h"

// init
lq_t *lq_init(int size)
{
	return llisthead_init(size);
}

// 入队
int lq_push(lq_t *l, const void *data)
{
	return llist_insert(l, data, INSERT_TAIL);
}

static int cmp(const void *data, const void *key)
{
	return 0;
}

// 出队
int lq_pop(lq_t *l, void *data)
{
	return llist_fetch(l, NULL, cmp, data);
}

// 队空
int lq_isempty(const lq_t *l)
{
	return llist_isempty(l);
}

// 销毁
void lq_destroy(lq_t *l)
{
	llist_destroy(l);
}

