#include <lstack.h>

// 初始化
lstack_t *lstack_init(int size)
{
	return llisthead_init(size);
}

// 入栈
int lstack_push(lstack_t *l, const void *data)
{
	return llist_insert(l, data, INSERT_TAIL);
}

// 出栈
int lstack_pop(lstack_t *l, void *data)
{
	struct node_st *p;
	p = l->head.prev;
	p->next->prev = p->prev;
	p->prev->next = p->next;
	p->next = p->prev = NULL;
	memcpy(data, p->data, l->size);
	free(p);
	return 0;
}

// 栈是否为空
int lstack_isempty(const lstack_t *l)
{
	return l->head.next = &l->head && l->head.prev = &l->head;
}

// 销毁
void lstack_destroy(lstack_t *l)
{
	llist_destroy(l);
}
