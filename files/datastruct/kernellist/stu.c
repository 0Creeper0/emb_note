#include <stdio.h>
#include <stdlib.h>
#include <stu.h>

// init
void sys_init(sysstu *head)
{
	INIT_LIST_HEAD(head);
}

// add
int stu_add(sysstu *head, struct stu_st stu)
{
	struct node_st *newnode;

	newnode = malloc(sizeof(struct node_st));
	if (NULL == newnode)
		return 1;

	newnode->stu = stu; 
	list_add_tail(&newnode->node, head);
	return 0;
}


// find
struct stu_st *stu_find(sysstu *head, const void *key, comp_t comp)
{
	struct node_st *cur;
	struct list_head *pos;
	list_for_each(pos, head)
	{
		cur = list_entry(pos, struct node_st, node);
		if (comp(cur->stu.name, key) == 0)
			return &cur->stu;
	}
	return NULL;
}
static struct node_st *myfind(sysstu *head, const void *key, comp_t comp)
{
	struct node_st *cur;
	struct list_head *pos;
	list_for_each(pos, head)
	{
		cur = list_entry(pos, struct node_st, node);
		if (comp(cur->stu.name, key) == 0)
			return cur;
	}
	return NULL;
}

// delete
int stu_del(sysstu *head, const void *key, comp_t comp)
{
	struct node_st *entry;
	entry = myfind(head, key, comp);
	if (NULL == entry)
		return -1;
	else
		list_del(&entry->node);
	return 0;
}

// update
int stu_update(sysstu *head, const void *key, comp_t comp, const struct stu_st stu)
{
	struct node_st *entry;
	entry = myfind(head, key, comp);
	if (NULL == entry)
		return -1;
	else
		entry->stu = stu;
	return 0;
}

// total
int stu_total(sysstu *head)
{
	struct list_head *pos;
	int count = 0;
	list_for_each(pos, head)
		count ++;
	return count;
}

// traval
void traval(sysstu *head)
{
	struct node_st *cur;
	struct list_head *pos;

	list_for_each(pos, head)
	{
		cur = list_entry(pos, struct node_st, node);
		printf("%s %d %s\n", cur->stu.name, cur->stu.age, cur->stu.phone);
	}
}

