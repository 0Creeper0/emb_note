#include <stdio.h>

#define N	10

//　宏参数必须有括号
#define FUN(m, n)	(m)*(n)

#define SWAP(a, b)	\
	do {\
		typeof(a) c; \
		c = a; \
		a = b; \
		b = c; \
	} while(0)

#define ABC
int main(void)
{
	int arr[N];
#ifdef ABC
	float a, b;

	a = 10.3;
	b = 2.5;

	SWAP(a, b);
	printf("%f, %f\n", a, b);
#endif
	printf("%d\n", FUN(1+2, 3+4));
	return 0;
}

