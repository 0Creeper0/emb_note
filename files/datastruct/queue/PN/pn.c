#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../stack/stack/stack.h"
#include "../../queue/q/queue.h"

char *mid2front(const char *mid);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;
	// argv[1]
	char *aft = mid2front(argv[1]);
	puts(aft);

	return 0;
}

static int is_operator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

static int is_digital(char ch)
{
	return ch >= '0' && ch <= '9';
}

static int accociaty(char ch)
{
	int level = 0;
	if (ch == '+' || ch == '-')
		level = 1;
	else if (ch == '*' || ch == '/')
		level = 2;

	return level;
}

char *mid2front(const char *mid)
{
	stack_t *s;
	queue_t *q;
	char *remid;
	char top;
	char *res;
	int j = 0;
	int len;

	remid = calloc(1, len+1);
	if (NULL == remid)
		return NULL;
	len = strlen(mid);
	// 倒序
	for(int i = 1; i <= len; i++)
	{
		remid[i-1] = mid[len-i];
	}
	remid[len] = '\0';

	res = calloc(1, len+1);
	if (NULL == res)
		return NULL;
		
	s = stack_init(sizeof(char), len);
	q = queue_init(sizeof(char), len);

	while (*remid) 
	{
		printf("1\n");
		if (is_operator(*remid)) 
		{
			// 是+-*/
			if (stack_isempty(s))
				stack_push(s, remid);
			else 
			{
				while (stack_pop(s, &top) == 0) 
				{
					// 优先级低的入队
					if (accociaty(*remid) < accociaty(top)) 
					{
						queue_eq(q, &top);
					} 
					else 
					{
						// 相等或者高入栈
						stack_push(s, &top);	
						break;
					}
				}
				stack_push(s, remid);
			}
		} 
		else if (is_digital(*remid)) 
			queue_eq(q, remid);
		else if (*remid == '(') 
			stack_push(s, remid);	
		else if (*remid == ')') 
		{
			stack_pop(s, &top);
			while (top != '(')
			{
				queue_eq(q, &top);
				stack_pop(s, &top);
			}
		} 
		else
		{
			// 错误
			stack_destroy(s);
			queue_destroy(q);
			return NULL;
		}
		remid ++;
	}

	while (stack_isempty(s) != 1) {
		stack_pop(s, &top);
		queue_eq(q, &top);
	}
	while (queue_isempty(q) != 1) {
		queue_dq(q, &top);
		res[j++] = top;
	}
	

	stack_destroy(s);
	queue_destroy(q);
	return res;
}

