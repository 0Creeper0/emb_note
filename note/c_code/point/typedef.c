#include <stdio.h>

#define DF  int *
typedef int *PF;

int main(void)
{
	DF a, b;	
	PF m, n;

	printf("%ld %ld %ld %ld\n", sizeof(a), sizeof(b),\
			sizeof(m), sizeof(n));

	return 0;
}

