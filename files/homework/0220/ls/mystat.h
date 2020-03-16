#ifndef __MYSTAT_H
#define __MYSTAT_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define TYPE	0x01
#define MODE	0x02

// 显示
int display_file(const char *path);

// 目录
int display_dir(const char *path);

// 类型&权限(flag为要获取的值,TYPE,MODE,TYPE|MODE)
char *my_mode(const char *pathname, struct stat *statbuf, int flag);

// 硬连接数
int my_nlink(const char *pathname, struct stat *statbuf);

// 拥有者
char *my_uid(const char *pathname, struct stat *statbuf);

//所属组
char *my_gid(const char *pathname, struct stat *statbuf);

// 大小
long my_size(const char *pathname, struct stat *statbuf);

// 时间
char *my_mtime(const char *pathname, struct stat *statbuf);

// 文件名
char *my_filename(const char *pathname);

#endif
