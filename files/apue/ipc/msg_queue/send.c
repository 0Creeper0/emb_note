#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	key_t key;
	int mgid;
	int created = 1;
	struct msg_st msg;

	if (argc != 3)
		exit(1);

	key = ftok(PATHNAME, PRO_ID);
	if (key == -1) {
		perror("ftok()");
		exit(1);
	}

	mgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
	if (mgid == -1) {
		if (errno != EEXIST) {
			perror("msgget()");
			exit(1);
		} else {
			// 存在
			mgid = msgget(key, 0);
			created = 0;
		}
	}

	msg.mtype = atoi(argv[1]);
	strncpy(msg.msg, argv[2], MSGSIZE);
	msgsnd(mgid, &msg, strlen(argv[2])+1, 0);

	if (created) {
		msgctl(mgid, IPC_RMID, NULL);
	}
	
	exit(0);
}
