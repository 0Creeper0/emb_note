#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[])
{
	struct stat res;
	struct tm *tm;

	stat(argv[1], &res);

	tm = localtime(&res.st_mtime);
	printf("%ld\n", res.st_mtime);

	return 0;
}
