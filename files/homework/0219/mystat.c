#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "mystat.h"

static char *__getType(struct stat statbuf)
{
	switch(statbuf.st_mode & S_IFMT)
	{
		case S_IFSOCK:
			return "s";
		case S_IFLNK: 
			return "l";
        case S_IFREG:
			return "-";
        case S_IFBLK:
			return "b";
        case S_IFDIR:
			return "d";
        case S_IFCHR:
			return "c";
        case S_IFIFO:
			return "p";
		default:
			return NULL;
	}
}

static char *__getMode(struct stat statbuf)
{
	static char res[] = "---------";

	if (statbuf.st_mode & S_IRUSR) 
		*res = 'r';
	if (statbuf.st_mode & S_IWUSR) 
		*(res+1) = 'w';
	if (statbuf.st_mode & S_IXUSR)
	{
		if (statbuf.st_mode & S_ISUID)
			*(res+2) = 's';
		else
			*(res+2) = 'x';
	}
	if (statbuf.st_mode & S_IRGRP)
		*(res+3) = 'r';
	if (statbuf.st_mode & S_IWGRP)
		*(res+4) = 'w';
	if (statbuf.st_mode & S_IXGRP)
	{
		if (statbuf.st_mode & S_ISUID)
			*(res+5) = 's';
		else
			*(res+5) = 'x';
	}
	if (statbuf.st_mode & S_IROTH)
		*(res+6) = 'r';
	if (statbuf.st_mode & S_IWOTH)
		*(res+7) = 'w';
	if (statbuf.st_mode & S_IXOTH)
	{
		if (statbuf.st_mode & S_ISUID)
			*(res+8) = 's';
		else
			*(res+8) = 'x';
	}
	return res;
}

// 类型&权限(flag为要获取的值,TYPE,MODE,TYPE|MODE)
char *my_mode(const char *pathname, struct stat *statbuf, int flag)
{
	int s;
	static char str[10] = {};

	s = stat(pathname, statbuf);
	if (s == -1)
		return NULL;

	if (flag == TYPE)
		return __getType(*statbuf);
	else if (flag == MODE)
		return __getMode(*statbuf);
	else if (flag == (TYPE | MODE))
	{
		memcpy(str, __getType(*statbuf), 1);
		memcpy(str+1, __getMode(*statbuf), 9);
		return str;
	}
	else
		return NULL;
}

// 硬连接数
int my_nlink(const char *pathname, struct stat *statbuf)
{
	int s;

	s = stat(pathname, statbuf);
	if (s == -1)
		return -1;

	return statbuf->st_nlink;
}

// 拥有者
char *my_uid(const char *pathname, struct stat *statbuf)
{
	int s;
	struct passwd *pwd;

	s = stat(pathname, statbuf);
	if (s == -1)
		return NULL;

	pwd = getpwuid(statbuf->st_uid);
	return pwd->pw_name;
}

//所属组
char *my_gid(const char *pathname, struct stat *statbuf)
{
	int s;
	struct group *grp;

	s = stat(pathname, statbuf);
	if (s == -1)
		return NULL;

	grp = getgrgid(statbuf->st_gid);
	return grp->gr_name;
}

// 大小
long my_size(const char *pathname, struct stat *statbuf)
{
	int s;

	s = stat(pathname, statbuf);
	if (s == -1)
		return -1;
	
	return statbuf->st_size;
}

// 时间
char *my_mtime(const char *pathname, struct stat *statbuf)
{
	static char buf[100] = {};
	struct tm *tm;
	int s;

	s = stat(pathname, statbuf);
	if (s == -1)
		return NULL;

	tm = localtime(&statbuf->st_mtime);
	strftime(buf, 100, "%m月 %d %H:%M", tm);
	
	return buf;	
}

// 文件名
char *my_filename(const char *pathname)
{
	return (char *)pathname;
}
