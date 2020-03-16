#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


#define THR_N 	20
#define F_NAME	"/tmp/out"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_t pth[THR_N] = {};

static int _read_file(const char *path, int *count);
static void *pth_job(void *arg);
int main(void)
{
	int err;
	int fd, res;

	for (int i = 0; i < THR_N; i++)
	{
		err = pthread_create(pth+i, NULL, pth_job, NULL);
		if (err != 0)
		{
			fprintf(stderr, "pthread_create() %s\n", strerror(err));
			exit(1);
		}
	}

	pthread_mutex_lock(&mutex);
	do {
	fd = open(F_NAME, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		if (errno == EINTR)
			continue;
		perror("open()");
		exit(1);
	}
	} while(fd < 0);

	res = write(fd, "0", 1);
	if (res == -1)
	{
		if (errno != EINTR)
		{
			perror("write()");
			close(fd);
			exit(1);
		}
	}
	close(fd);
	printf("%d\n", _read_file(F_NAME, NULL));
	exit(0);
	pthread_cond_broadcast(&cond); 
	pthread_mutex_unlock(&mutex);

	while (1)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		if (_read_file(F_NAME, NULL) == 20)
			break;
		pthread_mutex_unlock(&mutex);
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	exit(0);
}

static int _read_file(const char *path, int *count)
{
	int fd, res;
	char buf[128] = {};
	printf("1\n");

	do {
		fd = open(path, O_RDONLY);
		printf("1\n");
		if (fd == -1)
		{
			if (errno == EINTR)
				continue;
			perror("open()");
			exit(1);
		}
	} while(fd < 0);
	printf("1\n");

	while (1)
	{
		res = read(fd, buf, 128);
		if (res == 0)
			break;
		if (res == -1)
		{
			if (errno == EINTR)
				continue;
			perror("read()");
			close(fd);
			return -1;
		}
	}
	printf("1\n");
	close(fd);
	printf("res:%d\n", res);
	//memcpy(count, &res, sizeof(int));
	*count = res;
	printf("1\n");
	res = atoi(buf);
	printf("1\n");
	printf("count:%d res:%d\n", *count, res);
	return res;
}

static void *pth_job(void *arg)
{
	int num, count, i = 0;
	char str[128] = {};
	int fd, res;

	while (1)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		num = _read_file(F_NAME, &count);
		if (num == 20)
		{
			pthread_cond_broadcast(&cond);
			pthread_mutex_unlock(&mutex);
			pthread_exit((void *)0);
		}
		num ++;
		while (num != 0)
		{
			str[i++] = num%10 + '0';
			num /= 10;
		}
		str[i] = '\0';
		do {
			fd = open(F_NAME, O_WRONLY);
			if (fd == -1)
			{
				if (errno == EINTR)
					continue;
				perror("open()");
				exit(1);
			}
		} while(fd < 0);
		res = write(fd, str, strlen(str));
		if (res == -1)
		{
			if (errno != EINTR)
			{
				perror("write()");
				close(fd);
				exit(1);
			}
		}
		close(fd);
		printf("%d\n", _read_file(F_NAME, NULL));
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mutex);
	}
}
