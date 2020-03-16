#ifndef __LQ_H
#define __LQ_H

#include "../../llist2/llist.h"

// ADT
typedef llisthead_t lq_t;

// init
lq_t *lq_init(int size);

// 入队
int lq_push(lq_t *l, const void *data);

// 出队
int lq_pop(lq_t *l, void *data);

// 队空
int lq_isempty(const lq_t *l);

// 销毁
void lq_destroy(lq_t *l);

#endif
