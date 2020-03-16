#include <stdio.h>

int main()
{
	int arr[6] = {[2] = 5};
	int arr2[3];

	for (int i = 0; i < 6; i++)
	{
		printf ("%d ", arr[i]);
	}
	printf("\n");

	for (int i = 0; i < 3; i++)
	{
		printf ("%d ", arr2[i]);
	}
	printf("\n");

	return 0;
}
