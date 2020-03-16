#include <stdio.h>
#include <string.h>

class Student {
public:
	int id;
	char *name;
	void show() {
		printf("%d %s\n", id, name);
	}
};

int main()
{
	Student stu;
	stu.id = 1;
	stu.name = "魏英杰";
	stu.show();

	return 0;
}
