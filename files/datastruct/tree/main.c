#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

#define NAMESIZE	32

struct stu_st {
	int id;
	char name[NAMESIZE];
};

int comp(const void *data, const void *key)
{
	const struct stu_st *d = data;
	const struct stu_st *k = key;

	printf("%d %d\n", d->id, k->id);
	return d->id - k->id;
}

void pri(const void *data)
{
	const struct stu_st *d = data;
	printf("%d %s\n", d->id, d->name);
}

int main()
{
	tree_t *root = NULL;
	int ids[] = {5,7,4,1,9,2,3,8,6};
	struct stu_st s;

	for (int i = 0; i < sizeof(ids) / sizeof(*ids); i++) {
		s.id = ids[i];
		snprintf(s.name, NAMESIZE, "stu%d", ids[i]);
		tree_insert(&root, &s, sizeof(struct stu_st), comp);
	}
	
	tree_traval_mid(root, pri);

	return 0;
}

