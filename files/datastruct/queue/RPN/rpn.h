#ifndef __RPN_H
#define __RPN_H

#include "../../stack/stack/stack.h"
#include "../q/queue.h"

// ADT
typedef queue_t rpn_q;
typedef stack_t rpn_s;

// init
int rpn_init(rpn_q **q, rpn_s **s, int size, int maxnmemb);

// 入队
int rpn_eq(rpn_q *q, const void *data);

// 出队
int rpn_dq(rpn_q *q, void *data);

// 入栈
int rpn_push(rpn_s *s, const void *data);

// 出栈
int rpn_pop(rpn_s *s, void *data);

// 比较
int comp(const void *data, const void *key);

// 数字
int rpn_isd(const void *data);

#endif
