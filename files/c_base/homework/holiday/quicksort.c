#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE(a)	typeof(a) 

int comp_int(const void *data1, const void *data2)
{
	const int *d1 = data1;
	const int *d2 = data2;

	return *d1 - *d2;
}

int comp_char(const void *data1, const void *data2)
{
	const char *d1 = data1;
	const char *d2 = data2;

	return *d1 - *d2;
}

void myqsort(void *arr, int num, int size, int (*comp)(const void *, const void *));
int main()
{
	int arr_int[] = {48, 6, 3, 28, 19, 2, 0, 35};
	char arr_char[] = "afdxbxgsret";

	for (int i = 0; i < sizeof(arr_char) / sizeof(*arr_char); i++)
		printf("%c ", arr_char[i]);
	printf("\n");

	myqsort(arr_char, sizeof(arr_char) / sizeof(*arr_char), sizeof(char), comp_char);

	for (int i = 0; i < sizeof(arr_char) / sizeof(*arr_char); i++)
		printf("%c ", arr_char[i]);
	printf("\n");

	return 0;
}

void myqsort(void *arr, int num, int size, int (*comp)(const void *, const void *))
{
	int left = 0, right = num - 1;
	char *key = calloc(1, size);

	memcpy(key, (char *)arr, size);

	if (left == right)
		return;
	while (left != right)
	{
		while (right > left)
		{
			if (comp((char *)arr + right * size, key) > 0)
			{
				memcpy((char *)arr + left * size, (char *)arr + right * size, size);
				left ++;
				break;
			}
			else
				right --;
		}
		while (left < right)
		{
			if ( comp(key, (char *)arr + left * size) > 0)
			{
				memcpy((char *)arr + right * size, (char *)arr + left * size, size);
				right --;
				break;
			}
			else
				left ++;
		}
	}
	memcpy((char *)arr + left * size, key, size);
	free(key);
	if (left > 0)
		myqsort((char *)arr, left, size, comp);
	if (right < num - 1)
		myqsort((char *)arr + (right + 1) * size, num - 1 - right, size, comp);
}
