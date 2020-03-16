#include <stdio.h>

// 二维数组

int main(void)
{
	int arr[3][2];	
	int arr2[2][3] = {
		{1, 2, 3},
		{11, 22, 33}
	};

	// 赋值
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			arr[i][j] = i+j;
		}
	}

	// 遍历
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++)
			printf("%d ", arr[i][j]);
		printf("\n");
	}

	return 0;
}

