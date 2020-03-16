#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"


// init
queue_t *queue_init(int size, int maxnmemb)
{
	queue_t *q = malloc(sizeof(queue_t));
	if (NULL == q)
		return NULL;

	q->head = calloc(maxnmemb, size);
	if (NULL == q->head)
		return NULL;

	q->size = size;
	q->maxnmemb = maxnmemb;
	q->index_h = q->index_t = 0;
	q->flag = 0; // 执行入队时置一
	return q;
}

// 队空
int queue_isempty(const queue_t *q)
{
	return q->index_h == q->index_t && q->flag == 0;
}

// 队满
int queue_isfull(const queue_t *q)
{
	return q->index_h == q->index_t && q->flag == 1;
}

// 入队
int queue_eq(queue_t *q, const void *data)
{
	if (queue_isfull(q))
		return 1;
	q->flag = 1;
	memcpy((char *)q->head+q->index_t*q->size, data, q->size);
	q->index_t = (q->index_t + 1) % q->maxnmemb;
	return 0;
}

// 出队
int queue_dq(queue_t *q, void *data)
{
	if (queue_isempty(q))
		return 1;
	q->flag = 0;
	memcpy(data, (char *)q->head+q->index_h*q->size, q->size);
	q->index_h = (q->index_h + 1) % q->maxnmemb;
	return 0;
}

// 销毁
void queue_destroy(queue_t *q)
{
	free(q->head);
	free(q);
}
