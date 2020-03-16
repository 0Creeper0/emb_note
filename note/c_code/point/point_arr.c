#include <stdio.h>

int main(int argc, char *argv[] /*char **argv*/)
{
	// 指针数组
	char *str[3] = {"hello", "world", "after"};
	int *p;
	char *q;
	long *m;

	printf("%ld, %ld, %ld\n", sizeof(p), sizeof(q), sizeof(m));
	printf("%ld\n", sizeof(str));

	// str---->char **

	// for (int i = 0; i < argc; i++)
	for (int i = 0; argv[i] != NULL; i++)
		puts(argv[i]);

	return 0;
}
