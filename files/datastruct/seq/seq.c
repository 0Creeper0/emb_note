#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <seq.h>

// init
seq_t *seqlist_init(int size)
{
	seq_t *seq_p = NULL;

	seq_p = malloc(sizeof(*seq_p));

	if (NULL == seq_p)
		return seq_p;
	
	seq_p->p = NULL;
	seq_p->size = size;
	seq_p->num = 0;

	return seq_p;
}

//add
int seqlist_add(seq_t *seqlist, const void *data)
{
	seqlist->p = realloc(seqlist->p, (seqlist->num+1) * seqlist->size);
	if (NULL == seqlist->p)
		return 1;
	memcpy((char *)(seqlist->p)+seqlist->num * seqlist->size, data, seqlist->size);

	seqlist->num ++;

	return 0;
}

// 查
void *seqlist_find(const seq_t *seqlist, const void *key, comp_t cmp)
{
	for(int i = 0; i < seqlist->num; i++)
	{
		if(cmp((char *)(seqlist->p)+i*seqlist->size, key) == 0)
			return (char *)(seqlist->p)+i*seqlist->size;
	}
}

// 删
int seqlist_del(seq_t *seqlist, const void *key, comp_t cmp)
{
	char *forward, *next;
	for(int i = 0; i < seqlist->num; i++)
	{
		if(cmp((char *)(seqlist->p)+i*seqlist->size, key) == 0)
		{
			forward = (char *)(seqlist->p)+i*seqlist->size;
			break;
		}
	}

	next = forward + seqlist->size;

	memcpy(forward, next, seqlist->num*seqlist->size-(next-(char *)(seqlist->p)));

	seqlist->num --;

	seqlist->p = realloc(seqlist->p, seqlist->num*seqlist->size);
	if (NULL == seqlist->p)
		return 1;
	
	return 0;
}

// 改
int seqlist_update(seq_t *seqlist, const void *key, comp_t cmp, const void *newdata)
{
	char *dest;
	for(int i = 0; i < seqlist->num; i++)
	{
		if(cmp((char *)(seqlist->p)+i*seqlist->size, key) == 0)
		{
			dest = (char *)(seqlist->p)+i*seqlist->size;
			break;
		}
	}

	memcpy(dest, newdata, seqlist->size);

	return 0;

}

// traval
void *seqlist_traval(seq_t *seqlist, void (*pri)(const void *data))
{
	for(int i = 0; i < seqlist->num; i++)
	{
		pri((char *)(seqlist->p)+seqlist->size * i);
	}
}
