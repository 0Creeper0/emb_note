#include <stdio.h>

int main ()
{
	int n, k, res, sum;

	scanf ("%d%d", &n, &k);

	sum = n * 2;

	if (sum % k == 0)
		res = sum / k;
	else
		res = sum / k + 1;

	printf ("%d\n", res);

	return 0;
}

