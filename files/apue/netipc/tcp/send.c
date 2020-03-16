#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in rcvaddr, rtnaddr;
	socklen_t rtnaddrlen;
	msg_t msgbuf;

	if (argc != 2)
		exit(1);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	// bind();
	rcvaddr.sin_family = AF_INET;
	rcvaddr.sin_port = htons(RCV_PORT);
	inet_aton(RCV_IP, &rcvaddr.sin_addr);

	if (connect(sd, (struct sockaddr *)&rcvaddr, sizeof(rcvaddr)) == -1) {
		perror("connect()");
		exit(1);
	}

	strncpy(msgbuf.msg, argv[1], MSGSIZE);

	if(send(sd, msgbuf.msg, strlen(argv[1])+1, 0) == -1) { // write();
		perror("send()");
		exit(1);
	}
	exit(0);
}

