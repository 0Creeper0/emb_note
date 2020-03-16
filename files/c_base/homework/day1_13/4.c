#if 0
4. 尝试自己实现getline(3)函数
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t mygetline(char **lineptr, size_t *n, FILE *stream);
int main()
{
	int res;
	char *ptr = NULL;
	size_t n = 0;
	res = mygetline(&ptr, &n, stdin);
	printf("ptr:%s\nres:%d\n", ptr, res);

	return 0;
}

size_t mygetline(char **lineptr, size_t *n, FILE *stream)
{
	char ch, *p = NULL;
	int size = 0;
	int count1 = 0, count2 = 0;

	if (*lineptr == NULL && *n == 0)
	{
		p = realloc(p, size + 120);
		*p = '\0';
		while ((ch = getchar()) != '\n')
		{
			count1 ++;// 记录字符数量,满120就扩充
			if (count1 == 120)
			{
				count1 = 0;
				size ++;
			}
			p = realloc(p, size + 120);
			strcat(p, &ch);
		}
		*lineptr = p;
		while (*p)
		{
			if ((*p == ' ' && *(p - 1) != ' ') || (*(p+1) == '\0' && *p != ' '))
				count2 ++;
			p ++;
		}
	}

	return count2;
}
