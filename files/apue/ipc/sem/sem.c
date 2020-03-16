#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <errno.h>

#define FLNAME "/tmp/out"
#define BUFSIZE 100

static void P(int semid)
{
	struct sembuf sbf;
	sbf.sem_num = 0;
	sbf.sem_op = -1;
	sbf.sem_flg = 0;

	if (semop(semid, &sbf, 1) == -1) {
		perror("semop()");
		exit(1);
	}
}

static void V(int semid)
{
	struct sembuf sbf;
	sbf.sem_num = 0;
	sbf.sem_op = 1;
	sbf.sem_flg = 0;

	if (semop(semid, &sbf, 1) == -1) {
		perror("semop()");
		exit(1);
	}
}

int main(void)
{
	int semid;
	pid_t pid;

	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1) {
		if (errno != EEXIST) {
			perror("semget()");
			exit(1);
		}
	}

	semctl(semid, 0, SETVAL, 1);

	for (int i = 0; i < 20; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			FILE *fp;
			char buf[BUFSIZE] = {};
			fp = fopen(FLNAME, "r+");
			if (NULL == fp) {
				perror("fopen()");
				exit(1);
			}

			P(semid);
			fgets(buf, BUFSIZE, fp);
			rewind(fp);
			fprintf(fp, "%d", atoi(buf)+1);
			fflush(fp);
			V(semid);
			fclose(fp);
			exit(0);
		}
	}

	for (int i = 0; i < 20; i++)
		wait(NULL);

	semctl(semid, 0, IPC_RMID);
	

	exit(0);
}
