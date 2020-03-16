#include <stdio.h>

int main(void)
{
	int line = 10;	
	
	for (int i = 0; i < line; i++) {
		// 空格
		for (int j = 0; j < line-i-1; j++) {
			printf(" ");	
		}
		// 左边一半字符
		for (int j = 0; j <= i; j++) {
			printf("%c", 'A'+j);	
		}
		// 右半字符
		for (int j = i; j > 0; j--) {
			printf("%c", 'A'+j-1);
		}
		printf("\n");
	}


	return 0;
}
	
