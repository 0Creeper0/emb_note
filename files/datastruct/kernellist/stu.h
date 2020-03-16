//增加学生， 查找学生  删除指定学生 遍历所有学生信息 修改学生信息  得到总共有多少个学生
#ifndef __STU_H
#define __STU_H
#include <kernellist.h>

#define NAMESIZE 	32
#define PHONESIZE 	32

struct stu_st
{
	char name[NAMESIZE];
	int age;
	char phone[PHONESIZE];
};

struct node_st
{
	struct stu_st stu;
	struct list_head node;
};

typedef struct list_head sysstu;
typedef int (*comp_t)(const void *data, const void *key);

// init
void sys_init(sysstu *head);

// add
int stu_add(sysstu *head, struct stu_st stu);

// find
struct stu_st *stu_find(sysstu *head, const void *key, comp_t comp);

// delete
int stu_del(sysstu *head, const void *key, comp_t comp);

// update
int stu_update(sysstu *head, const void *key, comp_t comp, const struct stu_st stu);

// total
int stu_total(sysstu *head);

// traval
void traval(sysstu *head);

# endif
