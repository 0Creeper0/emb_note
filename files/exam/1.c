#include <stdio.h>

int str2int(char *str)
{
	int res = 0;
	while (*str != '\0')
	{
		res = res * 10 + (*str - '0');
		str ++;
	}
	return res;
}
int main(int argc, char *argv[])
{
	char *a;
	int res, b, c;
	b = str2int(argv[1]);
	a = argv[2];
	c = str2int(argv[3]);

	if (*a == '+')
		res = b + c;
	else if (*a == '-')
		res = b - c;
	else if (*a == '*')
		res = b * c;
	else 
		res = b / c;

	printf("%d\n", res);
	return 0;
}
