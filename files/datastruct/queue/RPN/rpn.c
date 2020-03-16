#include <stdio.h>
#include <string.h>
#include "rpn.h"

// init
int rpn_init(rpn_q **q, rpn_s **s, int size, int maxnmemb)
{
	*q = queue_init(size, maxnmemb);
	*s = stack_init(size, maxnmemb);
	return 0;
}

// 入队
int rpn_eq(rpn_q *q, const void *data)
{
	return queue_eq(q, data);
}

// 出队
int rpn_dq(rpn_q *q, void *data)
{
	return queue_dq(q, data);
}

// 入栈
int rpn_push(rpn_s *s, const void *data)
{
	return stack_push(s, data);
}

// 出栈
int rpn_pop(rpn_s *s, void *data)
{
	return stack_pop(s, data);
}

// 比较
int comp(const void *data, const void *key)
{
	int d, k;
	if (*(char *)data == '+' || *(char *)data == '-')
		d = 1;
	else
		d = 2;

	if (*(char *)key == '+' || *(char *)key == '-')
		k = 1;
	else if (*(char *)key == '*' || *(char *)key == '/')
		k = 2;
	else
		k = 0;
	return d - k;
}

// 数字
int rpn_isd(const void *data)
{
	return *(char *)data >=48 && *(char *)data <= 57;
}

