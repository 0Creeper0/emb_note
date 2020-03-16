#ifndef __TREE_H
#define __TREE_H

#define NAMESIZE	32

// ADT
typedef struct tree_st
{
	struct tree_st *left;
	struct tree_st *right;
	int size;
	void *data;
} tree_t;

typedef int (*comp_t)(const void *data, const void *key);
typedef void (*pri_t)(const void *data);


// 插入
int tree_insert(tree_t **t, const void *data, int size, comp_t comp);

// 删除
int tree_del(tree_t **t, const void *key, comp_t comp);

// 先序
void tree_traval_front(const tree_t *t, pri_t pri);

// 中序
void tree_traval_mid(const tree_t *t, pri_t pri);

// 后序
void tree_traval_after(const tree_t *t, pri_t pri);

#endif
