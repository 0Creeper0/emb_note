#include <stdio.h>
#include <string.h>
#include <seq.h>

#define NAMESIZE 	32

struct student_st
{
	int id;
	char name[NAMESIZE];
};

void pri(const void *data)
{
	const struct student_st *d = data;
	printf("%d %s\n", d->id, d->name);
}

int comp_name(const void *data, const void *key)
{
	const struct student_st *d = data;
	const char *k = key;

	return strcmp(d->name, k);
	
}

int main()
{
	// init
	seq_t *list;

	struct student_st stu;

	list = seqlist_init(sizeof(struct student_st));

	stu.id = 1;
	strcpy(stu.name, "aaa");
	seqlist_add(list, &stu);
	stu.id = 2;
	strcpy(stu.name, "bbb");
	seqlist_add(list, &stu);
	stu.id = 3;
	strcpy(stu.name, "ccc");
	seqlist_add(list, &stu);

	seqlist_traval(list, pri);	

	const char *delname = "bbb";
	seqlist_del(list, delname, comp_name);
	seqlist_traval(list, pri);	

	const char *update_name = "aaa";
	stu.id = 4;
	strcpy(stu.name, "asd");
	seqlist_update(list, update_name, comp_name, &stu);
	seqlist_traval(list, pri);	

	return 0;
}
