#include <stdio.h>
#include <string.h>

int main(void)
{
	int arr[11] = {2,6,8,9,10,15,17,19,20,36};
	int n;
	int high, low;
	int mid;

	printf("请输入待插入的整型数:");
	scanf("%d", &n);

#if 0
	for (i = 0; i < 10; i++) {
		if (n <= arr[i]) {
			for (int j = 9; j >= i; j--) {
				arr[j+1] = arr[j];	
			}
			arr[i] = n;
			break;
		}
	}
	if (i == 10) {
		arr[i] = n;
	}
#endif
	// 折半
	low = 0;
	high = 9;
	while (low <= high) {
		mid = (low + high) / 2;
		if (arr[mid] > n) {
			high = mid - 1;
		}
		else if (arr[mid] < n) {
			low = mid + 1;
		} else {
			break;	
		}
	}
	printf("mid:%d\n", mid);
	// n插在mid位置
	if (n > arr[mid]) {
		memcpy(arr+mid+2, arr+mid+1, (10-mid-1)*sizeof(int));
		arr[mid+1] = n;
	} else {
		memcpy(arr+mid+1, arr+mid, (10-mid)*sizeof(int));
		arr[mid] = n;
	}

	for (int i = 0; i < 11; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

