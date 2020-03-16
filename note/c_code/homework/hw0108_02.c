#include <stdio.h>

int main(void)
{
	// 0 alive 1 died
	int memb[42] = {};
	int died_cnt = 0;
	int cur = 0;
	int cnt = 0;

	while(1) {
		if (!memb[cur]) {
			// alive
			cnt ++;
			if (cnt == 3) {
				memb[cur] = 1;
				died_cnt ++;
				if (died_cnt == 41)
					break;
				cnt = 0;
			}
		}
		cur = (cur + 1) % 42;
	}

	for (int i = 0; i < 42; i++)
		if (memb[i] == 0) {
			printf("%d是活着的\n", i+1);	
			break;
		}

	return 0;
}

