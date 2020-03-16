#include <stdio.h>

int main(void)
{
	int arr[3][3][3] = {
		{
			{1, 0, 0},
			{1, 0, 0},
			{1, 1, 0}
		},
		{
			{1, 0, 0},
			{1, 1, 0},
			{0, 1, 0}
		},
		{
			{1, 1, 1},
			{0, 1, 0},
			{0, 0, 0}
		}
	};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int z = 0; z < 3; z++) {
				if (arr[i][j][z]) {
					printf("[]");
				} else {
					printf("  ");
				}
			}
			printf("\n");
		}
		printf("下一个图形\n");	
	}

	return 0;
}

