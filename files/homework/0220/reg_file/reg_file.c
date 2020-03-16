#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

#define BUFSIZE 	100

int reg_file(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	printf("%d\n", reg_file(argv[1]));

	return 0;
}

int reg_file(const char *path)
{
	puts(path);
	struct dirent *dr;
	struct stat statres;
	DIR *dirp;
	char buf[BUFSIZE] = {};
	int sum = 0;

	if (stat(path, &statres) == -1)
	{
		perror("stat()");
		return 1;
	}
	if (!S_ISDIR(statres.st_mode))
	{
		fprintf(stderr, "%s 不是目录\n", path);
		return 1;
	}

	dirp = opendir(path);
	if (NULL == dirp)
	{
		perror("opendir()");
		return 1;
	}

	while (1)
	{
		dr = readdir(dirp);
		if (NULL == dr)
		{
			if (errno)
			{
				perror("readdir()");
				return 0;
			}
			break;
		}
		if (strcmp(dr->d_name, ".") == 0 || strcmp(dr->d_name, "..") == 0)
			continue;
		if (dr->d_type & DT_REG)
			sum ++;
		else if (dr->d_type & DT_DIR)
		{
			memset(buf, '\0', BUFSIZE);
			snprintf(buf, BUFSIZE, "%s/%s", path, dr->d_name);
			sum += reg_file(buf);
		}
	}

	closedir(dirp);
	return sum;

}
