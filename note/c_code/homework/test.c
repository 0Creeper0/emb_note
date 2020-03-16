#include <stdio.h>

int main(void)
{
	int m = 20;
	int n = 10;
	int *p = &n;
	int **const pp = &p;
	int *q = &m;

	// **pp = 100;	
	*pp = &m;
	pp = &q;

	return 0;
}
