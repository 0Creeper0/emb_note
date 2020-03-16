#include <stdio.h>
#include <string.h>

#include "../../stack/stack/stack.h"
#include "../../queue/q/queue.h"

int ballClock();
int main()
{
	ballClock();
	
	return 0;
}

int is_success(queue_t *q)
{
	queue_t *q2;
	int data, key = 0, flag = 1;
	q2 = queue_init(sizeof(int), 27);

	while (!queue_isempty(q))
	{
		queue_dq(q, &data);
		queue_eq(q2, &data);
		if (flag == 1)
		{
			if (key > data)
				flag = 0;
			key = data;
		}
	}
	while (!queue_isempty(q2))
	{
		queue_dq(q2, &data);
		printf("%d ", data);
		queue_eq(q, &data);
	}
	printf("\n");
	queue_destroy(q2);
	return flag;// 1成功0失败
}

int ballClock()
{
	stack_t *s_s, *s_m, *s_h;
	queue_t *q;
	int day = 0;
	int ball, tmp;

	s_s = stack_init(sizeof(int), 4);
	s_m = stack_init(sizeof(int), 11);
	s_h = stack_init(sizeof(int), 11);

	q = queue_init(sizeof(int), 27);
	for (int i = 1; i < 28; i++)
		queue_eq(q, &i);
	
	while(1)
	{
		printf("%d\n", day);
		queue_dq(q, &ball);
		if (!stack_isfull(s_s))
		{
			stack_push(s_s, &ball);
		}
		else
		{
			while (!stack_isempty(s_s))
			{
				stack_pop(s_s, &tmp);
				queue_eq(q, &tmp);
			}
			if (!stack_isfull(s_m))
			{
				stack_push(s_m, &ball);
			}
			else
			{
				while (!stack_isempty(s_m))
				{
					stack_pop(s_m, &tmp);
					queue_eq(q, &tmp);
				}
				if (!stack_isfull(s_h))
				{
					stack_push(s_h, &ball);
				}
				else
				{
					while (!stack_isempty(s_h))
					{
						stack_pop(s_h, &tmp);
						queue_eq(q, &tmp);
					}
					queue_eq(q, &ball);
					day ++;
					if (is_success(q))
						break;
				}
			}
		}
	}
	printf("day: %d\n", day / 2);

	queue_destroy(q);
	stack_destroy(s_h);
	stack_destroy(s_m);
	stack_destroy(s_s);
	
	return 0;
}
