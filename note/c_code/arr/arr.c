#if 0
数组
	相同类型元素的集合
	定义
	赋值
	初始化
#endif

#include <stdio.h>

int main(void)
{
	// 定义
	int arr1[5];
	// 初始化
	int arr2[3] = {10, 14, 12};
	int arr3[3] = {0}; // 所有都为0
	int arr4[3] = {1}; // 第一个元素为1 其他为0
	int arr5[3] = {}; // 所有元素都初始化为0
	int arr6[10] = {[4]=5};

	// 赋值
	for (int i = 0; i < 5; i++) {
		arr1[i] = i+1;
	}

	// 遍历
	for (int i = 0; i < 5; i++) {
		printf("%d ", arr1[i]);
	}
	printf("\n");

	for (int i = 0; i < 10; i++)
		printf("%d ", arr6[i]);
	printf("\n");

	return 0;
}

