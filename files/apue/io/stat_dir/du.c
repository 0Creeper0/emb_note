#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

#define	BUFSIZE 	128
int get_dir_size(const char *dirname);
int main(int argc, char *argv[])
{

	if (argc < 2)
		return 1;

	printf("%dK %s\n", get_dir_size(argv[1]), argv[1]);

	return 0;
}

int get_dir_size(const char *dirname)
{
	struct stat statbuf;
	int size = 0;
	DIR *dp = NULL;
	struct dirent *dr;
	char path[BUFSIZE];
	puts(dirname);

	if (stat(dirname, &statbuf) == -1) {
		perror("stat()");
		return 1;
	}
	if (!S_ISDIR(statbuf.st_mode))
		return statbuf.st_blocks / 2;

	size += statbuf.st_blocks / 2;
	
	dp = opendir(dirname);
	if (NULL == dp) {
		perror("opendir()");
		return 1;
	}

	while (1) {
		dr = readdir(dp);
		if (dr == NULL) {
			if (errno) {
				perror("readdir");
				return 1;
			}
			break;
		}
		if (strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0)
			continue;
		memset(path, '\0', BUFSIZE);
		snprintf(path, BUFSIZE, "%s/%s", dirname, dr->d_name);
		size += get_dir_size(path);
	}
	return size;
}
