#include <stdio.h>

#include "mystat.h"

int main(int argc, char *argv[])
{
	if (argc < 2)
		return -1;

	struct stat statbuf;

	printf("%s ", my_mode(argv[1], &statbuf, TYPE | MODE));
	printf("%d ", my_nlink(argv[1], &statbuf));
	printf("%s ", my_uid(argv[1], &statbuf));
	printf("%s ", my_gid(argv[1], &statbuf));
	printf("%ld ", my_size(argv[1], &statbuf));
	printf("%s ", my_mtime(argv[1], &statbuf));
	printf("%s\n", my_filename(argv[1]));
	return 0;
}
