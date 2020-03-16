# ifndef __SEQ_H

#define __SEQ_H

typedef struct seq_t
{
	void *p;
	int size;
	int num;
} seq_t;

// func of custom to compare
typedef int (*comp_t)(const void *data, const void *key);

// init
seq_t *seqlist_init(int size);

//add
int seqlist_add(seq_t *seqlist, const void *data);

// 查
void *seqlist_find(const seq_t *seqlist, const void *key, comp_t cmp);

// 删
int seqlist_del(seq_t *seqlist, const void *key, comp_t cmp);

// 改
int seqlist_update(seq_t *seqlist, const void *key, comp_t cmp, const void *newdata);

// traval
void *seqlist_traval(seq_t *seqlist, void (*pri)(const void *data));

# endif
