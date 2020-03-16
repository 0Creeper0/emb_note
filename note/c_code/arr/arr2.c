#include <stdio.h>

// 请找出一下数组中的最大值和最小值并将其交换
int main(void)
{
	int arr[] = {3,2,1,6,7,9,5,6,2,8,10};
	int max, min;	
	int max_i, min_i;

	printf("%ld\n", sizeof(arr));

	max = min = arr[0];
	for (int i = 1; i < sizeof(arr) / sizeof(arr[0]); i++) {
		if (arr[i] > max) {
			max = arr[i];
			max_i = i;
		}
		if (arr[i] < min) {
			min = arr[i];
			min_i = i;
		}
	}
	arr[min_i] = max;
	arr[max_i] = min;
	
	printf("max:%d, min:%d\n", max, min);
	for (int i = 0; i < 11; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
