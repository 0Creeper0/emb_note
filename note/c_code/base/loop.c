#if 0
循环:
for(@1循环变量初始化; @2条件; @4循环变量改变) {
	@3循环体;
}
@1->@2真->@3->@4->@2-......

while (条件) {
	循环体;
}
do {
	循环体;
}while(条件);
break; 终止循环
continue; 终止本次循环，继续下一次循环
#endif
#include <stdio.h>

int main(void) 
{
	int i;

	for (i = 0; i < 100; i++)
		printf("*");
	printf("\n");

	i = 0;
	while (i < 100) {
		printf("*");	
		i++;
	}
	printf("\n");

	return 0;
}

