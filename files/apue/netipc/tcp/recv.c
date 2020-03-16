#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "proto.h"


int main(void)
{
	int sd, newsd;
	struct sockaddr_in rcvaddr, rtnaddr;
	socklen_t rtnaddrlen;
	msg_t msgbuf;
	int cnt;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	rcvaddr.sin_family = AF_INET;
	rcvaddr.sin_port = htons(RCV_PORT);
	inet_aton(RCV_IP, &rcvaddr.sin_addr);

	if (bind(sd, (struct sockaddr *)&rcvaddr, sizeof(rcvaddr)) == -1) {
		perror("bind()");
		exit(1);
	}

	if(listen(sd, MSGSIZE) == -1) {
		perror("listen()");
		exit(1);
	}

	while (1) {
		newsd = accept(sd, (struct sockaddr *)&rtnaddr, &rtnaddrlen);
		if (newsd == -1) {
			perror("accept()");
			exit(1);
		}

		cnt = read(newsd, &msgbuf.msg, MSGSIZE);// recv();

		write(1, msgbuf.msg, cnt);

		close(newsd);
	}

	close(sd);

	exit(0);
}
