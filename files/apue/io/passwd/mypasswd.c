#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <shadow.h>

#define NAMESIZE 128

int main()
{
	char user_name[NAMESIZE] = {};
	char *user_passwd, *passwd;
	struct spwd *sp;
	char salt[100];

	printf("输入用户名:");
	scanf("%s", user_name);

	user_passwd = getpass("输入密码:");
	if (NULL == user_passwd)
	{
		perror("getpass()");
		return 1;
	}

	sp = getspnam(user_name);
	if (NULL == sp)
	{
		fprintf(stderr, "getspnam() error\n");
		return 1;
	}

	passwd = crypt(user_passwd, sp->sp_pwdp);
	if (NULL == passwd)
		return 1;

	if (strcmp(passwd, sp->sp_pwdp) == 0)
		printf("成功\n");
	else
		printf("失败\n");
	puts(user_name);
	puts(user_passwd);

	return 0;
}

