#include <stdio.h>

int main()
{
	int score;

	printf("请输入分数:");
	scanf("%d", &score);

	if (score <= 100)
	{
		if (score >= 90 )
			printf("等级为A\n");
		else if (score >= 80)
			printf("等级为B\n");
		else if (score >= 70)
			printf("等级为C\n");
		else if (score >= 60)
			printf("等级为D\n");
		else if (score >= 0 && score < 60)
			printf("等级为E\n");
	}
	else
		printf("输入有误\n");

	return 0;
}

