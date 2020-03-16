#include <stdio.h>
r (int i = 1; i < n; i++) {


// 排序

int main(void)
{
	int arr[] = {3,2,1,6,9,8,3,4,9,5,19,7};
	int n, tmp;
	int j;
	
	n = sizeof(arr) / sizeof(arr[0]);
#if 0
	// 冒泡
	for (int i = 0; i < n-1; i++) {
		// 第i趟	
		for (int j = 0; j < n-i-1; j++) {
			if (arr[j] > arr[j+1]) {
				tmp = arr[j];
				arr[j] = arr[j+1];	
				arr[j+1] = tmp;
			}
		}
	}
#endif

#if 0

	// 选择排序
	for (int i = 0; i < n-1; i++) {
		// 对于所选择的下表i，与后续所有元素依次比较
		for (int j = i+1; j < n; j++) {
			if (arr[i] > arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
#endif

	// 直接插入排序
	for (int i = 1; i < n; i++) {
		tmp = arr[i]; // 待插入元素
		for (j = i-1; j >= 0; j--) {
			if (tmp < arr[j]) {
				arr[j+1] = arr[j];
			} else 
				break;
		}
		arr[j+1] = tmp;	
	}
	
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}
