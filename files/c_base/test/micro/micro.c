#include <stdio.h>

#define FUN(m, n)	(m)*(n) //注意要加上括号,宏是纯替换
#define FUN2(a, b)	a = a ^ b; b = a ^ b; a = a ^ b
#define FUN3(a, b)	typeof(a) e; e = a; a = b; b = e
int main()
{
	int a = 5, b = 3;
	float c = 1.2, d = 3.44;
 	FUN3(c, d);
	printf("a:%f b:%f\n", c, d);

	return 0;
}
