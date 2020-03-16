#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

static void fun1()
{
	printf("fun1\n");
}

static void fun2()
{
	printf("fun2\n");
}

static void fun3()
{
	printf("fun3\n");
}

static void test()
{
	printf("test()");
	exit(0);
}
int main()
{
	for (int i = 0; environ[i] != NULL; i++)
		puts(environ[i]);
	atexit(fun1);
	atexit(fun2);
	atexit(fun3);
	

	test();
	printf("main()");
	exit(EXIT_SUCCESS);
}
