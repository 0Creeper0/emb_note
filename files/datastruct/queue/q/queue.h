#ifndef __QUEUE_H
#define __QUEUE_H

// ADT
typedef struct
{
	void *head;
	int index_h;
	int index_t;
	int size;
	int maxnmemb;
	int flag;
} queue_t;

// init
queue_t *queue_init(int size, int maxnmemb);

// 队空
int queue_isempty(const queue_t *q);

// 队满
int queue_isfull(const queue_t *q);

// 入队
int queue_eq(queue_t *q, const void *data);

// 出队
int queue_dq(queue_t *q, void *data);

// 销毁
void queue_destroy(queue_t *q);

#endif
