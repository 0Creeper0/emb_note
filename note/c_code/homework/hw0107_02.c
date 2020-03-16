#include <stdio.h>

int main(void)
{
	char str[1024] = {};
	int i;
	int start, flag = 0;
	int cnt = 0;

	i = 0;
	do {
		str[i] = getchar();	
		if (str[i] == '\n')
			break;
		i++;
	}while(i < 1024);
	str[i] = '\0';

	for (i = 0; str[i]; i++) {
		if (!flag && str[i] != ' ') {
			start = i;
			flag = 1;
			cnt = 0;
		}
		if (str[i] == ' ') {
			str[i] = '\0';
			if (cnt == 0) {
				printf("%s\n", str+start);
			}
			flag = 0;
			cnt ++;
		}
	}
	if (str[i-1] != '\0')
		printf("%s\n", str+start);

	return 0;
}

