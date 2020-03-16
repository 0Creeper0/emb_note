#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int pipefd[2] = {}, fd;
	pid_t pid;
	char *str;
	char ch;
	struct stat statres;

	if (argc != 2) {
		exit(1);
	}

	if (pipe(pipefd) == -1) {
		perror("pipe()");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		exit(1);
	}

	if (pid == 0) {
		// 子进程
		write(1, "child\n", 6);
		close(pipefd[1]); // 关写

		while (read(pipefd[0], &ch, 1) > 0) {
			if (ch >= 'a' && ch <= 'z') {
				ch -= 32;
			} else if (ch >= 'A' && ch <= 'Z') {
				ch += 32;
			}
			write(1, &ch, 1);
		}

		write(1, "\n", 1);
		close(pipefd[0]);
		_exit(0);

	} else {
		// 父进程
		close(pipefd[0]);

		fd = open(argv[1], O_RDONLY);
		if (fd == -1) {
			perror("open()");
			exit(1);
		}

		if (stat(argv[1], &statres) == -1) {
			perror("stat()");
			exit(1);
		}
//////////////////////////////////////////////
		str = mmap(argv[1], statres.st_size, PROT_READ, MAP_SHARED, fd, lseek(fd, 0, SEEK_SET));
		if (MAP_FAILED == str) {
			perror("mmap()");
			exit(1);
		}

		write(pipefd[1], str, strlen(str));
		close(pipefd[1]);

		wait(NULL);
		exit(0);
	}
}
