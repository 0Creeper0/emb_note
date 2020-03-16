//增加学生， 查找学生  删除指定学生 遍历所有学生信息 修改学生信息  得到总共有多少个学生
#include <stdio.h>
#include <string.h>
#include <stu.h>

enum 
{
	ADD = 1,
	FIND,
	DEL,
	UPDATE,
	SHOW,
	TOTAL,
	EXIT = 9
};

int comp(const void *data, const void *key)
{
	const char *d = data;
	const char *k = key;
	return strcmp(d, k);
}

static void get_extra_ch()
{
	do
	{
		if (getchar() == '\n')
			break;
	} while(1);
}
int main()
{
	sysstu sys;
	struct stu_st stu, *f;
	int choice;
	char name[NAMESIZE];

	sys_init(&sys);

	while (1)
	{
		printf("1.增加 2.查找 3.删除 4.修改 5.显示所有 6.总人数 9.退出\n");
		printf("请输入选项:");
		scanf("%d", &choice);
		get_extra_ch();
		if (choice == EXIT)
			break;
		switch (choice)
		{
			case ADD:
				printf("请输入学生信息\n");
				printf("姓名: ");
				fgets(stu.name, NAMESIZE, stdin);
				(stu.name)[strlen(stu.name)-1] = '\0';
				printf("年龄: ");
				scanf("%d", &stu.age);
				get_extra_ch();
				printf("电话: ");
				fgets(stu.phone, PHONESIZE, stdin);
				(stu.phone)[strlen(stu.phone)-1] = '\0';
				stu_add(&sys, stu);
				break;
			case FIND:
				printf("请输入学生姓名: ");
				fgets(stu.name, NAMESIZE, stdin);
				(stu.name)[strlen(stu.name)-1] = '\0';
				f = stu_find(&sys, &stu.name, comp);
				if (NULL == f)
					printf("没有这个学生\n");
				else
					printf("姓名 %s 年龄 %d 电话 %s\n", f->name, f->age, f->phone);
				break;
			case DEL:
				printf("请输入学生姓名: ");
				fgets(stu.name, NAMESIZE, stdin);
				(stu.name)[strlen(stu.name)-1] = '\0';
				if (stu_del(&sys, &stu.name, comp) == 0)
					printf("已删除%s\n", stu.name);
				else
					printf("没有这个学生\n");
				break;
			case UPDATE:
				printf("请输入学生姓名: ");
				fgets(stu.name, NAMESIZE, stdin);
				(stu.name)[strlen(stu.name)-1] = '\0';
				f = stu_find(&sys, &stu.name, comp);
				if (NULL == f)
					printf("没有这个学生\n");
				else
				{
					memcpy(name, &stu.name, NAMESIZE);
					printf("请输入修改后的学生信息\n");
					printf("姓名: ");
					fgets(stu.name, NAMESIZE, stdin);
					(stu.name)[strlen(stu.name)-1] = '\0';
					printf("年龄: ");
					scanf("%d", &stu.age);
					get_extra_ch();
					printf("电话: ");
					fgets(stu.phone, PHONESIZE, stdin);
					(stu.phone)[strlen(stu.phone)-1] = '\0';
					if (stu_update(&sys, name, comp, stu) == 0)
						printf("修改成功\n");
					else
						printf("修改失败\n");
				}
				break;
			case TOTAL:
				printf("总人数:%d\n", stu_total(&sys));
				break;
			case SHOW:
				traval(&sys);
				break;
			default:
				break;
		}
	}
	
	return 0;
}
