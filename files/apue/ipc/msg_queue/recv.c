#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <errno.h>

#include "proto.h"

int main(void)
{
	key_t key;
	int mgid;
	int created = 1;
	struct msg_st buf;

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

	if (msgrcv(mgid, &buf, MSGSIZE, 0, 0) == -1) {
		perror("msgrcv()");
		goto ERROR;
	}

	printf("%ld, %s\n", buf.mtype, buf.msg);

	if (created) {
		msgctl(mgid, IPC_RMID, NULL);
	}
	
	exit(0);

ERROR:
	if (created) {
		msgctl(mgid, IPC_RMID, NULL);
	}
	exit(1);
}
