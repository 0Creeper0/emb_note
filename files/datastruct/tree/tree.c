#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"



// 插入
int tree_insert(tree_t **t, const void *data, int size, comp_t comp)
{
	tree_t *new;
	if (NULL == *t)
	{
		printf("1\n");
		new = malloc(sizeof(*new));
		printf("2\n");
		if (NULL == new)
			return -1;
		printf("3\n");
		memcpy(new->data, data, size);
		printf("4\n");
		new->left = new->right = NULL;
		*t = new;
		return 0;
	}
	else
	{
		printf("%d\n", comp(data, (*t)->data));
		if (comp(data, (*t)->data) <= 0)
			return tree_insert(&(*t)->left, data, size, comp);
		else
			return tree_insert(&(*t)->right, data, size, comp);
	}
}

// 删除
int tree_del(tree_t **t, const void *key, comp_t comp);

// 先序
void tree_traval_front(const tree_t *t, pri_t pri);

// 中序
void tree_traval_mid(const tree_t *t, pri_t pri)
{
	if (NULL == t)
		return ;
	tree_traval_mid(t->left, pri);
	pri(t->data);
	tree_traval_mid(t->right, pri);
}

// 后序
void tree_traval_after(const tree_t *t, pri_t pri);
