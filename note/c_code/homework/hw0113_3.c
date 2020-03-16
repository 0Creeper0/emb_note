#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arr_insert(int **arr, int *n, int elm);
void arr_traval(int *arr, int n);
int main(void)
{
	int *p = NULL;
	int n = 0;
	int num;

	while (1) {
		printf("输入要插入的元素:");	
		scanf("%d", &num);
		arr_insert(&p, &n, num);
		arr_traval(p, n);
	}

	return 0;
}

int arr_insert(int **arr, int *n, int elm)
{
	int i;

	*arr = realloc(*arr, (*n+1) * sizeof(int));
	if (NULL == *arr)
		return -1;

	for (i = (*n)-1; i >= 0; i--) {
		if ((*arr)[i] > elm)
			break;
	}

	// elm插入到i+1位置
	if (*n > 0)
		memmove(*arr+i+2, *arr+i+1, (*n-i-1)*sizeof(int));
	(*arr)[i+1] = elm;
	(*n)++;

	return 0;
}

void arr_traval(int *arr, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}



