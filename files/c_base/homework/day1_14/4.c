#if 0
4. 通过命令行传参，统计命令行第二个参数大写字母和小写字母分别有多少个
#endif
#include <stdio.h>

int main(int argc, char *argv[])
{
	int count1 = 0, count2 = 0;
	char *p = argv[1];
	while (*p != '\0')
	{
		if (*p >= 65 && *p <= (65 + 26))
			count1++;

		if (*p >= 97 && *p <= (97 + 26))
			count2++;

		p ++;
	}

	printf("大写:%d 小写:%d\n", count1, count2);

	return 0;
}



