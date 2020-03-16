#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef int a;
typedef int (*cmp_t)(const void *, const void *);

int cmp_int(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d2 - *d1;
}

int cmp_str(const void *data1, const void *data2)
{
	 char *const*d1 = data1;
	 char *const*d2 = data2;

	 return strcmp(*d2, *d1);
}

void sort_arr(void *arr, int n, int size, cmp_t cmp);
int main(void)
{
	int arr[] = {3,2,1,6,7,9,8,4,2,5};	
	char *str[] = {"hello", "morning", "morn", "hi"};

	sort_arr(arr, sizeof(arr) / sizeof(*arr), sizeof(int), cmp_int);

	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
		printf("%d ", arr[i]);
	printf("\n");

	sort_arr(str, sizeof(str) / sizeof(*str), sizeof(char *), cmp_str);
	
	for (int i = 0; i < sizeof(str) / sizeof(*str); i++)
		puts(str[i]);

	return 0;
}


void sort_arr(void *arr, int n, int size, cmp_t cmp) 
{
	char *p = calloc(size, 1);
	// if error

	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (cmp((char *)arr+j*size, (char *)arr+(j+1)*size)>0) {
				memcpy(p, (char *)arr+j*size, size);		
				memcpy((char *)arr+j*size, (char *)arr+(j+1)*size, size);		
				memcpy((char *)arr+(j+1)*size, p, size);		
			}
		}
	}
	free(p);
}

