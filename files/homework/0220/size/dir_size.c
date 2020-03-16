#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <glob.h>

#define 	BUFSIZE 	100

void show(const char *path);
int main(int argc, char *argv[])
{
	struct stat statres;

	if (argc < 2)
		return 1;

	if (stat(argv[1], &statres) == -1)
	{
		perror("stat()");
		return 1;
	}

	if (!S_ISDIR(statres.st_mode))
	{
		printf("size:%ld\n", statres.st_size);
		return 0;
	}
	else
	{
		show(argv[1]);
	}
	return 0;

}

void show(const char *path)
{
	struct stat statres;
	glob_t glb;
	char buf[BUFSIZE] = {};
	char *p;

	if (stat(path, &statres) == -1)
	{
		perror("stat()");
		return ;
	}

	if (!S_ISDIR(statres.st_mode))
	{
		printf("%ld %s\n", statres.st_size, path); //这里求出来的字节个数不对
		return ;
	}
	
	snprintf(buf, BUFSIZE, "%s/*", path);
	if(glob(buf, 0, NULL, &glb) != 0)
		return ;
	memset(buf, '\0', BUFSIZE);
	snprintf(buf, BUFSIZE, "%s/.*", path);
	if(glob(buf, GLOB_APPEND, NULL, &glb) != 0)
		return ;
	for (int i = 0; i < (int)glb.gl_pathc; i++)
	{
		p = strrchr(glb.gl_pathv[i], '/');                                
		if (p != NULL) 
		{
			if (strcmp(p+1, ".") == 0 || strcmp(p+1, "..") == 0)
				continue;
		}
		show(glb.gl_pathv[i]);
	}
}
