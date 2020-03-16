/*
 *	读入10个学生信息(id姓名成绩), 求出10个学生中成绩最高的学生
 * */
#include <stdio.h>
#include <string.h>

#define NAMESIZE	32
#define STUNUM		10

#pragma pack(4)	//指定对齐长度

struct student_st
{
	int id;
	char name[NAMESIZE];
	int score;
}/*__attribute__((packed)) 加上表示单字节对齐*/;
int main()
{
	struct student_st stu[STUNUM];
	int max = 0;
	int index = 0;

	for (int i = 0; i < STUNUM; i++)
	{
		printf("输入第%d个学生的id:", i+1);
		scanf("%d", &(stu[i].id));

		printf("输入第%d个学生的姓名:", i+1);
		scanf("%s", stu[i].name);

		printf("输入第%d个学生的成绩:", i+1);
		scanf("%d", &stu[i].score);

		if (stu[i].score > max)
		{
			max = stu[i].score;
			index = i;
		}
	}


	return 0;
}
