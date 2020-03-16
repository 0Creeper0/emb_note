#include <stdio.h>

#include "../../../stack/stack.h"

static int count;

static void move(stack_t *src, stack_t *dest)
{
	int n;
	stack_pop(src, &n);
	stack_push(dest, &n);
	count ++;
}

static void hanoi(stack_t *one, int n, stack_t *three, stack_t *two)
{
	if (n < 1)
		return;
	if (n == 1)	{
		move(one, three);
		return;
	}
	hanoi(one, n-1, two, three);
	move(one, three);
	hanoi(two, n-1, three, one);
}

int main(void)
{
	stack_t *one, *two, *three;
	int pop;

	one = stack_init(sizeof(int), 10);
	two = stack_init(sizeof(int), 10);
	three = stack_init(sizeof(int), 10);

	for (int i = 10; i > 0; i--)	{
		stack_push(one, &i);	
	}
	hanoi(one, 10, three, two);

	printf("count:%d\n", count);

	while (!stack_isempty(three)) {
		stack_pop(three, &pop);
		printf("%d\n", pop);
	}

	stack_destroy(one);
	stack_destroy(two);
	stack_destroy(three);
	return 0;
}

