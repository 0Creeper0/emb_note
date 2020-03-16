#include <stdio.h>
#include <string.h>

#define NAMESIZE	32

// 练习 读入10个学生的信息(id和姓名和成绩),　求出10个学生中成绩最高的学生

struct stu_st {
	int id;
	int score;
	char name[NAMESIZE];
} a, b;
int main(void)
{
	struct stu_st s;
	struct stu_st *p = &s;
	struct stu_st arr[10];
	int max = 0;

#if 0
	s.id = 1;
	strncpy(s.name, "uplooking", NAMESIZE);

	printf("%d, %s\n", s.id, s.name);
	printf("%d, %s\n", p->id, p->name);
#endif

	for (int i = 0; i < 10; i++) {
		printf("id:");
		scanf("%d", &arr[i].id);
		printf("name:");
		scanf("%s", arr[i].name);
		printf("score:");
		scanf("%d", &arr[i].score);
		if (arr[i].score > max)
			max = arr[i].score;
	}

	printf("%d\n", max);

	return 0;
}

