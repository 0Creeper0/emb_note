#if 0
2. 约瑟夫环问题，题意是：已知 42 个人（分别用编号 1，2，3，…，42 表示）围坐在一张圆桌周围，从编号为 1 的人开始顺时针报数，数到 3 的那个人杀掉；他的下一个人又从 1 开始，还是顺时针开始报数，数到 3 的那个人又杀掉；依次重复下去，直到圆桌上剩余一个人。
#endif
#include <stdio.h>

int main()
{
	int arr[42] = {};
	int die = 1;
	int count = 42;

	while (count >= 1)
	{
		for (int i = 0; i < 42; i++)
		{
			if (arr[i] == 1)
				continue;
			if (count == 1)
			{
				printf("%d号活着\n", i+1);
				return 0;
			}
			if (die == 3)
			{
				arr[i] = 1;
				count--;
				die = 0;
				printf("%d号挂\n", i+1);
			}
			die++;
		}
	}

	return -1;
}
