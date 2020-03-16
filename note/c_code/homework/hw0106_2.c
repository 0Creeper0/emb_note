#include <stdio.h>

int main(void)
{
	int score[10] = {};			
	int count[11] = {};

	for (int i = 0; i < 10; i++) {
		printf("请输入第%d学生的成绩:", i+1);
		scanf("%d", &score[i]);
		count[score[i] / 10] ++;
	}

	// 打印成绩分布
	printf("100:");
	for (int i = 0; i < count[10]; i++)
		printf("* ");
	printf("\n");
	for (int i = 9; i >= 0; i--) {
		printf("%d~%d:", i*10, i*10+9);	
		for (int j = 0; j < count[i]; j++) {
			printf("* ");
		} 
		printf("\n");
	}

	return 0;
}

