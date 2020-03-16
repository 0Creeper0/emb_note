#if 0
读入用户输入的成绩, 判断所属等级
90~100: A
80~89:  B
70~79:	C
60~69:	C
0~59: E
#endif

#include <stdio.h>

int main(void)
{
	int score;

	scanf("%d", &score);
	if (!(score >= 0 && score <= 100))
		return 1;

#if 0
	if (score >= 90 && score <= 100) {
		printf("A\n");
	} else if (score >= 80 && score < 90) {
		printf("B\n");
	} else if (score >= 70 && score <= 79) {
		printf("C\n");
	} else if (score >= 60 && score < 70) {
		printf("D\n");
	} else {
		printf("E\n");
	}
#endif
	switch (score/10) {
		case 10:
			printf("优秀\n");
		case 9:
			printf("A\n");
			break;
		case 8:
			printf("B\n");
			break;
		case 7:
			printf("C\n");
			break;
		case 6:
			printf("D\n");
			break;
		default:
			printf("E\n");
			break;
	}

	return 0;
}

