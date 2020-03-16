#include <stdio.h>
#include <string.h>

#include "rpn.h"

int main(int argc, char *argv[])
{
	rpn_q *q;
	rpn_s *s;
	int size = sizeof(int);
	int maxnmemb = 10;
	rpn_init(&q, &s, size, maxnmemb);
	char cur;
	char pop;
	int a, b, res = 0;

	for(int i = 0; i < strlen(argv[1]); i++)
	{
		cur = argv[1][i];
		if (rpn_isd(&cur))
			// 是数字
			rpn_eq(q, &cur);
		else
		{
			// 是符号
			if (cur == '(')
				// 是(
				rpn_push(s, &cur);
			else
			{
				// 是+-*/)
				if (cur == ')')
				{
					// 是)
					while (*((char *)s->top-s->size) != '(')
					{
						rpn_pop(s, &pop);
						rpn_eq(q, &pop);
					}
					rpn_pop(s, &pop);
				}
				else
				{
					// 是+-*/
					if (comp(&cur, (char *)s->top-s->size) > 0 || s->top == s->base)
						// 优先级比栈顶高或者栈顶是(
						rpn_push(s, &cur);
					else
					{
						// 优先级比栈顶低或者相等
						while ( s->top != s->base)
						{
							if (comp(&cur, (char *)s->top-s->size) <= 0)
							{
								rpn_pop(s, &pop);
								rpn_eq(q, &pop);
							}
							else
								break;
						}
						rpn_push(s, &cur);
					}
				}
			}
		}
	}
	
	while (s->top != s->base)
	{
		rpn_pop(s, &pop);
		rpn_eq(q, &pop);
	}

	printf("*********\n");
	while (rpn_dq(q, &pop) == 0)
	{
		printf("%c\n", pop);
		if (rpn_isd(&pop))
			rpn_push(s, &pop);
		else
		{
			rpn_pop(s, &a);
			rpn_pop(s, &b);
			a = a - '0';
			b = b - '0';
			if(pop == '+')
				res = a + b;
			else if (pop == '-')
				res = a - b;
			else if (pop == '*')
				res = a * b;
			else 
				res = a / b;
			res = res + '0';
			rpn_push(s, &res);

		}

	}
	rpn_pop(s, &res);
	printf("Res:%d\n", res-'0');

	return 0;
}
